#include "sudoku.h"

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

  assert(i>=0 && i<9);

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

  assert(j>=0 && j<9);

  // BEG TODO

for (int n=0;n<9;n++)
{
	if(sudoku[n][j]==val)
	return 1;
}  

  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO

  int isq=(i/3) *3;
int jsq=(j/3) *3;
int a; //for row
int b; // for col counter
for(a=0;a<3;a++){
	for(b=0;b<3;b++)
	{
	if(sudoku[isq+a][jsq+b]==val)
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
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
int i,j;
int fill=1; //assumed it's filled
for (i=0;((i<9) && (fill==1));i++){

	for(j=0;((j<9) && (fill==1));j++){	
	if (sudoku[i][j]==0){
	fill=0;
	break;
	}	

}	
}
i=i-1; //bc i always is 1 too much
if(fill==1){
return 1;
}
else
{
//i & j is unfillled value
}

for (int num=1;num<=9;num++){
	if (is_val_valid(num,i,j,sudoku)){
	sudoku[i][j]=num;
	if(solve_sudoku(sudoku)){
	return 1;
	}
sudoku[i][j]=0;
}
}

  return 0;
  // END TODO.
}



