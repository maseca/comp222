/*
 * Maxwell Plotkin
 * COMP222 Spring 2018
 * Assignment 4
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct Entry {
	int vp; //virtual page
	int pf; //page frame
} Entry;

void print_mapping(Entry* table, int t_size, int v_addr, int policy) {
	int i;

	//TO-DO: print page address

	printf(
		"---------\n"
		"|VP |PF |\n"
	);

	for(i = 0; i < t_size; ++i) {
		printf(
			"---------\n"
			"|%3d|%3d|\n",
			table[i].vp, table[i].pf
		);
	}

	printf(
		"---------\n"
	);
}

int main(void) {
	char s; //selection
	int mm, ps, p, va, ts; //main memory, page size, policy, virtual address, table size
	int i;
	Entry* t; //table

	mm = ps = p = va = -1;

	while(1) {
		printf(
			"\n\n"
			"Virtual-to-Main Memory Mapping:\n"
			"-------------------------------\n"
			"a) Enter Parameters\n"
			"b) Map Virtual Address\n"
			"c) Quit\n"
			"\n"
			"Enter Selection: "
		);
		s = getchar(); getchar(); //flush buffer
		printf("\n");

		switch(s) {
			case 'a':
			case 'A':
				do {
					printf("Enter Main Memory Size (words): ");
					scanf("%d", &mm); getchar();  //flush buffer

					if(mm <= 0)
						printf("Invalid Size, please choose a positive integer.\n");
				} while(mm <= 0);

				do {
					printf("Enter Page Size (words/page): ");
					scanf("%d", &ps); getchar();  //flush buffer

					if(ps <= 0 || ps > mm)
						printf("Invalid Size, please choose a positive integer not greater than main memory size.\n");
				} while(ps <= 0 || ps > mm);

				ts = mm / ps;
				t = (Entry*) malloc(ts * sizeof(Entry));

				for(i = 0; i < ts; ++i) {
					t[i].vp = -1;
					t[i].pf = -1;
				}

				do {
					printf("Enter Replacement Policy (0 = LRU, 1 = FIFO): ");
					scanf("%d", &p); getchar();  //flush buffer

					if(p != 0 && p != 1)
						printf("Invalid Policy, please choose 0 or 1.\n");

				} while(p != 0 && p != 1);

				break;
			case 'b':
			case 'B':
				if(mm < 0) {
					printf("Please enter parameters first.\n");
					break;
				}

				do {
					printf("Enter Virtual Memory Address: ");
					scanf("%d", &va); getchar();

					if(va < 0) 
						printf("Address Invalid, please enter non-negative number.\n");

				} while(va < 0);

				print_mapping(t, ts, va, p);
				break;
			case 'c':
			case 'C':
				printf("Exiting\n");
				return 0;
			default:
				printf("Invalid Selection\n");
				break;
		}
	}
}
