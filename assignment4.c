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

void print_mapping(Entry* table, int t_size, int p_size, int v_addr, int policy) {
	Entry swp;
	int vp = v_addr / p_size; //virtual page
	int pf = table[0].pf;
	int i;

	for(i = 0; i < t_size; ++i) {
		if(table[i].vp == vp) 
			break;
	}

	if(i == t_size) {
		printf("Page fault!\n");

		if(table[t_size-1].vp < 0) {
			for(i = 0; i < t_size; ++i) {
				if(table[i].vp < 0) {
					table[i] = (Entry){vp, i};
					break;
				}
			}
		} else {
			for(i = 0; i < t_size-1; ++i)
				table[i] = table[i+1];
			
			table[t_size-1] = (Entry){vp, pf};
		}
	} else {
		printf(
			"Virtual Address %d => Physical Address %d\n",
			v_addr,
			v_addr + p_size * (table[i].pf - vp)
		);

		if(policy == 0) {//lru reorder
			while(i < t_size-1) {
				swp = table[i];
				table[i] = table[i+1];
				table[i+1] = swp;
				++i;
			}
		}
	}

	printf(
		"---------\n"
		"|VP |PF |\n"
	);

	for(i = 0; i < t_size; ++i) {
		if(table[i].vp >= 0) {
			printf(
				"---------\n"
				"|%3d|%3d|\n",
				table[i].vp, table[i].pf
			);
		}
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
					t[i].pf = i;
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

				print_mapping(t, ts, ps, va, p);
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
