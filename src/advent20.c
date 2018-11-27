#include "advent.h"
/*
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
*/

typedef struct Pixel {
	int p[3];
	int v[3];
	int a[3];
} Pixel;

static Pixel *pix;
static int cntP;

static int getInput(char *f) {

	char * line = NULL;
    size_t l = 0;

	cntP = 0;    
    pix = NULL;

	FILE *file=fopen(f, "r");
	if(file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return 0;
	}
	
	while (getline(&line, &l, file) != -1) {
		int a, b, c;
        pix = (Pixel*)realloc(pix, ++cntP * sizeof(Pixel));
        char *s = strtok(line, " ");
        sscanf(s,"p=<%d,%d,%d", &a, &b, &c);
        pix[cntP-1].p[0] = a;
        pix[cntP-1].p[1] = b;
        pix[cntP-1].p[2] = c;
        s = strtok(NULL, " ");
        sscanf(s,"v=<%d,%d,%d", &a, &b, &c);
        pix[cntP-1].v[0] = a;
        pix[cntP-1].v[1] = b;
        pix[cntP-1].v[2] = c;
        s = strtok(NULL, " ");
        sscanf(s,"a=<%d,%d,%d", &a, &b, &c);
        pix[cntP-1].a[0] = a;
        pix[cntP-1].a[1] = b;
        pix[cntP-1].a[2] = c;    
    }
   
	fclose(file);
    free(line);
	return 1;

}

void get20a(char *f) {

	if(!getInput(f))
		return;

	int pixNum, minA = 99999999;

	for(int i = 0; i < cntP; i++) {

		int acc = abs(pix[i].a[0]) + abs(pix[i].a[1]) + abs(pix[i].a[2]);

		if(acc < minA) {
			minA = acc;
			pixNum = i;
		}
	}

	free(pix);

	printf("20a: %d\n", pixNum);
}


void get20b(char *f) {
	printf("20b: not implemented\n");
}

/*
int main() {

	get20a("../input/20.txt");
	
	return 1;
}
*/