#include "advent.h"
/*
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
*/


typedef struct Instruction {
	char name[5];
	int a;
	int regA;
	int b; 
	int regB;
} Instruction;

typedef struct QueueNode {
	long long value;
	struct QueueNode *next;
} QueueNode;

static Instruction *in;
static long long regs[2][26];
static QueueNode *qh[2] = {NULL}, *qt[2] = {NULL};
static int snd, lines;
static char state[2] = "oo";

/*
int toI(char *s) {
	int sum = 0, min = 0;
	if(*s == '-') {
		*s++;
		min++;
	}
    while (*s && *s != '\n')
        sum = sum * 10 + (*s++ - '0');
    return min?-sum:sum;
}
*/

static int getInput(char *f) {

	char * line = NULL;
    size_t l = 0;

	lines = 0;    
    in = NULL;

	FILE *file=fopen(f, "r");
	if(file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return 0;
	}
	
	while (getline(&line, &l, file) != -1) {
        in = (Instruction*)realloc(in, ++lines * sizeof(Instruction));

        char *ptr = strtok(line, " ");
        strcpy(in[lines-1].name,ptr);  

        ptr = strtok(NULL, " ");
        if(ptr && ptr[0] >= 'a' && ptr[0] <= 'z') {
        	in[lines-1].a = ptr[0] - 'a';
        	in[lines-1].regA = 1;
        }
        else if(ptr) {
        	in[lines-1].a = toI(ptr);
        	in[lines-1].regA = 0;
        }
        else
        	in[lines-1].a = 0;

        ptr = strtok(NULL, " ");
        if(ptr && ptr[0] >= 'a' && ptr[0] <= 'z') {
        	in[lines-1].b = ptr[0] - 'a';
        	in[lines-1].regB = 1;
        }
        else if(ptr) {
        	in[lines-1].b = toI(ptr);
        	in[lines-1].regB = 0;
        }
        else
        	in[lines-1].b = 0;
    }
   
	fclose(file);
    free(line);
	return 1;

}


static int execCmd(int line, int prog, int choose) {
	long long a,b;
	
	switch(in[line].name[0]) {
		case 'r': 
			if(choose) {
				if(qh[prog] == NULL) {
					if(state[1-prog] == 'd')
						state[prog] = 'b';
					else if(qh[1-prog] == NULL && state[1-prog] == 'r')
						state[prog] = 'b';
					else
						state[prog] = 'i';
					return line;
					
				}
				else if(qh[prog]->next == NULL) {
					regs[prog][in[line].a] = qh[prog]->value;
					free(qh[prog]);
					qh[prog] = NULL;	
					state[prog] = 'o';
				}
				else {
					QueueNode *tmp = qh[prog];
					regs[prog][in[line].a] = qh[prog]->value;
					qh[prog] = qh[prog]->next;
					free(tmp);
					state[prog] = 'o';
				}
			}
			else {
				a = in[line].regA ? regs[prog][in[line].a] : in[line].a;
				if(a) line = -2;
			}
			break;

		case 'a': 
			b = in[line].regB ? regs[prog][in[line].b] : in[line].b; 
			regs[prog][in[line].a] += b; 
			break;

		case 'j': 
			a = in[line].regA ? regs[prog][in[line].a] : in[line].a; 
			b = in[line].regB ? regs[prog][in[line].b] : in[line].b; 
			if(a) return b + line ; 
			break;

		case 'm': 
			b = in[line].regB ? regs[prog][in[line].b] : in[line].b;
			if(in[line].name[1] == 'u') 
				regs[prog][in[line].a] *= b;
			else
				regs[prog][in[line].a] %= b;
			break;

		case 's': 
			a = in[line].regA ? regs[prog][in[line].a] : in[line].a;
			b = in[line].regB ? regs[prog][in[line].b] : in[line].b;
			if(in[line].name[1] == 'e') 
				regs[prog][in[line].a] = b;
			else {
				if(choose){
					QueueNode *newQ = (QueueNode*)malloc(sizeof(QueueNode));
					newQ->value = a;
					newQ->next = NULL;
					
					if(qh[1-prog] == NULL){
						qh[1-prog] = newQ;
						qt[1-prog] = newQ;
					}
					else {
						qt[1-prog]->next = newQ;
						qt[1-prog] = newQ;
					}
					if(prog)
						++snd;
				}
				else
					snd = a;
			}
			break;
	}
	return ++line;
}

void get18a(char *f) {

	if(!getInput(f))
		return;

	int i = 0;
	snd = 0;

	while( (i = execCmd(i, 0, 0) ) != -1);

	free(in);

	printf("18a: %d\n", snd);
}



void get18b(char *f) {

	if(!getInput(f))
		return;

	int line = 0, iS[2] = {0,0}, prog = 0, send[2] = {0,0};
	snd = 0;

	for(int i = 0; i < 26; i++){
		regs[0][i] = 0;
		regs[1][i] = 0;
	}
	regs[1][15] = 1;

	while(1) {
		long long a,b;
		//
		if(in[line].name[0] == 'r') {
			if(qh[prog] == NULL) {
				//printf("State: %d %d\n",send[prog],prog);
				if(state[1-prog] == 'd')
					break;
				else if(qh[1-prog] == NULL && state[1-prog] == 'r')
					break;
				iS[prog] = line;
				state[prog] = 'r';
				prog = 1 - prog;
				line = iS[prog] - 1;
			}
			else if(qh[prog]->next == NULL) {
				
				regs[prog][in[line].a] = qh[prog]->value;
				free(qh[prog]);
				qh[prog] = NULL;	
				state[prog] = 'o';

			}
			else {
				QueueNode *tmp = qh[prog];
				regs[prog][in[line].a] = qh[prog]->value;
				qh[prog] = qh[prog]->next;
				free(tmp);
				state[prog] = 'o';
			}
		}
		else if(in[line].name[0] == 'a') {
			b = in[line].regB ? regs[prog][in[line].b] : in[line].b; 
			regs[prog][in[line].a] += b; 
		}

		else if(in[line].name[0] ==  'j') {
			a = in[line].regA ? regs[prog][in[line].a] : in[line].a; 
			b = in[line].regB ? regs[prog][in[line].b] : in[line].b; 
			if(a) line += b -1; 
		}

		else if(in[line].name[0] ==  'm') {
			b = in[line].regB ? regs[prog][in[line].b] : in[line].b;
			if(in[line].name[1] == 'u') 
				regs[prog][in[line].a] *= b;
			else
				regs[prog][in[line].a] %= b;
		}

		else if(in[line].name[0] ==  's') {
			a = in[line].regA ? regs[prog][in[line].a] : in[line].a;
			b = in[line].regB ? regs[prog][in[line].b] : in[line].b;
			if(in[line].name[1] == 'e') 
				regs[prog][in[line].a] = b;
			else {
				
				QueueNode *newQ = (QueueNode*)malloc(sizeof(QueueNode));
				newQ->value = a;
				newQ->next = NULL;
				
				if(qh[1-prog] == NULL){

					qh[1-prog] = newQ;
					qt[1-prog] = newQ;
				}
				else {
					qt[1-prog]->next = newQ;
					qt[1-prog] = newQ;
				}
				send[1-prog] += 1;
				if(prog == 1)
					++snd;
			}
		}
		++line;

		if(line < 0 || line >= lines) {
	        if(state[1-prog] == 'd')
	            break;
	        state[prog] = 'd';
	        iS[prog] = line;
	        prog = 1-prog;
	        line = iS[prog];
	    }
	    
	    if(snd > 8000)
	    	break;
	}

	printf("18b: %d\n\n", snd);

}

void get18bb(char *f) {

	if(!getInput(f))
		return;

	int i = 0, iS[2] = {0}, pg = 0;
	snd = 0;

	for(int i = 0; i < 26; i++){
		regs[0][i] = 0;
		regs[1][i] = 0;
	}
	regs[1][15] = 1;


	while(1) {
		
		i = execCmd(i, pg, 1);
		if(state[pg] == 'b')
			break;
		if(i >= lines) {
			printf("DONE %d\n",pg);
			if(state[1-pg] == 'd');
            	break;
	        state[pg] = 'd';
	        iS[pg] = i;
	        pg = 1-pg;
	        i = iS[pg];
		}

		if(state[pg] == 'i') {
			state[pg] = 'r';
			iS[pg] = i;
	        pg = 1 - pg;
	        i = iS[pg] - 1;
		}
        printf("%d\n", snd);
		fflush(stdout);

	}

	free(in);

	printf("18b: %d\n", snd);
}
/*
int main() {
	get18b("../input/18.txt");


	return 1;
	
}
*/