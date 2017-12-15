/*
--- Day 7: Recursive Circus ---
Wandering further through the circuits of the computer, you come upon a tower of programs that have gotten themselves into a bit of trouble. A recursive algorithm has gotten out of hand, and now they're balanced precariously in a large tower.

One program at the bottom supports the entire tower. It's holding a large disc, and on the disc are balanced several more sub-towers. At the bottom of these sub-towers, standing on the bottom disc, are other programs, each holding their own disc, and so on. At the very tops of these sub-sub-sub-...-towers, many programs stand simply keeping the disc below them balanced but with no disc of their own.

You offer to help, but first you need to understand the structure of these towers. You ask each program to yell out their name, their weight, and (if they're holding a disc) the names of the programs immediately above them balancing on that disc. You write this information down (your puzzle input). Unfortunately, in their panic, they don't do this in an orderly fashion; by the time you're done, you're not sure which program gave which information.

For example, if your list is the following:

pbga (66)
xhth (57)
ebii (61)
havc (66)
ktlj (57)
fwft (72) -> ktlj, cntj, xhth
qoyq (66)
padx (45) -> pbga, havc, qoyq
tknk (41) -> ugml, padx, fwft
jptl (61)
ugml (68) -> gyxo, ebii, jptl
gyxo (61)
cntj (57)
...then you would be able to recreate the structure of the towers that looks like this:

                gyxo
              /     
         ugml - ebii
       /      \     
      |         jptl
      |        
      |         pbga
     /        /
tknk --- padx - havc
     \        \
      |         qoyq
      |             
      |         ktlj
       \      /     
         fwft - cntj
              \     
                xhth
In this example, tknk is at the bottom of the tower (the bottom program), and is holding up ugml, padx, and fwft. Those programs are, in turn, holding up other programs; in this example, none of those programs are holding up any other programs, and are all the tops of their own towers. (The actual tower balancing in front of you is much larger.)

Before you're ready to help them, you need to make sure your information is correct. What is the name of the bottom program?

Your puzzle answer was hlhomy.

--- Part Two ---
The programs explain the situation: they can't get down. Rather, they could get down, if they weren't expending all of their energy trying to keep the tower balanced. Apparently, one program has the wrong weight, and until it's fixed, they're stuck here.

For any program holding a disc, each program standing on that disc forms a sub-tower. Each of those sub-towers are supposed to be the same weight, or the disc itself isn't balanced. The weight of a tower is the sum of the weights of the programs in that tower.

In the example above, this means that for ugml's disc to be balanced, gyxo, ebii, and jptl must all have the same weight, and they do: 61.

However, for tknk to be balanced, each of the programs standing on its disc and all programs above it must each match. This means that the following sums must all be the same:

ugml + (gyxo + ebii + jptl) = 68 + (61 + 61 + 61) = 251
padx + (pbga + havc + qoyq) = 45 + (66 + 66 + 66) = 243
fwft + (ktlj + cntj + xhth) = 72 + (57 + 57 + 57) = 243
As you can see, tknk's disc is unbalanced: ugml's stack is heavier than the other two. Even though the nodes above ugml are balanced, ugml itself is too heavy: it needs to be 8 units lighter for its stack to weigh 243 and keep the towers balanced. If this change were made, its weight would be 60.

Given that exactly one program is the wrong weight, what would its weight need to be to balance the entire tower?

Your puzzle answer was 1505.
*/
#include "advent.h"

typedef struct  Node{
	char *name;
	int weight;
	int *children;
	int cntC;
} Node;

static Node *nodes;
static int cntN;


static int nodeIndex(char *s) {
	for(int i = 0; i < cntN; i++) {
		if(!strcmp(nodes[i].name, s)) {
			return i;
		}
	}
	return -1;
}


static int getInput(char *f) {

	char * line = NULL;
    size_t l = 0;

    nodes = NULL;
    cntN = 0;

	FILE *file=fopen(f, "r");
	if(file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return 0;
	}
	while (getline(&line, &l, file) != -1) {
        char *ptr = strtok(line, " ")  ;
        int index = nodeIndex(ptr);
        if(index == -1) {
	        nodes = (Node*)realloc(nodes, ++cntN * sizeof(Node));
	        index = cntN - 1;
	        nodes[index].name = (char*)malloc(strlen(ptr)+1);
	        strcpy(nodes[index].name,ptr);
	        nodes[index].children = NULL;
	        nodes[index].cntC = 0;
	    }
	    
        ptr = strtok(NULL, ")");
        nodes[index].weight = toI(ptr+1);

        ptr = strtok(NULL, ">");
		ptr = strtok(NULL, ">");

		if(ptr) {
			int cntC = 0, indexC = -1;
			char *pt = strtok(ptr+1," ");

			while(pt) {
				if(pt[strlen(pt)-1] == ',' || pt[strlen(pt)-1] == '\n')
					pt[strlen(pt)-1] = '\0';
				int indexC = nodeIndex(pt);
				if(indexC == -1) {
					nodes = (Node*)realloc(nodes, ++cntN * sizeof(Node));
					indexC = cntN - 1;
			        nodes[indexC].name = (char*)malloc(strlen(pt)+1);
			        strcpy(nodes[indexC].name,pt);
			        nodes[indexC].children = NULL;
			        nodes[indexC].cntC = 0;
			    }
				
				nodes[index].children = (int*)realloc(nodes[index].children, ++cntC * sizeof(int));
				nodes[index].children[cntC-1] = indexC;

				pt = strtok(NULL, " ");
			}
			nodes[index].cntC = cntC;
		}
    }
   
	fclose(file);
    free(line);
	return 1;
}


static void findRoot(char *s, int *index) {

	int noChild = 0;

	for(int i = 0; i < cntN && noChild == 0; i++) {
		noChild = 1;
		for(int j = 0; j < cntN && noChild == 1; j++)
			for(int k = 0; k < nodes[j].cntC && noChild == 1; k++)
				if(!strcmp(nodes[i].name, nodes[nodes[j].children[k]].name))
					noChild = 0;

		if(noChild) {
			strcpy(s, nodes[i].name);
			*index = i;
		}
	}
}


static int DFS(int root) {
	int exp = -1;
	int weightsCC[nodes[root].cntC];
	int s = nodes[root].weight;
	int w = 0;
	for(int i = 0; i < nodes[root].cntC; i++) {
		w = DFS(nodes[root].children[i]);
		s += w;
		weightsCC[i] = w + nodes[root].weight;
	}
	for(int i = 1; i < nodes[root].cntC; i++) {
		if(i == 1 && weightsCC[i-1] != weightsCC[i] && weightsCC[i+1] == weightsCC[i]) {
			int diff = weightsCC[i-1] - weightsCC[i];
			int childW = nodes[nodes[root].children[i-1]].weight;
			//printf("%s (%d) is %d off. Should have %d \n", nodes[nodes[root].children[i-1]].name, childW, diff, childW -  diff );
			printf("7b: %d\n\n", childW - diff);
			return s - diff;
		}
		else if( (i == nodes[root].cntC - 1 && weightsCC[i-1] != weightsCC[i]) ||
				 (weightsCC[i-1] != weightsCC[i] && weightsCC[i+1] != weightsCC[i]) ) {
			int diff = weightsCC[i] - weightsCC[i-1];
			int childW = nodes[nodes[root].children[i]].weight;
			//printf("%s (%d) is %d off. Should have %d \n", nodes[nodes[root].children[i]].name, childW, diff, childW -  diff );
			printf("7b: %d\n\n", childW - diff);
			return s - diff;
		}
	}

	return s;
}


static int solve(int choose, char *f) {

	if(!getInput(f))
		return 0;

	char res[32];
	int index;

	findRoot(res, &index);

	if(choose)
		DFS(index);
	else
		printf("7a: %s\n", res);

	for(int i = 0; i < cntN; i++) {
		free(nodes[i].name);
		free(nodes[i].children);
	}
	free(nodes);
}


void get7a(char *f) {
	solve(0, f);
}


void get7b(char *f) {
	solve(1, f);
}

