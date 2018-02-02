/*
 * Maxwell Plotkin
 * COMP222 Spring 2018
 * Assignment 1
 */
#include <stdlib.h>
#include <stdio.h>

void printMenu(void);
int parseInput(char in);
void enterParams(void);
float calculateCPI(void);
float calculateExecTime(void);
float calculateMIPS(void);

int numClasses = 0;
int MHz = 0;
int* CPIs;

int main(){
	char sel = 'e';

	while(1){ 
		printMenu();
		scanf("%c", &sel);
		if(parseInput(sel))
			return 0;
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
		">"
	);
}

int parseInput(char in){
	switch(in){
		case 'a':
			enterParams();
			return 0;
		case 'b':
			return 0;
		case 'c':
			return 0;
		case 'd':
			return 0;
		case 'e':
			return 1;
		default:
			return 0;
	}
}

void enterParams(void){
	printf("Enter number of instruction classes: ");
	scanf("%d", &numClasses);

	CPIs = malloc(sizeof(int) * numClasses);

	printf("Enter frequency in MHz: ");
	scanf("%d", &MHz);

	for(int i = 0; i < numClasses; ++i){
		printf("Enter class #%d instruction count: ", i+1);
		scanf("%d", &CPIs[i]);
	}
	getchar();
}

float calculateCPI(void){
}

float calculateExecTime(void){
}

float calculateMIPS(void){
}
