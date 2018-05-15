/*
 * Maxwell Plotkin
 * COMP222 Spring 2018
 * Assignment 5
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct Inst {
	int dst;
	int src1;
	int src2;
	int delay;
} Inst;

int main(void) {
	Inst* sb; //scoreboard
	char s; //selection
	char in[8]; //input string
	int ic = -1; //instruction count
	int d = 0; //delay
	int i, j; //iterators

	while(1) {
		printf(
			"\n\n"
			"Instruction-Level Parallelism\n"
			"------------------------------\n"
			"a) Enter Instructions\n"
			"b) Calculate Cycle Count, 6-Stage Pipeline\n"
			"c) Quit Program\n"
			"\n"
			"Enter Selection: "
		);
		s = getchar(); getchar(); //flush buffer
		printf("\n");

		switch(s) {
			case 'a':
			case 'A':
				do {
					printf("Enter Instruction Count: ");
					scanf("%d", &ic); getchar();  //flush buffer

					if(ic <= 0)
						printf("Invalid Size, please choose a positive integer.\n");
				} while(ic <= 0);

				sb = malloc((ic+1) * sizeof(Inst));
				sb[0] = (Inst) {-1, -1, -1, -1};

				for(i = 1; i < ic+1; ++i) {
					printf("%d) ", i); 
					scanf("%s", in); getchar();
					sb[i] = (Inst) {in[1]-'0', in[4]-'0', in[7]-'0', 0};
				}

				break;
			case 'b':
			case 'B':
				if(ic <= 0) {
					printf("Please enter instructions.");
				} else {
					for(i = 1; i < ic+1; ++i) {
						if(i != 1) {
							if((sb[i].src1 == sb[i-1].dst) || (sb[i].src2 == sb[i-1].dst)) {
								d += 2;
								for(j = i; j < ic+1; ++j)
									sb[j].delay += 2;
							} else if((sb[i].src1 == sb[i-2].dst) || (sb[i].src2 == sb[i-2].dst)) {
								d += sb[i-1].delay > sb[i-2].delay ? 0 : 1;
								for(j = i; j < ic+1; ++j)
									sb[j].delay += sb[i-1].delay > sb[i-2].delay ? 0 : 1;
							}
						}

						printf("%d)", i);

						for(j = 1 - i; j < sb[i].delay; ++j) {
							printf("\t");
						}

						printf("FI\tDI\tCO\tFO\tEI\tWO\n");
					}

					printf("\nTotal Cycles: %d", ic + 5 + d);
				}
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
