/*
--- Day 19: A Series of Tubes ---
Somehow, a network packet got lost and ended up here. It's trying to follow a routing diagram (your puzzle input), but it's confused about where to go.

Its starting point is just off the top of the diagram. Lines (drawn with |, -, and +) show the path it needs to take, starting by going down onto the only line connected to the top of the diagram. It needs to follow this path until it reaches the end (located somewhere within the diagram) and stop there.

Sometimes, the lines cross over each other; in these cases, it needs to continue going the same direction, and only turn left or right when there's no other option. In addition, someone has left letters on the line; these also don't change its direction, but it can use them to keep track of where it's been. For example:

     |          
     |  +--+    
     A  |  C    
 F---|----E|--+ 
     |  |  |  D 
     +B-+  +--+ 

Given this diagram, the packet needs to take the following path:

Starting at the only line touching the top of the diagram, it must go down, pass through A, and continue onward to the first +.
Travel right, up, and right, passing through B in the process.
Continue down (collecting C), right, and up (collecting D).
Finally, go all the way left through E and stopping at F.
Following the path to the end, the letters it sees on its path are ABCDEF.

The little packet looks up at you, hoping you can help it find the way. What letters will it see (in the order it would see them) if it follows the path? (The routing diagram is very wide; make sure you view it without line wrapping.)

Your puzzle answer was PVBSCMEQHY.

--- Part Two ---
The packet is curious how many steps it needs to go.

For example, using the same routing diagram from the example above...

     |          
     |  +--+    
     A  |  C    
 F---|--|-E---+ 
     |  |  |  D 
     +B-+  +--+ 

...the packet would go:

6 steps down (including the first line at the top of the diagram).
3 steps right.
4 steps up.
3 steps right.
4 steps down.
3 steps right.
2 steps up.
13 steps left (including the F it stops on).
This would result in a total of 38 steps.

How many steps does the packet need to go?

Your puzzle answer was 17736.
*/
#include "advent.h"

static char **in;
static int lines;


enum {UP, DOWN, LEFT, RIGHT};

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
        in = (char**)realloc(in, ++lines * sizeof(char*));
        in[lines-1] = (char*)malloc(strlen(line) + 2);
            strcpy(in[lines-1], line);
    }
   
	fclose(file);
    free(line);
	return 1;

}


static int walkTheLine(int x, int y, int dir, char *out, int writePos) {
    int inc     = (dir == LEFT) || (dir == UP) ? -1 : 1; 
    int plane   = (dir == LEFT) || (dir == RIGHT) ? 1: 0;
    char next   = plane ? in[y][x+inc] : in[y+inc][x];
    int xNext   = plane ? x+inc : x;
    int yNext   = plane ? y : y+inc;
    int steps   = 0;
    
    switch(in[y][x]) {
        case '+': 
            if(plane) {
                if(in[y-1][x] == '|')
                    steps += walkTheLine(x, y-1 , UP, out, writePos);
                else
                    steps += walkTheLine(x, y+1 , DOWN, out, writePos);
            }
            else {
                if(in[y][x-1] == '-')
                    steps += walkTheLine(x-1, y , LEFT, out, writePos);
                else
                    steps += walkTheLine(x+1, y , RIGHT, out, writePos);
            }
            break;

        case '-': 
            if(next == '|')
                steps += walkTheLine(xNext + inc, yNext, dir, out, writePos) + 1;
            else
                steps += walkTheLine(xNext, yNext, dir, out, writePos);
            break;

        case '|': 
             if(next == '-')
                steps += walkTheLine(xNext, yNext + inc, dir, out, writePos) + 1;
            else
                steps += walkTheLine(xNext, yNext, dir, out, writePos);
            break;

        case ' ':
        case '\0':
            return steps;
            break;

        default: 
            out[writePos++] = in[y][x]; 
            if(plane)
                steps += walkTheLine(xNext + inc, yNext, dir, out, writePos++) + 1;
            else
                steps += walkTheLine(xNext, yNext + inc, dir, out, writePos++) + 1;
            break;
    }
    
    return ++steps;
}


void get19a(char *f){

    if(!getInput(f))
        return;

    int pos = 0, dir = DOWN;
    char out[32] = {0};

    while(in[0][pos++] != '|');

    walkTheLine(pos-1, 0, dir, out, 0); 

    for(int i = 0; i < lines; i++)
        free(in[i]);
    free(in);

    printf("19a: %s\n", out);


}


void get19b(char *f){

    if(!getInput(f))
        return;

    int pos = 0, dir = DOWN, steps;
    char out[32] = {0};

    while(in[0][pos++] != '|');

    steps = walkTheLine(pos-1, 0, dir, out, 0); 

    for(int i = 0; i < lines; i++)
        free(in[i]);
    free(in);

    printf("19b: %d\n\n", steps - 1);


}
