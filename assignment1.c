/*
 * Maxwell Plotkin
 * COMP222 Spring 2018
 * Assignment 1
 */
#include <stdio.h>

void printMenu(void);
int parseInput(char in);
void enterParams(void);
float calcExecTime(void);
float calcMIPS(void);

float MHz = 0; 
float CPI = 0;
int I = 0;

int main(){
	char sel = 'e';

	while(1){ 
		printMenu();
		scanf("%c", &sel);
		printf("\n");
		if(parseInput(sel))
			return 0;
		getchar();
		printf("\n");
	}
}

void printMenu(void){
	printf(
		"CPU Metrics\n"
		"***********\n"
		"a) Enter Parameters\n"
		"b) Calculate Average CPI\n"
		"c) Calculate Total Instruction Time\n"
		"d) Calculate MIPS\n"
		"e) Quit\n"
		"> "
	);
}

int parseInput(char in){
	switch(in){
		case 'a':
			enterParams();
			return 0;
		case 'b':
			printf("Average CPI: %.2f\n", CPI); 
			return 0;
		case 'c':
			printf("Total Instruction Time (ms): %.2f\n", calcExecTime());
			return 0;
		case 'd':
			printf("MIPS: %.2f\n", calcMIPS());
			return 0;
		case 'e':
			return 1;
		default:
			printf("Invalid Selection.\n");
			return 0;
	}
}

void enterParams(void){
	int cpi = 0; 
	int it = 0;
	int nc, t1, t2;

	printf("Enter number of instruction classes: ");
	scanf("%d", &nc);

	printf("Enter frequency in MHz: ");
	scanf("%f", &MHz);

	for(int i = 0; i < nc; ++i){
		printf("Enter class #%d CPI: ", i+1);
		scanf("%d", &t1);

		printf("Enter class #%d instruction count (mil): ", i+1);
		scanf("%d", &t2);

		cpi += t1 * t2;
		it += t2;
	}

	CPI = (float) cpi / it;
	I = it;
}

float calcExecTime(void){
	return MHz ? 1000 * I * CPI / MHz : 0;
}

float calcMIPS(void){
	return CPI ? MHz / CPI : 0;
}
