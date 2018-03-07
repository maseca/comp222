/*
 * Maxwell Plotkin
 * COMP222 Spring 2018
 * Assignment 2
 */
#include <stdio.h>
#include <stdlib.h>

struct line {
	int tag;
	int* block;
};

typedef struct line line;

void parse_adr(int* mem_adr, int* tag, int* block, int* word, int* c_s, int* b_s) {
	*tag = *mem_adr / *c_s;
	*block = (*mem_adr % *c_s) / *b_s;
	*word = *mem_adr % *b_s;
}

void print_data(line* cache, int* tag, int* block, int* word) {
	printf("| Tag: %d\t| Block: %d\t| Word: %d (%d)\n", *tag, *block, *word, cache[*block].block[*word]);
}

int main(void) {
	char s; //selection
	int ms, cs, bs, ma, t, b, w, v, i; 
	//memory size, cache size, block size, MM address, tag, block, word, value
	ms = 0;
	int* m; //memory
	line* c; //cache
	
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
				do {
					printf("Enter Main Memory Size (words): ");
					scanf("%d", &ms); getchar();

					if(ms <= 0)
						printf("Please enter positive number.\n");
				} while(ms <= 0);

				m = malloc(sizeof(int) * ms);
				for(i = 0; i < ms; ++i) {
					m[i] = ms - i;
				}

				do {
					printf("Enter Cache Size (words): ");
					scanf("%d", &cs); getchar();
					if(cs <= 0)
						printf("Please enter positive number.\n");
				} while(cs <= 0);

				do {
				printf("Enter Block Size (words/block): ");
				scanf("%d", &bs); getchar();
					if(bs <= 0)
						printf("Please enter positive number.\n");
				} while(bs <= 0);

				c = malloc(sizeof(line) * cs / bs);
				for(i = 0; i < cs / bs; ++i) {
					c[i].block = NULL;
					c[i].tag = -1;
				}

				printf("\n\n");
				break;

			case 'b':
			case 'B':
				if(!ms) {
					printf("Memory not yet allocated, please select option A to continue.\n\n");
					break;
				}

				printf("(R)ead or (W)rite?: ");
				s = getchar(); getchar();

				switch(s) {
					case 'r':
					case 'R':
						do {
							printf("Enter Memory Address to Read From: ");
							scanf("%d", &ma); getchar();

							if(ma >= ms || ma < 0)
								printf("Invalid Address.\n");
						} while(ma >= ms || ma < 0);

						parse_adr(&ma, &t, &b, &w, &cs, &bs);
						printf("\n");

						if(c[b].tag != t) {
							printf("Cache MISS!:");

							if(c[b].tag == -1) {
								printf(" (Allocating Block...) ");
								c[b].block = malloc(sizeof(int) * bs);
							}

							c[b].tag = t;
							for(i = 0; i < bs; ++i) {
								c[b].block[i] = m[(ma / bs) * bs + i];
							}
						} else {
							printf("Cache HIT!: ");
						}

						print_data(c, &t, &b, &w);
						break;

					case 'w':
					case 'W':
						do {
							printf("Enter Memory Address to Write To: ");
							scanf("%d", &ma); getchar();

							if(ma >= ms || ma < 0)
								printf("Invalid Address.\n");
						} while(ma >= ms || ma < 0);

						printf("Enter Value to Write: ");
						scanf("%d", &v); getchar();

						parse_adr(&ma, &t, &b, &w, &cs, &bs);
						printf("\n");

						if(c[b].tag != t || (c[b].block && c[b].block[w] != v)) {
							printf("Cache MISS! Data written: ");

							if(c[b].tag == -1) {
								printf(" (Allocating Block...) ");
								c[b].block = malloc(sizeof(int) * bs);
							}

							c[b].tag = t;
							m[(ma / bs) * bs + w] = v;

							for(i = 0; i < bs; ++i) {
								c[b].block[i] = m[(ma / bs) * bs + i];
							}
						} else {
							printf("Cache HIT! No changes made: ");
						}

						print_data(c, &t, &b, &w);
						break;
					
					default:
						printf("Invalid Selection.\n");
				}

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
