/*
--- Day 23: Coprocessor Conflagration ---
You decide to head directly to the CPU and fix the printer from there. As you get close, you find an experimental coprocessor doing so much work that the local programs are afraid it will halt and catch fire. This would cause serious issues for the rest of the computer, so you head in and see what you can do.

The code it's running seems to be a variant of the kind you saw recently on that tablet. The general functionality seems very similar, but some of the instructions are different:

set X Y sets register X to the value of Y.
sub X Y decreases register X by the value of Y.
mul X Y sets register X to the result of multiplying the value contained in register X by the value of Y.
jnz X Y jumps with an offset of the value of Y, but only if the value of X is not zero. (An offset of 2 skips the next instruction, an offset of -1 jumps to the previous instruction, and so on.)
Only the instructions listed above are used. The eight registers here, named a through h, all start at 0.

The coprocessor is currently set to some kind of debug mode, which allows for testing, but prevents it from doing any meaningful work.

If you run the program (your puzzle input), how many times is the mul instruction invoked?

Your puzzle answer was 3969.

--- Part Two ---
Now, it's time to fix the problem.

The debug mode switch is wired directly to register a. You flip the switch, which makes register a now start at 1 when the program is executed.

Immediately, the coprocessor begins to overheat. Whoever wrote this program obviously didn't choose a very efficient implementation. You'll need to optimize the program if it has any hope of completing before Santa needs that printer working.

The coprocessor's ultimate goal is to determine the final value left in register h once the program completes. Technically, if it had that... it wouldn't even need to run the program.

After setting register a to 1, if the program were to run to completion, what value would be left in register h?

Your puzzle answer was 917.
*/
#include "advent.h"

typedef struct Instruction {
	char name[5];
	int a;
	int regA;
	int b; 
	int regB;
} Instruction;

static Instruction *in;
static int lines, regs[8];


static int getInput(char *f) {

	char * line = NULL;
    size_t l = 0;

    for(int i = 0; i < 8; i++)
        regs[i] = 0;
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


static int execCMD(int line, int *cnt) {
    int a, b;
    switch(in[line].name[0]) {
        case 'j': 
            a = in[line].regA ? regs[in[line].a] : in[line].a; 
            b = in[line].regB ? regs[in[line].b] : in[line].b; 
            if(a) return b + line ; 
            break;
        case 'm': 
            b = in[line].regB ? regs[in[line].b] : in[line].b;
            regs[in[line].a] *= b;
            *cnt += 1;
            break;
        case 's': 
            b = in[line].regB ? regs[in[line].b] : in[line].b;
            if(in[line].name[1] == 'e')
                regs[in[line].a] = b;
            else
                regs[in[line].a] -= b;
            break;
    }
    return line+1;
}


static int prime(int n) {
    for(int i = 2; i <= n/2; ++i)
        if(n % i == 0)
            return 1;
    return 0;
}


void get23a(char *f) {

    if(!getInput(f))
        return;

    int line = 0, cnt = 0;

    while(line >= 0 && line < lines)
        line = execCMD(line, &cnt);
        
    printf("23a: %d\n", cnt);
}


void get23b(char *f) {

    if(!getInput(f))
        return;

    int line = 0, cnt = 0;

    regs[0] = 1;

    while(line < 8) 
        line = execCMD(line, &cnt);
    
    cnt = 0;

    for(int i = regs[1]; i <= regs[2]; i+=17) 
        cnt += prime(i);
    
    printf("23b: %d\n\n", cnt);
}
