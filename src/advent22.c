/*
--- Day 22: Sporifica Virus ---
Diagnostics indicate that the local grid computing cluster has been contaminated with the Sporifica Virus. The grid computing cluster is a seemingly-infinite two-dimensional grid of compute nodes. Each node is either clean or infected by the virus.

To prevent overloading the nodes (which would render them useless to the virus) or detection by system administrators, exactly one virus carrier moves through the network, infecting or cleaning nodes as it moves. The virus carrier is always located on a single node in the network (the current node) and keeps track of the direction it is facing.

To avoid detection, the virus carrier works in bursts; in each burst, it wakes up, does some work, and goes back to sleep. The following steps are all executed in order one time each burst:

If the current node is infected, it turns to its right. Otherwise, it turns to its left. (Turning is done in-place; the current node does not change.)
If the current node is clean, it becomes infected. Otherwise, it becomes cleaned. (This is done after the node is considered for the purposes of changing direction.)
The virus carrier moves forward one node in the direction it is facing.
Diagnostics have also provided a map of the node infection status (your puzzle input). Clean nodes are shown as .; infected nodes are shown as #. This map only shows the center of the grid; there are many more nodes beyond those shown, but none of them are currently infected.

The virus carrier begins in the middle of the map facing up.

For example, suppose you are given a map like this:

..#
#..
...
Then, the middle of the infinite grid looks like this, with the virus carrier's position marked with [ ]:

. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . # . . .
. . . #[.]. . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
The virus carrier is on a clean node, so it turns left, infects the node, and moves left:

. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . # . . .
. . .[#]# . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
The virus carrier is on an infected node, so it turns right, cleans the node, and moves up:

. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . .[.]. # . . .
. . . . # . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
Four times in a row, the virus carrier finds a clean, infects it, turns left, and moves forward, ending in the same place and still facing up:

. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . #[#]. # . . .
. . # # # . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
Now on the same node as before, it sees an infection, which causes it to turn right, clean the node, and move forward:

. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . # .[.]# . . .
. . # # # . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
After the above actions, a total of 7 bursts of activity had taken place. Of them, 5 bursts of activity caused an infection.

After a total of 70, the grid looks like this, with the virus carrier facing up:

. . . . . # # . .
. . . . # . . # .
. . . # . . . . #
. . # . #[.]. . #
. . # . # . . # .
. . . . . # # . .
. . . . . . . . .
. . . . . . . . .
By this time, 41 bursts of activity caused an infection (though most of those nodes have since been cleaned).

After a total of 10000 bursts of activity, 5587 bursts will have caused an infection.

Given your actual map, after 10000 bursts of activity, how many bursts cause a node to become infected? (Do not count nodes that begin infected.)

Your puzzle answer was 5460.

--- Part Two ---
As you go to remove the virus from the infected nodes, it evolves to resist your attempt.

Now, before it infects a clean node, it will weaken it to disable your defenses. If it encounters an infected node, it will instead flag the node to be cleaned in the future. So:

Clean nodes become weakened.
Weakened nodes become infected.
Infected nodes become flagged.
Flagged nodes become clean.
Every node is always in exactly one of the above states.

The virus carrier still functions in a similar way, but now uses the following logic during its bursts of action:

Decide which way to turn based on the current node:
If it is clean, it turns left.
If it is weakened, it does not turn, and will continue moving in the same direction.
If it is infected, it turns right.
If it is flagged, it reverses direction, and will go back the way it came.
Modify the state of the current node, as described above.
The virus carrier moves forward one node in the direction it is facing.
Start with the same map (still using . for clean and # for infected) and still with the virus carrier starting in the middle and facing up.

Using the same initial state as the previous example, and drawing weakened as W and flagged as F, the middle of the infinite grid looks like this, with the virus carrier's position again marked with [ ]:

. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . # . . .
. . . #[.]. . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
This is the same as before, since no initial nodes are weakened or flagged. The virus carrier is on a clean node, so it still turns left, instead weakens the node, and moves left:

. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . # . . .
. . .[#]W . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
The virus carrier is on an infected node, so it still turns right, instead flags the node, and moves up:

. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . .[.]. # . . .
. . . F W . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
This process repeats three more times, ending on the previously-flagged node and facing right:

. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . W W . # . . .
. . W[F]W . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
Finding a flagged node, it reverses direction and cleans the node:

. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . W W . # . . .
. .[W]. W . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
The weakened node becomes infected, and it continues in the same direction:

. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . W W . # . . .
.[.]# . W . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
Of the first 100 bursts, 26 will result in infection. Unfortunately, another feature of this evolved virus is speed; of the first 10000000 bursts, 2511944 will result in infection.

Given your actual map, after 10000000 bursts of activity, how many bursts cause a node to become infected? (Do not count nodes that begin infected.)

Your puzzle answer was 2511702.
*/
#include "advent.h"

enum {UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3};
static int **map, lines, cols;


static int getInput(char *f) {

	char * line = NULL;
    size_t l = 0;

	lines = 0; 
	cols = 0;   
    map = NULL;

	FILE *file=fopen(f, "r");
	if(file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return 0;
	}
	
	while (getline(&line, &l, file) != -1) {
		map = (int**)realloc(map, ++lines * sizeof(int*));
		cols = strlen(line);
		if(line[cols-1] == '\n') cols--;
		map[lines-1] = (int*)malloc(cols * sizeof(int));
		for(int i = 0; i < cols; i++) {
			if(line[i] == '.')
				map[lines-1][i] = 0;
			else
				map[lines-1][i] = 1;
		}
	
    }
   
	fclose(file);
    free(line);
	return 1;

}


static void resize(int x, int y) {
	if(y == lines) {
		map = (int**)realloc(map, ++lines * sizeof(int*));
		map[lines-1] = (int*)malloc(cols * sizeof(int));
		for(int i = 0; i < cols; i++)
			map[lines-1][i] = 0;
	}
	else if(y < 0) {
		map = (int**)realloc(map, ++lines * sizeof(int*));
		map[lines-1] = (int*)malloc(cols * sizeof(int));
		for(int i = lines-1; i > 0 ; i--)
			memcpy(map[i], map[i-1], cols * sizeof(int));
		for(int i = 0; i < cols; i++)
			map[0][i] = 0;
	}
	else if(x < 0) {
		for(int i = 0; i < lines; i++) {
			map[i] = (int*)realloc(map[i], (cols + 1) * sizeof(int));
			int tmp[cols];
			memcpy(tmp, map[i], cols * sizeof(int));
			memcpy(map[i]+1, tmp, cols * sizeof(int));
			map[i][0] = 0;
		}
		cols++;
	}
	else if(x == cols) {
		for(int i = 0; i < lines; i++) {
			map[i] = (int*)realloc(map[i], (cols + 1) * sizeof(int));
			map[i][cols] = 0;
		}
		cols++;
	}
}


static int calcNodeB(int x, int y, int dir, int infected) {
	static int cnt = 0;
	if(++cnt > 10000000)
		return infected;

	if(map[y][x] == 1)
		dir++;
	else if(map[y][x] == 0)
		dir--;
	else if(map[y][x] == 3)
		dir += 2;

	if(dir < 0)
		dir = 3;
	else if(dir == 4)
		dir = 0;
	else if(dir == 5)
		dir = 1;

	if(map[y][x] == 0)
		map[y][x] = 2;
	else if(map[y][x] == 2) {
		map[y][x] = 1;
		infected++;
	}
	else if(map[y][x] == 1)
		map[y][x] = 3;
	else
		map[y][x] = 0;

	int newX = x, newY = y;

	if(dir == LEFT)
		newX--;
	else if(dir == RIGHT)
		newX++;
	else if (dir== UP)
		newY--;
	else
		newY++;

	resize(newX, newY);

	if(newX < 0)
		newX = 0;
	else if(newY < 0)
		newY = 0;

	infected = calcNodeB(newX, newY, dir, infected);
	return infected;
}


static int calcNodeA(int x, int y, int dir, int infected) {
	static int cnt = 0;
	if(++cnt > 10000)
		return infected;

	if(map[y][x] == 1)
		dir++;
	else
		dir--;

	if(dir < 0)
		dir = 3;
	else if(dir > 3)
		dir = 0;

	if(map[y][x] == 0) infected++;
	map[y][x] = !map[y][x];

	int newX = x, newY = y;

	if(dir == LEFT)
		newX--;
	else if(dir == RIGHT)
		newX++;
	else if (dir== UP)
		newY--;
	else
		newY++;

	resize(newX, newY);

	if(newX < 0)
		newX = 0;
	else if(newY < 0)
		newY = 0;

	infected = calcNodeA(newX, newY, dir, infected);
	return infected;
}


void get22a(char *f) {

	if(!getInput(f))
		return;

	int cnt = calcNodeA(cols/2, lines/2, UP, 0);

	for(int i = 0; i < lines; i++)
		free(map[i]);
	free(map);

	printf("22a: %d\n", cnt);
}


void get22b(char *f) {

	if(!getInput(f))
		return;

	int cnt = calcNodeB(cols/2, lines/2, UP, 0);

	for(int i = 0; i < lines; i++)
		free(map[i]);
	free(map);

	printf("22b: %d\n\n", cnt);
}
