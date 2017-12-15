/*
--- Day 8: I Heard You Like Registers ---
You receive a signal directly from the CPU. Because of your recent assistance with jump instructions, it would like you to compute the result of a series of unusual register instructions.

Each instruction consists of several parts: the register to modify, whether to increase or decrease that register's value, the amount by which to increase or decrease it, and a condition. If the condition fails, skip the instruction without modifying the register. The registers all start at 0. The instructions look like this:

b inc 5 if a > 1
a inc 1 if b < 5
c dec -10 if a >= 1
c inc -20 if c == 10
These instructions would be processed as follows:

Because a starts at 0, it is not greater than 1, and so b is not modified.
a is increased by 1 (to 1) because b is less than 5 (it is 0).
c is decreased by -10 (to 10) because a is now greater than or equal to 1 (it is 1).
c is increased by -20 (to -10) because c is equal to 10.
After this process, the largest value in any register is 1.

You might also encounter <= (less than or equal to) or != (not equal to). However, the CPU doesn't have the bandwidth to tell you what all the registers are named, and leaves that to you to determine.

What is the largest value in any register after completing the instructions in your puzzle input?

Your puzzle answer was 3089.

--- Part Two ---
To be safe, the CPU also needs to know the highest value held in any register during this process so that it can decide how much memory to allocate to these operations. For example, in the above instructions, the highest value ever held was 10 (in register c after the third instruction was evaluated).

Your puzzle answer was 5391.
*/
#include "advent.h"

typedef struct Register {
	char name[5];
	int val;
} Register;

static char **in;
static Register *regs;
static int cntReg = 0, max2 = -999999999, lines = 0;


static int getInput(char *f) {

	char * line = NULL;
    size_t l = 0;

    regs = NULL;
    in = NULL;
	lines = 0;
	cntReg = 0;

	FILE *file=fopen(f, "r");
	if(file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return 0;
	}
	
	while (getline(&line, &l, file) != -1) {
        in = (char**)realloc(in, ++lines * sizeof(char*));
        in[lines-1] = (char*)malloc((strlen(line) + 1) * sizeof(char));
        strcpy(in[lines-1],line);  
    }
   
	fclose(file);
    free(line);
	return 1;

}

static int getReg(char *reg){
	for(int i = 0; i < cntReg; i++)
		if(!strcmp(regs[i].name,reg)) 
			return regs[i].val;	// found -> return	
	regs = (Register*)realloc(regs, ++cntReg * sizeof(Register));
	strcpy(regs[cntReg-1].name,reg);
	regs[cntReg-1].val = 0;
	return 0;
}

static int setReg(char *reg, char *crement, int val){
	for(int i = 0; i < cntReg; i++) {
		if(!strcmp(regs[i].name,reg))
			if(!strcmp(crement,"inc"))	
				regs[i].val += val;
			else
				regs[i].val -= val;
		if(regs[i].val > max2)
			max2 = regs[i].val;
	}
}

void parseInstructions() {

	for(int i = 0; i < lines; i++) {

		char *dest = strtok(in[i], " ");
		char *crement = strtok(NULL, " ");
		char *value = strtok(NULL, " ");
		char *iff = strtok(NULL, " ");
		char *source = strtok(NULL, " ");
		char *op = strtok(NULL, " ");
		char *compare = strtok(NULL, " ");

		getReg(dest);
		int val = toI(value);
		int src = getReg(source);
		int comp = toI(compare);
		int res = 0;

		if(strlen(op) == 1) {
			if(op[0] == '>')
				res = src > comp;
			if(op[0] == '<')
				res = src < comp;
		}
		else {
			switch(op[0]) {
				case '>': res = src >= comp; break;
				case '<': res = src <= comp; break;
				case '=': res = src == comp; break;
				case '!': res = src != comp; break;
			}
		}
		if(res)
			setReg(dest, crement, val);
	}
}

void get8a(char *f) {

	if(!getInput(f))
		return;
	
	int max = 0;

	parseInstructions();

	for(int i = 0; i < cntReg; i++)
		if(regs[i].val > max)
			max = regs[i].val;

	free(regs);
	for(int i = 0; i < lines; i++) 
    	free(in[i]);
    free(in);

	printf("8a: %d\n", max);

}

void get8b(char *f) {

	if(!getInput(f))
		return;

	parseInstructions();

	free(regs);
	for(int i = 0; i < lines; i++) 
    	free(in[i]);
    free(in);
    

	printf("8b: %d\n\n", max2);
	
}
