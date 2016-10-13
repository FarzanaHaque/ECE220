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
/*
For this program we implement game of life using 3 functions countLive neighbor, updateBoard and alive stable.
For countliveneighbor we are input the pointer of the board, #rows,#columns, and the row & col of the specific 
item on the board we want to count neighbors for. We initialize # of neighbors to zero and use variables m,n
which represent the row and column value respectively of the neighbor we're checking. We know all the neighbors
have to have an m value between row-1 to row+1 inclusive and n value from col -1 to col +1.
We go through the neighbors by using 2 for loops. Each time we get a pair of values for m & n we need to make sure they're valid.
that pair is a valid location in the board if the m &n value are both >=0 && <boardSize for that dimension. eg for a 3 x4 board,
m can be from 0-2 but not 3, n can be 0-3 but not 4. We also need to make sure that we're not counting board[row][col] as a neighbor
even though it's within the range so we put !(m==row & n==col)
each time we go through a valid location we check to see if it's alive and then increment neighbor. We consider a location alive if 
it's 1 by definition and 2 which'll make more sense when we look at update board. we return neighbor

For update board we go through every cell in the board using 2 for loops using variables i & j, which both go from 0 to a boarddimension
if the cell is dead (==0) then we check to see if it has 3 alive neighbors then we make it turn alive, else it stays dead.
if the cell is alive (==1) then we check to see if it has less than 2 or greater than 3 neighbors then we make it dead, else it stays the alive.
while going to through the board we can't make it cells turn for 0 to 1 or 1 to 0 because it'll mess up counting neighbors later on.
so for that reason we go through every cell on the board twice, 1st to see whether or not the cell should stay the same state or change
2nd iteration updating the board so those cells represent 0 if dead 1 if alive. Going through 2 iterations prevents counting neighbors from messing up.
//if it's an alive cell going to DEAD it's going to change to 2 in first iteration, 0 in the 2nd iteration
//if it's a dead cell going to ALIVE it's going to change to 3 in the first iteration, 1 in the 2nd iteration
//we do this to preserve the original state

For Alive stable, we initialize change to 1, it's the value we return. We go through the entire board using 2 for loops like in updateboard. If the cell is dead & has 3 live neighbors, change=0
if the cell is alive has less than 2 or more than 3 neighbors, change=1. If we go through the entire board and neither of these cases happen change is left unchanged and we return 1 otherwise we return 0.
*/
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
int m=0; //row of location being checked
int n=0; //col of location being checked
for ((m=(row-1));(m<=(row+1));m++) //m has to be within row-1 and row+1 to be nieghbor
{
	for((n=(col-1));(n<=(col+1));n++) //n has to be within col-1 and col+1 to be a neighbor
	{
		if((m>=0) && (m<boardRowSize) && (n>=0) && (n<boardColSize) && !(m==row && n==col)) //neighbor only if valid (m,n>=0 and within boardsize) 
//and m,n not same as row,col bc then it's itself not a neighbor 
		{
			if(board[m*boardColSize+n]==2 || board[m*boardColSize+n]==1) //alive if 1 bc def & 2 bc then it was alive when counting but when you update the board that cell will be dead
				neighbor++; //increment
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
	for(j=0;j<boardColSize;j++) //goes through every cell on board
{
	if(board[i*boardColSize+j]==0) //dead cell
	{
		if((countLiveNeighbor(board,boardRowSize, boardColSize, i,j))==3) //number of alive neighbors=3
		board[i*boardColSize+j]=3; //should go from alive to 'dead' aka 3 
	}
if(board[i*boardColSize+j]==1) //alive cell
{
int cln=countLiveNeighbor(board,boardRowSize, boardColSize, i,j);
if((cln<2) || (cln>3)) //live neighbor <2 or >3
board[i*boardColSize+j]=2; //cell goes from dead to 'alive' aka 2
}
}
}
//finished first iteration
for(i=0;i<boardRowSize;i++)
{
	for(j=0;j<boardColSize;j++) //go through board 2nd time
{
	if(board[i*boardColSize+j]==2) //'dead'
	board[i*boardColSize+j]=0; //now actually represent dead
	if(board[i*boardColSize+j]==3) //'alive'
	board[i*boardColSize+j]=1; //now actually alive
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
int change=1; //change is unchanged if board is stable 
int cln; //stores countneighborlive when cell is alive, written like this just so easier to write
int i=0; //row variable
int j=0; //col variable
for(i=0;i<boardRowSize;i++)
{
	for(j=0;j<boardColSize;j++) //go through every cell in board
{
	if(board[i*boardColSize+j]==0) //cell is dead
	{
		if((countLiveNeighbor(board,boardRowSize, boardColSize, i,j))==3) //neighbors =3
		change=0; //change change
	}
if(board[i*boardColSize+j]==1) //cell is alive
{
cln=countLiveNeighbor(board,boardRowSize, boardColSize, i,j);
if((cln<2) || (cln>3)) //neighbors <2 || >3
change=0; //change is changed
}
}
}
return change; //1 if stable 0 if not
}

				
				
			

