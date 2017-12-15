#include "advent.h"

#define execute(s) 	get##s##a("input/" #s ".txt"); \
					get##s##b("input/" #s ".txt"); 

int main() {
	
	printf("\n\n### Solutions ###\n\n");

	execute(1)
	execute(2)
	execute(3)
	execute(4)
	execute(5)
	execute(6)
	execute(7)
	execute(8)
	execute(9)
	execute(10)
	execute(11)
	execute(12)
	execute(13)
	execute(14)
	
	return 1;
}