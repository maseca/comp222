#include <stdio.h>
#include <stdlib.h>

struct line {
	int tag;
	int* block;
};

typedef struct line line;

int main(void) {
	char s; //selection
	int m, c, b; //memory size, cache size, block size
	int* memory;
	line* cache;
	
	while(1) {
		printf(
			"Cache Memory Allocation and Mapping:\n"
			"------------------------------------\n"
			"a) Enter Parameters\n"
			"b) Access Cache for Read/Write or Data Transfer\n"
			"c) Quit\n"
			"\n"
			"Enter Selection: "
		);
		s = getchar(); getchar(); //flush input buffer

		switch(s) {
			case 'a':
			case 'A':
				printf("Enter Main Memory Size (words): ");
				scanf("%d", &m); getchar();

				memory = malloc(sizeof(int) * m);
				for(int i = 0; i < m; ++i) {
					memory[i] = m - i;
				}

				printf("Enter Cache Size (words): ");
				scanf("%d", &c); getchar();

				printf("Enter Block Size (words/block): ");
				scanf("%d", &b); getchar();

				cache = malloc(sizeof(line) * c / b);
				for(int i = 0; i < c / b; ++i) {
					cache[i].block = malloc(sizeof(int) * b);
					cache[i].tag = -1;
				}

				printf("\n\n");
				break;

			case 'b':
			case 'B':
				printf("\n\n");
				break;

			case 'c':
			case 'C':
				printf("Exiting\n");
				return 0;

			default:
				printf("Invalid Selection\n\n");
				break;
		}
	}
}

