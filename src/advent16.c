/*
--- Day 16: Permutation Promenade ---
You come upon a very unusual sight; a group of programs here appear to be dancing.

There are sixteen programs in total, named a through p. They start by standing in a line: a stands in position 0, b stands in position 1, and so on until p, which stands in position 15.

The programs' dance consists of a sequence of dance moves:

Spin, written sX, makes X programs move from the end to the front, but maintain their order otherwise. (For example, s3 on abcde produces cdeab).
Exchange, written xA/B, makes the programs at positions A and B swap places.
Partner, written pA/B, makes the programs named A and B swap places.
For example, with only five programs standing in a line (abcde), they could do the following dance:

s1, a spin of size 1: eabcd.
x3/4, swapping the last two programs: eabdc.
pe/b, swapping programs e and b: baedc.
After finishing their dance, the programs end up in order baedc.

You watch the dance for a while and record their dance moves (your puzzle input). In what order are the programs standing after their dance?

Your puzzle answer was bkgcdefiholnpmja.

--- Part Two ---
Now that you're starting to get a feel for the dance moves, you turn your attention to the dance as a whole.

Keeping the positions they ended up in from their previous dance, the programs perform it again and again: including the first dance, a total of one billion (1000000000) times.

In the example above, their second dance would begin with the order baedc, and use the same dance moves:

s1, a spin of size 1: cbaed.
x3/4, swapping the last two programs: cbade.
pe/b, swapping programs e and b: ceadb.
In what order are the programs standing after their billion dances?

Your puzzle answer was knmdfoijcbpghlea.
*/
#include "advent.h"

typedef struct Instruction {
	char c;
	int a;
	int b;
} Instruction;

static Instruction *input;
static int cntIn;


static int getInput(char *f) {

	char * line = NULL;
    size_t l = 0;
    int flag = 0;

    input = NULL;
    cntIn = 0;

	FILE *file=fopen(f, "r");
	if(file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return 0;
	}
	
	while (getline(&line, &l, file) != -1) {

		char *ptr = strtok(line, ","), ptr1[5] = {0}, ptr2[5] = {0}, *pt;

		while(ptr) {

			input = (Instruction*)realloc(input, ++cntIn * sizeof(Instruction));
			
			if((pt = strchr(ptr, '/')) != NULL)
				ptr[pt-ptr] = ' ';
			sscanf(ptr+1,"%s %s", ptr1, ptr2);

			input[cntIn-1].c = ptr[0];
			if(ptr[0] == 'p') {
				input[cntIn-1].a = ptr1[0] - 'a';
				input[cntIn-1].b = ptr2[0] - 'a';
			}
			else {
				input[cntIn-1].a = toI(ptr1);
				input[cntIn-1].b = toI(ptr2);
			}

			ptr = strtok(NULL, ",");
		}
    }

	fclose(file);
    free(line);
	return 1;
}


static void swap(int *arr, int a, int b) {
	int tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
}


static void calcDance(int *arr, char *res) {

	int val, x, y, tmp[16];

	for(int i = 0; i < cntIn; i++) {

		switch(input[i].c) {

			case 's': 
				val = input[i].a;
				memcpy(tmp, arr + (16-val), val*sizeof(int));
				memcpy(tmp + val, arr, (16-val)*sizeof(int));
				memcpy(arr,tmp,16*sizeof(int)); 
				break;

			case 'p':
				for(int j = 0; j < 16; j++) {
					x = arr[j] == input[i].a ? j : x;
					y = arr[j] == input[i].b ? j : y;
				}
				swap(arr, x, y);
				break;

			case 'x': 
				swap(arr, input[i].a, input[i].b); 
				break;
		}
	} 

	for(int i = 0; i < 16; i++)
		res[i] = arr[i]+97;
}


static char* solve(int choose,  char *f) {

	if(!getInput(f))
		return 0;

	int arr[16], cnt = 0;
	char *res = (char*)calloc(17,sizeof(char));

	for(int i = 0; i < 16; i++)
		arr[i] = i;

	if(choose) {

		while(++cnt){

			calcDance(arr, res);
			
			if(!strcmp(res,"abcdefghijklmnop"))
				break;
		}

		int rounds = 1000000000 % cnt;

		for(int i = 0; i < rounds; i++)
			calcDance(arr, res);	
	}
	else 
		calcDance(arr, res);

	free(input);

	return res;
}

void get16a(char *f) {
	printf("16a: %s\n", solve(0, f));
	
}

void get16b(char *f) {
	printf("16b: %s\n\n", solve(1, f));
}
