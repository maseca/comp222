#include <stdio.h>
#include <stdlib.h>

/* Define structure for instruction containing fields for destination register, 2 source registers, and individual instruction delay 
and a variable as pointer to structure for creating a dynamic array of instructions */


/*************************************************************/
void FUNCTION TO PRINT OUT CHART OF INSTRUCTIONS WITH DELAYS() 
{
/* Declare local variables */
/* For each instruction, align instructions by tabbing according to delay, and print out stages with proper tabbing (FI\tDI\tCO\tFO\tEI\tWO) */
  return;
}


/*************************************************************/
void FUNCTION TO ENTER INSTRUCTIONS()
{
/* Declare local variables, including an array of characters to store user input */

/* Prompt for total number of instructions */
 
/* Allocate memory to hold a set of instructions based on total number of instructions+1 (instruction 0 used for dependency checking)*/

/* Initialize instruction 0's destination register to -1 to prevent false RAW dependency w/ instruction 2 */

/* For each instruction, prompt for user input with instruction number, such as: 1)   
and read instruction as a string and store at proper field of appropriate index within dynamic array of instructions */

return;
}


/*****************************************************/
void FUNCTION TO CALCULATE DELAY OF SET OF INSTRUCTIONS ON A 6-STAGE PIPLELINE ARCHITECTURE
{
/* Declare local variables */

/* For each instruction i from 2 to total number of instructions, initialize delay as 0 and check for dependency
between instruction (i-2) and i, as well as between instruction (i-1) and i */

{ /* begin for-loop */

/* If dependency,  set delay appropriately, as well
as a flag to check for possible overlap between dependent instructions */

/* Note: general formula for delay: 
delay=2 if instruction i depends on instruction (i-1)
delay=1 if instruction i depends on instruction (i-2) and no overlap of dependencies
delay=0 otherwise
*/

/* Calculate individual delay for current instruction */

} /* end for-loop */

/* print chart */
return;
}

/***************************************************************/

void FUNCTION TO CALCULATE DELAY OF SET OF INSTRUCTIONS ON A 6-STAGE SUPERSCALAR ARCHITECTURE
{
/* Declare local variables */

/* For each instruction i from 2 to total number of instructions */

{ /* begin for-loop */

/* Flip the flag used for expected/non-expected pipeline delay to resemble delay pattern for superscalar: 
 if flag is 0, set it to 1, if it is 1, reset it to 0 */

initialize delay as 0 and check for dependencies
between instruction (i-4) and i, (i-3) and i, all the way to (i-1) and i */

/* If dependency, set delay appropriately, as well as setting flag for expected pipeline delay to 1, and set
flag to check for possible overlap between dependent instructions */

/* Note: general formula for delay: 
delay=2 if instruction i depends on instruction (i-1)

delay=2 if instruction i depends on instruction (i-2) and expected pipeline delay and no overlap of dependencies

delay=1 if instruction i depends on instruction (i-2) and no expected pipeline delay and no overlap of dependencies 

delay=1 if instruction i depends on instruction (i-3) and no overlap of dependencies

delay=1 if instruction i depends on instruction (i-4) and expected pipeline delay and no overlap of dependencies 

delay=0 otherwise
*/

/* Calculate individual delay for current instruction */

} /* end for-loop */

/* print chart */

return;
}


/****************************************************************/
int main()
{
/* Declare local variables */

/* Until user quits, print menu, prompt for user input, and select corresponding function */

return 1;
}
