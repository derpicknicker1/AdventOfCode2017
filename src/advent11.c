/*
--- Day 11: Hex Ed ---
Crossing the bridge, you've barely reached the other side of the stream when a program comes up to you, clearly in distress. "It's my child process," she says, "he's gotten lost in an infinite grid!"

Fortunately for her, you have plenty of experience with infinite grids.

Unfortunately for you, it's a hex grid.

The hexagons ("hexes") in this grid are aligned such that adjacent hexes can be found to the north, northeast, southeast, south, southwest, and northwest:

  \ n  /
nw +--+ ne
  /    \
-+      +-
  \    /
sw +--+ se
  / s  \
You have the path the child process took. Starting where he started, you need to determine the fewest number of steps required to reach him. (A "step" means to move from the hex you are in to any adjacent hex.)

For example:

ne,ne,ne is 3 steps away.
ne,ne,sw,sw is 0 steps away (back where you started).
ne,ne,s,s is 2 steps away (se,se).
se,sw,se,sw,sw is 3 steps away (s,s,sw).
Your puzzle answer was 810.

--- Part Two ---
How many steps away is the furthest he ever got from his starting position?

Your puzzle answer was 1567.
*/
#include "advent.h"

static char *input;


static int getInput(char *f) {

	char * line = NULL;
    size_t l = 0;

	FILE *file=fopen(f, "r");
	if(file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return 0;
	}
	
	while (getline(&line, &l, file) != -1) {
        input = (char*)malloc((strlen(line) + 1) * sizeof(char));
        strcpy(input,line);  
    }
   
	fclose(file);
    free(line);
	return 1;
}

static int calcDist(int choose) {

	int x = 0, y = 0, z = 0, res, res2 = 0;
	char *ptr = strtok(input, ",");

	while(ptr) {

		if(!strcmp(ptr,"n")) 		{ y++; z--; }
		else if(!strcmp(ptr,"nw")) 	{ x--; y++; }
		else if(!strcmp(ptr,"ne")) 	{ x++; z--; }
		else if(!strcmp(ptr,"s")) 	{ y--; z++; }
		else if(!strcmp(ptr,"sw")) 	{ x--; z++; }
		else if(!strcmp(ptr,"se")) 	{ x++; y--; }

		if(MAX( MAX(abs(x), abs(y)), abs(z) ) > res2)
			res2 = MAX( MAX(abs(x), abs(y)), abs(z) );

		ptr = strtok(NULL, ",");
	}

	res = MAX( MAX(abs(x), abs(y)), abs(z) );

	free(input);
	input = NULL;

	return choose ? res2 : res;

}

void get11a(char *f) {

	if(!getInput(f))
		return;

	printf("11a: %d\n", calcDist(0));
}


void get11b(char *f) {

	if(!getInput(f))
		return;

	printf("11b: %d\n\n", calcDist(1));
}
