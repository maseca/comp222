/*
 * Maxwell Plotkin
 * COMP222 Spring 2018
 * Assignment 3
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct HC {
	char* fs; //fixed str
	int bb; //bad bit 
} HC;

HC check(char* str) {
	HC o = {fs: str, bb: -1}; //output
	//check code, return bad bit and fixed string
	return o;
}

int main(void) {
	int nv, ml, al, i; //not valid, maximum length, actual length
	char s, p; //selection, parity
	char* c; //code str
	HC r; //return value

	nv = ml = al = 0;

	while(1) {
		printf(
			"\n\n"
			"Hamming Code Error Detection/Correction:\n"
			"----------------------------------------\n"
			"a) Enter Parameters\n"
			"b) Check Hamming Code\n"
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
					printf("Enter Maximum Length: ");
					scanf("%d", &ml); getchar();  //flush buffer

					if(ml <= 0)
						printf("Invalid Length, please choose a positive integer.\n");
					else {
						c = (char*)malloc(ml+1);
					}
				} while(ml <= 0);

				do {
					printf("Enter Parity (0 = even, 1 = odd): ");
					p = getchar(); getchar();  //flush buffer

					if(p != '0' && p != '1')
						printf("Invalid Parity, please choose 0 or 1.\n");

				} while(p != '0' && p != '1');

				break;

			case 'b':
			case 'B':
				if(ml == 0) {
					printf("Please enter parameters first.\n");
					break;
				}

				do {
					printf("Enter Hamming Code: ");
					scanf("%s", c); getchar();

					for(i = 0; i < ml+1; ++i) {
						if(i == ml)
							al = i + 1;

						if(c[i] != '0' && c[i] != '1'){
							if(c[i] == '\0') {
								al = i;
								nv = 0;
								break;
							} else {
								nv = 1;
								printf("Invalid Code, please try again.\n");
								break;
							}
						}
					}
				} while(nv);

				printf("Code: %s\n", c);
				r = check(c);

				if(r.bb == -1) {
					printf("No error detected.\n");
					break;
				} else {
					printf("Error at bit: %d\nCode after correction: %s\n", &r.bb, r.fs);
					break;
				}
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
