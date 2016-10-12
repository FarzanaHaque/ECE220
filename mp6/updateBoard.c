/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */
#include <stdio.h>
int sboard[18*35] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){

/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: number of alive neighbors
 */
int neighbor=0;
int m=0;
int n=0;
for ((m=(row-1));(m<=(row+1));m++)
{
	for((n=(col-1));(n<=(col+1));n++)
	{
		if((m>=0) && (m<boardRowSize) && (n>=0) && (n<boardColSize) && !(m==row && n==col))
		{ //printf("%d,%d",m,n);
			if(board[m*boardColSize+n]==2 || board[m*boardColSize+n]==1)
				neighbor++;
		}
	}

}
return neighbor;
}
void updateBoard(int* board, int boardRowSize, int boardColSize) {
//if it's an alive cell going to DEAD it's going to change to 2 in first iteration
//if it's a dead cell going to ALIVE it's going to change to 3 in the first iteration
//we do this to preserve the original state
int i,j;
for(i=0;i<boardRowSize;i++)
{
	for(j=0;j<boardColSize;j++)
{
	if(board[i*boardColSize+j]==0)
	{
		if((countLiveNeighbor(board,boardRowSize, boardColSize, i,j))==3)
		board[i*boardColSize+j]=3;
	}
if(board[i*boardColSize+j]==1)
{
int cln=countLiveNeighbor(board,boardRowSize, boardColSize, i,j);
if((cln<2) || (cln>3))
board[i*boardColSize+j]=2;
}
}
}
//finished first iteration
for(i=0;i<boardRowSize;i++)
{
	for(j=0;j<boardColSize;j++)
{
	if(board[i*boardColSize+j]==2)
	board[i*boardColSize+j]=0;
	if(board[i*boardColSize+j]==3)
	board[i*boardColSize+j]=1;
}
}



}


/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
int change=1;
int cln;
int i=0;
int j=0;
for(i=0;i<boardRowSize;i++)
{
	for(j=0;j<boardColSize;j++)
{
	if(board[i*boardColSize+j]==0)
	{
		if((countLiveNeighbor(board,boardRowSize, boardColSize, i,j))==3)
		change=0;
	}
if(board[i*boardColSize+j]==1)
{
cln=countLiveNeighbor(board,boardRowSize, boardColSize, i,j);
if((cln<2) || (cln>3))
change=0;
}
}
}
return change;
}

				
				
			

