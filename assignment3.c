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

char* strrev(char* str) { //adapted from public domain code by Bob Stout
	char *p1, *p2;

	if (! str || ! *str)
		return str;
	for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2) {
		*p1 ^= *p2;
		*p2 ^= *p1;
		*p1 ^= *p2;
	}
	return str;
}

HC check(char* str, char parity) {
	HC o = {fs: str, bb: 0}; //output
	int i, j, k, mp_bit, offset;
	int len = strlen(str);
	int* pb, * pp;

	i = j = k = mp_bit = offset = 0;

	//check code, return bad bit and fixed string
	for(i = 0; i < len; ++i) {
		if(str[i] == '1') {
			mp_bit = (int) (log(len - i) / log(2)) + 1;
			break;
		}
	}

	pb = (int*)calloc(mp_bit, sizeof(int));
	pp = (int*)calloc(mp_bit, sizeof(int));
	str = strrev(str);

	for(i = 0; i < mp_bit; ++i) {
		offset = (int) pow(2, i);

		for(j = offset - 1; j < len; j += (2 * offset)) {
			for(k = 0; k < offset; ++k) {
				if(str[j+k] == '\0')
					break;
				else if(j+k == offset - 1 && str[j+k] == '1')
					++(pp[i]);
				else if(str[j+k] == '1')
					++(pb[i]);
			}
		}

		if(parity == '1')
			++(pb[i]);

		pb[i] %= 2;
	}

	for(i = 0; i < mp_bit; ++i) {
		if(pb[i] != pp[i] && (int) pow(2,i) < len)
			o.bb += (int) pow(2, i);
	}

	if(o.bb > 0) {
		if(str[o.bb - 1] == '1')
			str[o.bb - 1] = '0';
		else
			str[o.bb - 1] = '1';
	}

	str = strrev(str);
	free(pb);
	free(pp);
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
						if(i == ml){
							al = i + 1;
							c[i] = '\0';
						}

						if(c[i] != '0' && c[i] != '1') {
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
				r = check(c, p);

				if(r.bb == 0) {
					printf("No error detected.\n");
					break;
				} else {
					printf("Error at bit: %d\nCode after correction: %s\n", r.bb, r.fs);
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
