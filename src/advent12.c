/*
--- Day 12: Digital Plumber ---
Walking along the memory banks of the stream, you find a small village that is experiencing a little confusion: some programs can't communicate with each other.

Programs in this village communicate using a fixed system of pipes. Messages are passed between programs using these pipes, but most programs aren't connected to each other directly. Instead, programs pass messages between each other until the message reaches the intended recipient.

For some reason, though, some of these messages aren't ever reaching their intended recipient, and the programs suspect that some pipes are missing. They would like you to investigate.

You walk through the village and record the ID of each program and the IDs with which it can communicate directly (your puzzle input). Each program has one or more programs with which it can communicate, and these pipes are bidirectional; if 8 says it can communicate with 11, then 11 will say it can communicate with 8.

You need to figure out how many programs are in the group that contains program ID 0.

For example, suppose you go door-to-door like a travelling salesman and record the following list:

0 <-> 2
1 <-> 1
2 <-> 0, 3, 4
3 <-> 2, 4
4 <-> 2, 3, 6
5 <-> 6
6 <-> 4, 5
In this example, the following programs are in the group that contains program ID 0:

Program 0 by definition.
Program 2, directly connected to program 0.
Program 3 via program 2.
Program 4 via program 2.
Program 5 via programs 6, then 4, then 2.
Program 6 via programs 4, then 2.
Therefore, a total of 6 programs are in this group; all but program 1, which has a pipe that connects it to itself.

How many programs are in the group that contains program ID 0?

Your puzzle answer was 378.

--- Part Two ---
There are more programs than just the ones in the group containing program ID 0. The rest of them have no way of reaching that group, and still might have no way of reaching each other.

A group is a collection of programs that can all communicate via pipes either directly or indirectly. The programs you identified just a moment ago are all part of the same group. Now, they would like you to determine the total number of groups.

In the example above, there were 2 groups: one consisting of programs 0,2,3,4,5,6, and the other consisting solely of program 1.

How many groups are there in total?

Your puzzle answer was 204.
*/

#include "advent.h"

typedef struct Node {
	int name;
	int cnt;
	int *childs;
} Node;

static Node *nodes;
static int  cntN;

static int getInput(char *f) {
	int read, temp, node, cnt;
	char *line = NULL, *li, ch;
	size_t t = 0;

	nodes = NULL;
	cntN = 0;

	FILE *file = fopen(f, "r");
	if(file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return 0;
	}
	
	while (getline(&line, &t, file) != -1) {

		if(line[strlen(line)-1] != '\n')
			strcat(line,"\n");
		li = line;
		cnt = 0;

		nodes = (Node*)realloc(nodes, ++cntN * sizeof(Node));
	    sscanf(li,"%d%*s%n", &nodes[cntN-1].name, &read);
	    li += read;

	    nodes[cntN-1].childs = NULL;

	    while(2 == sscanf(li," %d%c%n", &temp, &ch, &read)){
	        li += read;
	        nodes[cntN-1].childs = (int*)realloc(nodes[cntN-1].childs,++cnt*sizeof(int));
	        nodes[cntN-1].childs[cnt-1] = temp;
	    }

	    nodes[cntN-1].cnt = cnt;

	    free(line);
	    line = NULL;

	}
	
	fclose(file);
	return 1;
}

static int DFS(int x, int *visit) {
	static int cnt;

	if(visit[x])
		return 0;

	cnt++;
	visit[x] = 1;

	for(int i = 0; i < nodes[x].cnt; i++)
		if(!visit[nodes[x].childs[i]])
			DFS(nodes[x].childs[i], visit);

	return cnt;
}


static int solve(int choose, char *f) {

	if(!getInput(f))
		return 0;

	int visit[cntN], groups = 0;

	for(int i = 0; i < cntN; i++)
		visit[i] = 0;

	if(choose)
		for(int i = 0; i < cntN; i++)
			if(DFS(i, visit))
				groups++;

	
	groups = choose ? groups : DFS(0, visit);

	for(int i = 0; i < cntN; i++)
		free(nodes[i].childs);
	free(nodes);

	return groups;
}


void get12a(char *f) {
	printf("12a: %d\n", solve(0, f));
}

void get12b(char *f) {
	printf("12b: %d\n\n", solve(1, f));
}
