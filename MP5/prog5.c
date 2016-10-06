/*			
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */



#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"

/* INTRO***************
For this MP, we're creating a code breaker, which is implemented used 3 functions here. We create static variables that can be used for any of these functions.
The first function is set_seed, we call sscanf which takes the input and stores the integer in seed and the rest in post. We use sscanf, secure scanf, so that
if the user creates a too long post it won't extend past the 2 memory locations which we had already save for it when we declared char post[2].
the return value of sscanf, numitems, contains the number of items successful read, for our seed we only want 1 integer, so if numitems equals 1
we srand(seed) and return 1. The seed we got from sscanf, we need to do srand to create the seed for our random function because true randomness is incredibly
difficult to create otherwise. If numitems doesn't equal 1, we print an error message and return 0.

Our 2nd function is start_game. It's called after set_seed by main.c *one equals rand()%8, *two, *three*, *four are also set to rand()%8.
The order the rands are declared is important otherwise the solutions wouldn't be at the right places. We do %8 bc we want our numbers to be
only 0-7. We make copies of the four solution number into our static variables (solution1 etc) so we can use it for the make_guess function later on.
We also set guess_number =1 at the start of the game

make_guess is called by main.c everytime the user types in a guess
The guess they made is in string guess_str. We create another post, and integers w,x,y,z.
We use another sscanf, which will store the four integers from guess_str into w,x,y,z.
and the rest into post. The return value of sscanf (numitems2) indicates the number of items sucessfully read from the string.
The guess_str is valid if w,x,y,z are all integers between 0 and 7, inclusive and if numitems2 is 4. Otherwise we print an error string and return 0.
If it's valid we declare pair1-4 which tells if solution1-4 are paired with an integer the user guessed & similarily we declare pairw-z which tells if
w-z are pair with any of the solution integers. We also declare matched & misplaced to keep track of the # of perfect matches and misplaced matches respectively.
All of these 10 variables are initially set to 0, and we make sure to declare them in the if statement, otherwise if the guess_str was invalid, we wouldn't use them
and thus a warning would occur.
We first check perfect matches eg w==solution1, in which case we set the corresponding pairings to zero and increment matched. We repeat this for x=solution2 and etc.
Then we checked for misplaced matches, first we check if w is paired, if it's not it's possible it was misplaced. If w==solution2 and solution2 is unpaired (aka pair2==0)
then we know w is a misplaced solution 2 and we set the pairing for w & 2 to 1 and increment misplaced by one. We continue this process with w for solution 3 & 4. Each time
we check to make sure w is still unpaired since we don't want the 1 inputted integer to count for 2 misplaced matched.
We then do the same for x,y,z if it's unpaired. for x don't need to check sol2, for y not sol3 and z not for sol4 bc already checked in earlier if loop
print string with # of guesses,#of perfect matches and #misplaced matches
increment guess_number AFTER printing otherwise it'd be one off. Then check to see if matches ==4, if so it was a perfect guess and print a string saying so.
Return 1 (when the guess string is valid.
*/


static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;
//static variables used in various functions

/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int set_seed (const char seed_str[])
{
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read.
//    We declare
//    int seed;
//    char post[2];
//    The sscanf statement below reads the integer into seed.
//    sscanf (seed_str, "%d%1s", &seed, post)
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully.
//    Check that the return value is 1 to ensure the user enters only an integer.

   int seed;
      char post[2]; //makes a changeable string of 1 char and 1 null
  int numitems= sscanf (seed_str, "%d%1s", &seed, post); //numitems indicates number of items read successfully
  if(numitems==1) //means exactly 1 item was read successfully
 { srand(seed); //do our srand with the item stored in seed
    return 1;
    }
else{ //if not exactly 1 item
    printf("set_seed: invalid seed\n"); //error message
    return 0;
}

}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above.
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 0 and 7)
 *          *two -- the second solution value (between 0 and 7)
 *          *three -- the third solution value (between 0 and 7)
 *          *four -- the fourth solution value (between 0 and 7)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void
start_game (int* one, int* two, int* three, int* four)
{

    //values in solution code sequence set to random number from 0 to 7 so rand()%8
    *one = rand() % 8;
    *two = rand() % 8;
    *three = rand() % 8;
    *four = rand() % 8;
    
    //set static variable guess_number to 1
    guess_number = 1;

    //make copy in static variables to be used in make_guess function
    solution1 = *one;
    solution2 = *two;
    solution3 = *three;
    solution4 = *four;
    
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 0-7). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 0 and 7)
 *          *two -- the second guess value (between 0 and 7)
 *          *three -- the third guess value (between 0 and 7)
 *          *four -- the fourth color value (between 0 and 7)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 0 and 7), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */

int make_guess (const char guess_str[], int* one, int* two, 
	    int* three, int* four)
{
//  One thing you will need to read four integers from the string guess_str, using a process
//  similar to set_seed
//  The statement, given char post[2]; and four integers w,x,y,z,
char post[2]; //string of 1 char and 1 null
int w,x,y,z; //will contain integers from guess_str
 int numitems2= sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post);
//  will read four integers from guess_str into the integers and read anything else present into post
//  The return value of sscanf (numitems2) indicates the number of items sucessfully read from the string.
if( w>=0 && w<=7 && x>=0 && x<=7 && y>=0 && y<=7 && z>=0 && z<=7 && numitems2==4)
{//only true if w,x,y,z are between 0 & 7, and number of items successfully read is 4
//have variables for whether the numbers in the solution are paired (pair1, etc)
//have variables for whether the integers from guess_str which was typed by the user in main.c
//are pair (pairw, pairx etc). all these are set initally to 0 and set to one if and only if
//it's paired
int pair1=0;
int pair2=0;
int pair3=0;
int pair4=0;
int pairw=0;
int pairx=0;
int pairy=0;
int pairz=0;
int matched=0; //value counting matched
int misplaced=0; //counting misplaced
	if(w==solution1){ 
	++matched; //increment matched
	pair1=1;
	pairw=1;
	//set pairing
} //do same for x,y,z &sol2,3,4 respectively
	if(x==solution2){
	++matched;
	pair2=1;
	pairx=1;
}
if(y==solution3){
	++matched;
	pair3=1;
	pairy=1;
}
if(z==solution4){
	++matched;
	pair4=1;
	pairz=1;
}
if(!pairw) //w is not paired
{
	if(!pair2 &&w==solution2) //check to see if sol2 is paired
{//if w is unpaired and equals sol2 which is also unpaired then you know it's misplaced  
	++misplaced; //increment
	//update pairing
	pair2=1;
	pairw=1;
}
	if(!pair3 &&w==solution3 && !pairw) 
 //repeat same process as above for sol3
// but now also check again for !pairw bc you don't know if w got paired from a previous if loop
{
	++misplaced; //increment
	//update pairing
	pair3=1;
	pairw=1;
}
	if(!pair4 &&w==solution4 && !pairw) //same as sol3
{
	++misplaced;
	pair4=1;
	pairw=1;
}
	
//repeat process for x,y &z, for x don't need to check sol2, for y not sol3 and z not for sol4 bc already checked in earlier if
}
if(!pairx) //x is not paired
{
	if(!pair1 &&x==solution1)
{
	++misplaced;
	pair1=1;
	pairx=1;
}

	if(!pair3 &&x==solution3 && !pairx)
{
	++misplaced;
	pair3=1;
	pairx=1;
}
	if(!pair4 &&x==solution4 && !pairx)
{
	++misplaced;
	pair4=1;
	pairx=1;	
}
	

}
if(!pairy) //y is not paired
{
	if(!pair1 &&y==solution1)
{
	++misplaced;
	pair1=1;
	pairy=1;
}
	if(!pair2 &&y==solution2 && !pairy)
{
	++misplaced;
	pair2=1;
	pairy=1;
}

	if(!pair4 &&y==solution4 && !pairy)
{
	++misplaced;
	pair4=1;
	pairy=1;
}
	

}
if(!pairz) //z is not paired
{
	if(!pair1 &&z==solution1)
{
	misplaced++;
	pair1=1;
	pairz=1;
}
	if(!pair2 &&z==solution2 && !pairz)
{
	misplaced++;
	pair2=1;
	pairz=1;
}

	if(!pair3 &&z==solution3 && !pairz)
{
	misplaced++;
	pair3=1;
	pairz=1;
}
	

}

//matches and misplaced are updated
printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n",guess_number,matched,misplaced);//print string with # of guesses,#of perfect matches and #misplaced matches
guess_number++; //increment AFTER printing otherwise it'd be one off
if(matched==4) //if all letters in right place
printf(	"You guessed correctly in %d guesses\n",guess_number); //perfect guessing
return 1;
}
else
{	
	printf("make_guess: invalid guess\n"); //invalid guess, error string
	return 0;
}
//  You should then check if the 4 integers are between 0-7. If so, it is a valid guess
//  Otherwise, it is invalid.  

}


