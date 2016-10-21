#include "sudoku.h"
/*
our first function,is_val_in_row checks 1)that i is the valid range
2)returns 1 if it's in the row, which we do by checking all the columns in a given row
similarly for is_val_in_col, given a jth column we check sudoku[n][j] where n ranges from 0 to 8
the is_val_in3x3 is a bit more complicated
//i decided to find the upper left corner of the 3x3 zone that [i][j] is in, the upper left corner of that zone
//can be found as [(i/3)*3] [(j/3)*3] which works because we're using integers not floating points
//then after finding the corner i loop through the entire zone using 2 for loops, returning 1 if val is found in any of those locations
is_val_valid checks that all the above functions, if all of them are them return zero, that means you can put the value in that i,j because it doesn't make the rules of sudoku

for solve_soduku

we first set fill as 1,assuming it's filled
then we go through sudoku to see if any sudoku[i][j]==0
in that case, we'll set fill as 0 and we can use that i,j for the location of an unfilled space so 
we dont' have to do an additional iteration checking sudoku, however bc of the way my loop is implemented
I have to subtract i by 1 in order to get the right i value i want of the empty cell
if going through all of sudoku, filled is still 1, the sudoku is solved and return 1
if not we use the i & j of the empty cell and see if a guess is valid in that location using is_val_valid
if it is, we make the guess and use memorization technique. so the function will call itself and keep on making valid
guesses for subsequent cells, if at the end, it's filled then return 1, just solved the thing
a guess is wrong when it calls solve_Sudoku, it'll return 0  , it'll change the cell back to zero and go through the loop to make the next valid guess
it's possible for an intial guess to be right and a subsequent guess to be wrong, but in that case, the wrong guess would go back into the loop trying different nums until it's right 


*/
// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}

//-------------------------------------------------------------------------------------------------
// Start coding your MP here.
// ------------------------------------------------------------------------------------------------

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9); //valid range for i

for (int n=0;n<9;n++)
{
	if(sudoku[i][n]==val)
	return 1;
}
  // BEG TODO
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9); //valid range for j

  // BEG TODO

for (int n=0;n<9;n++)
{
	if(sudoku[n][j]==val)
	return 1; //found
}  

  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO
//i decided to find the upper left corner of the 3x3 zone that [i][j] is in, the upper left corner of that zone
//can be found as [(i/3)*3] [(j/3)*3] which works because we're using integers not floating points
//then after finding the corner i loop through the entire zone using 2 for loops, returning 1 if val is found in any of those locations
 
  int isq=(i/3) *3; //gives us the i value for upper left corner of 3x3
int jsq=(j/3) *3; //j value for same corner
int a; //for row counter
int b; // for col counter
for(a=0;a<3;a++){
	for(b=0;b<3;b++)
	{
	if(sudoku[isq+a][jsq+b]==val) //location in 3x3 zone currently being checked
	return 1;
	}
}
  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {
  if(is_val_in_row(val, i, sudoku)) return 0;
  if(is_val_in_col(val, j, sudoku)) return 0;
  if(is_val_in_3x3_zone(val, i, j, sudoku)) return 0;
  return 1;
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
/*
we first set fill as 1,assuming it's filled
then we go through sudoku to see if any sudoku[i][j]==0
in that case, we'll set fill as 0 and we can use that i,j for the location of an unfilled space so 
we dont' have to do an additional iteration checking sudoku, however bc of the way my loop is implemented
I have to subtract i by 1 in order to get the right i value i want of the empty cell
if going through all of sudoku, filled is still 1, the sudoku is solved and return 1
if not we use the i & j of the empty cell and see if a guess is valid in that location using is_val_valid
if it is, we make the guess (sets sudoku[i][j]=num) and use memoirization technique. so the function will call itself and keep on making valid
guesses for subsequent cells, if at the end, it's filled then return 1, just solved the thing
a guess is wrong when it calls solve_Sudoku, it'll return 0  , it'll change the cell back to zero and go through the loop to make the next valid guess
it's possible for an intial guess to be right and a subsequent guess to be wrong, but in that case, the wrong guess would go back into the loop trying different nums until it's right 
at the end if it's solvable it'll be solved

*/
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
int i,j;
int fill=1; //assumed it's filled
//if fill==0 it'll stop the loop
for (i=0;((i<9) && (fill==1));i++){

	for(j=0;((j<9) && (fill==1));j++){	//looping through the 9x9 sudoku
	if (sudoku[i][j]==0){
	fill=0; //means there's an empty spot in sudoku and thus it's not filled
	break;
	}	

}	
}
i=i-1; //bc i always is 1 too much after we break the loop 
if(fill==1){
return 1; //if filled it's already solved
}
else //not filled
{

for (int num=1;num<=9;num++){//1-9 is valid numbers in sudoku
	if (is_val_valid(num,i,j,sudoku)){ //check to see if we can put num in that i,j
	sudoku[i][j]=num; //if we can make that guess
	if(solve_sudoku(sudoku)){ //recursive, so it'll continue on making guesses for the rest of the empty spots until it's either filled or can't make any more valid guesses
	return 1; //if all the guesses made are valid then you solved it and should return 1
	}
sudoku[i][j]=0; //num in that spot doesn't work, turn back into zero and try guessing another number in next interation
}
}

  return 0; //given soduku is unsolveable
}
  // END TODO.
}



