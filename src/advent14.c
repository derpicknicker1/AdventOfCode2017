/*
--- Day 14: Disk Defragmentation ---
Suddenly, a scheduled job activates the system's disk defragmenter. Were the situation different, you might sit and watch it for a while, but today, you just don't have that kind of time. It's soaking up valuable system resources that are needed elsewhere, and so the only option is to help it finish its task as soon as possible.

The disk in question consists of a 128x128 grid; each square of the grid is either free or used. On this disk, the state of the grid is tracked by the bits in a sequence of knot hashes.

A total of 128 knot hashes are calculated, each corresponding to a single row in the grid; each hash contains 128 bits which correspond to individual grid squares. Each bit of a hash indicates whether that square is free (0) or used (1).

The hash inputs are a key string (your puzzle input), a dash, and a number from 0 to 127 corresponding to the row. For example, if your key string were flqrgnkx, then the first row would be given by the bits of the knot hash of flqrgnkx-0, the second row from the bits of the knot hash of flqrgnkx-1, and so on until the last row, flqrgnkx-127.

The output of a knot hash is traditionally represented by 32 hexadecimal digits; each of these digits correspond to 4 bits, for a total of 4 * 32 = 128 bits. To convert to bits, turn each hexadecimal digit to its equivalent binary value, high-bit first: 0 becomes 0000, 1 becomes 0001, e becomes 1110, f becomes 1111, and so on; a hash that begins with a0c2017... in hexadecimal would begin with 10100000110000100000000101110000... in binary.

Continuing this process, the first 8 rows and columns for key flqrgnkx appear as follows, using # to denote used squares, and . to denote free ones:

##.#.#..-->
.#.#.#.#   
....#.#.   
#.#.##.#   
.##.#...   
##..#..#   
.#...#..   
##.#.##.-->
|      |   
V      V   
In this example, 8108 squares are used across the entire 128x128 grid.

Given your actual key string, how many squares are used?

Your puzzle answer was 8074.

--- Part Two ---
Now, all the defragmenter needs to know is the number of regions. A region is a group of used squares that are all adjacent, not including diagonals. Every used square is in exactly one region: lone used squares form their own isolated regions, while several adjacent squares all count as a single region.

In the example above, the following nine regions are visible, each marked with a distinct digit:

11.2.3..-->
.1.2.3.4   
....5.6.   
7.8.55.9   
.88.5...   
88..5..8   
.8...8..   
88.8.88.-->
|      |   
V      V   
Of particular interest is the region marked 8; while it does not appear contiguous in this small view, all of the squares marked 8 are connected when considering the whole 128x128 grid. In total, in this example, 1242 regions are present.

How many regions are present given your key string?

Your puzzle answer was 1212.
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

void getHash(char *in, int* out) {

	int row[256], *length, skip = 0, pos = 0, len = strlen(in);


	for(int i = 0; i < 256; i++)
		row[i] = i;
	
	
	length = (int*)malloc(len  * sizeof(int));
		for(int i = 0; i < strlen(in); i++)
			length[i] = in[i];

	for(int x = 0; x < 64; x++) {
		for(int i = 0; i < len; i++) {

			for( int j = length[i], k = 0; j > 1; j-=2, k++) {
				int begin = pos+k;
				int end = pos+length[i]-k-1;
				if(begin >= 256) 
					begin = begin - (256*(begin/256));
				if(end >= 256)
					end = end - (256*(end/256));
				int tmp = row[begin];
				row[begin] = row[end];
				row[end] = tmp;
			}
			pos += length[i] + skip++;
			if(pos >= 256)
				pos = abs(256 - pos);
		}
	}

	free(length);
	
	for(int i = 0; i < 16; i++) {
		out[i] = row[0+i*16] ^ row[1+i*16] ^ row[2+i*16] ^ row[3+i*16] ^ row[4+i*16] ^ row[5+i*16] ^ row[6+i*16] ^ row[7+i*16] ^ row[8+i*16] ^ row[9+i*16] ^ row[10+i*16] ^ row[11+i*16] ^ row[12+i*16] ^ row[13+i*16] ^ row[14+i*16] ^ row[15+i*16];
	}
}

static void markPos(int *map, int x, int y, int cnt) {
	map[y*128+x] = cnt;
	if(x-1 >= 0 && map[y*128 + (x-1)] == 0) 
			markPos(map, x-1, y, cnt);
	if(x+1 < 128 && map[y*128 + (x+1)] == 0) 
			markPos(map, x+1, y, cnt);
	if(y-1 >= 0 && map[(y-1)*128 + x] == 0) 
			markPos(map, x, y-1, cnt);
	if(y+1 < 128 && map[(y+1)*128 + x] == 0) 
			markPos(map, x, y+1, cnt);
}

void get14a(char *f) {

	if(!getInput(f))
		return;

	char key[18];
	int hash[16], cnt = 0;

	for(int i = 0; i < 128; i++) {
		sprintf(key,"%s-%d%c%cI/%c", input, i, 17,31,23);
		getHash(key, hash);
		for(int j = 0; j < 16; j++)
			cnt += __builtin_popcount (hash[j]);
			//do cnt += hash[j] & 1 ? 1 : 0; while(hash[j] >>= 1); 
	}

	free(input);
	input = NULL;

	printf("14a: %d\n", cnt);

}

void get14b(char *f) {

	if(!getInput(f))
		return;

	char key[18];
	int hash[16], map[128][128], cnt = 0;

	for(int i = 0; i < 128; i++) {
		sprintf(key,"%s-%d%c%cI/%c", input, i, 17,31,23);
		getHash(key, hash);
		for(int j = 0; j < 16; j++) {
			for(int k = 7; k >= 0; k--) {
				 map[i][j*8+k] = hash[j] & 1 ? 0 : -1;
				 hash[j] >>= 1 ;
			}
		}
	}

	for(int i = 0; i < 128; i++)
		for(int j = 0; j < 128; j++) 
			if(map[i][j] == 0)
				markPos((int*)map, j, i, ++cnt);

	free(input);
	input = NULL;

	printf("14b: %d\n\n", cnt);

}
