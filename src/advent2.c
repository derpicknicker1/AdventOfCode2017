/*
--- Day 2: Corruption Checksum ---
As you walk through the door, a glowing humanoid shape yells in your direction. "You there! Your state appears to be idle. Come help us repair the corruption in this spreadsheet - if we take another millisecond, we'll have to display an hourglass cursor!"

The spreadsheet consists of rows of apparently-random numbers. To make sure the recovery process is on the right track, they need you to calculate the spreadsheet's checksum. For each row, determine the difference between the largest value and the smallest value; the checksum is the sum of all of these differences.

For example, given the following spreadsheet:

5 1 9 5
7 5 3
2 4 6 8
The first row's largest and smallest values are 9 and 1, and their difference is 8.
The second row's largest and smallest values are 7 and 3, and their difference is 4.
The third row's difference is 6.
In this example, the spreadsheet's checksum would be 8 + 4 + 6 = 18.

What is the checksum for the spreadsheet in your puzzle input?

Your puzzle answer was 54426.

--- Part Two ---
"Great work; looks like we're on the right track after all. Here's a star for your effort." However, the program seems a little worried. Can programs be worried?

"Based on what we're seeing, it looks like all the User wanted is some information about the evenly divisible values in the spreadsheet. Unfortunately, none of us are equipped for that kind of calculation - most of us specialize in bitwise operations."

It sounds like the goal is to find the only two numbers in each row where one evenly divides the other - that is, where the result of the division operation is a whole number. They would like you to find those numbers on each line, divide them, and add up each line's result.

For example, given the following spreadsheet:

5 9 2 8
9 4 7 3
3 8 6 5
In the first row, the only two numbers that evenly divide are 8 and 2; the result of this division is 4.
In the second row, the two numbers are 9 and 3; the result is 3.
In the third row, the result is 2.
In this example, the sum of the results would be 4 + 3 + 2 = 9.

What is the sum of each row's result in your puzzle input?

Your puzzle answer was 333.
*/

#include "advent.h"

static int **input;
static int H = 0, W = 0;


static int getInput(char *f) {
	char * line = NULL;
    size_t len = 0;

	input = NULL; 
	H = W = 0;

	FILE *file=fopen(f, "r");
	if(file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return 0;
	}
	
	while (getline(&line, &len, file) != -1) {

        input = (int**)realloc(input, ++H * sizeof(int*));
        input[H-1] = NULL;

        int cnt = 0;
        char *ptr = strtok(line, "\t");
        
        while(ptr) {
        	input[H-1] = (int*)realloc(input[H-1], ++cnt * sizeof(int));
        	input[H-1][cnt-1] =  toI(ptr);
        	ptr = strtok(NULL, "\t");
        }
       
        if(cnt > W)
        	W = cnt;
    }

    for(int i = 0; i < H; i++)
    	input[i] = (int*)realloc(input[i], W * sizeof(int));

	fclose(file);
    free(line);
	return 1;
}

void get2a(char *f) {

	if(!getInput(f))
		return;

	int sum = 0;

	for(int y = 0;y<H;y++) {

		int min = 100000000, max = 0;

		for(int x = 0;x<W;x++) {

			if(input[y][x] > max)
				max = input[y][x];

			if(input[y][x] < min)
				min = input[y][x];
		}

		sum += max-min;	
	}
	
	for(int i = 0; i < H; i++)
    	free(input[i]);
	free(input);

	printf("2a: %d\n",sum);
}

void get2b(char *f) {
	
	if(!getInput(f))
		return;

	int sum = 0;

	for(int y = 0;y<H;y++)

		for(int x = 0;x<W-1;x++)

			for(int i = x+1; i < W; i++) {

				if(input[y][x] % input[y][i] == 0) {
					sum += input[y][x] / input[y][i];
					break;
				}
				
				if(input[y][i] % input[y][x] == 0) {
					sum += input[y][i] / input[y][x];
					break;
				}
			}

	for(int i = 0; i < H; i++)
    	free(input[i]);
	free(input);

	printf("2b: %d\n\n",sum);
}