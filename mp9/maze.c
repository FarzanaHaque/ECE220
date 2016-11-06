#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
/*
So first you create the maze. You have to open the file, scan the first 2 integers to get width & height
allocate space for maze, and then for cells, you have in total width*height # of cells, but it's a 2d array
so I allocated space for the 0th column of cells then i made a for loop,that went through every cell basically
so every time you increased i, you'd allocate space for the next column
you scan each char of the maze, if it's a newline you skip it and go to the next one, otherwise you store in that cell
if it's S, that i,j is startcolumn,startrow of the maze, similarily if it's E the i,j is end row,endcolumn
then we close the file and return the maze
for destroy maze we have to free first all the cells then the maze and then set MAZE to null
for printMaze we use 2 nested for loops for i,j printing every cell of the board & a new line before incrementing i (the row)

for solveMazeManhattanDFs, first we check to see if we're at the end of the maze, in that case we return 1
then we  check if the col row is within bounds, otherwise we return 0
Then we check if it's not S && not Empty, if it is we return 0 because we are either revisiting or hit a wall
if the it's not S, we set that cell[row][col] to path (.)
Then we calculate the manhattan distances for up,down,left,right
we calculate the manhattan distances because we don't want to move randomly, we want to move in the direction that's closes to the endpoint
We use a sorting algorithm instead of a bunch of if's so we create an array = {leftManhat, downManhat, rightManhat, upManhat}
we implement sorting so that it's from smallest manhattan distance to largest
we implement another for loop to go through each element of the list, we check if the element is leftManhat,down,right,up (in that order), if it's left, it we check to make sure the cell left of the given isn't Start
then we set our variable s to equal solveMazeManhattanDFS (maze,col-1,row) if s==1 we know we found a solution and we return 1, otherwise
we similarily do something for down,right,up
if none of these case return 1, we increment i and check that element in the array the same way
if cell given isn't start we unmark the path (.) and instead put (~) for visited & then return 0
That way if you hit that point again, you know it's already been visited & doesn't work so you skip it

*/
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
FILE *f;
f=fopen(fileName,"r+");
if(f== NULL){
	printf("Cannot open %s\n", fileName);
return NULL;
}
int width, height;//cols,rows
fscanf(f,"%d %d",&width,&height);
maze_t *m;
m=(maze_t*)malloc(sizeof(maze_t));
m->width=width;
m->height=height;

int i,j=0;
m->cells = malloc(height*sizeof(char*));//allocates space for column 0
for (i=0;i<height;i++){//allocates space for each subsequent column
	m->cells[i]=malloc(width*sizeof(char));
	for(j=0;j<width;j++){
		char scanned;
		fscanf(f,"%c",&scanned);
		if(scanned==10){
			j--;
		}
		else
		m->cells[i][j]=scanned;
		if(scanned==83){//start
			m->startColumn=j;
			m->startRow=i	;		
		}
		if(scanned==69){//end
			m->endColumn=j;
			m->endRow=i	;
		}	
		//printf("%c\n",m->cells[i][j]);
	}
}
//printf("%d,%d %d,%d",m->startRow,m->startColumn,m->endRow,m->endColumn);
//printf("%d %d",width,height);
fclose(f);

    return m;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    free(maze->cells); //need to do this before free maze!
	free(maze);
	maze=NULL; 

}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    int i,j=0;
	for(i=0;i<maze->height;i++){
		for(j=0;j<maze->width;j++){
		printf("%c",maze->cells[i][j]);
		}
		printf("\n");
	}
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search and a manhattan distance heuristic
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search and a manhattan distance heuristic
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */


int solveMazeManhattanDFS(maze_t * maze, int col, int row)
{

    
    //both parts together
        //base cases
    //if we are at the end of the maze, i.e. at 'E'
    if(row == maze->endRow && col == maze->endColumn)
    	return 1;

    //if out of bounds
    if(row > maze->height || row < 0 || col > maze->width || col < 0) 
        return 0;
    //if not S and then if not a space
    if(maze->cells[row][col] != 83) //83 is S
        if(maze->cells[row][col] != 32) //ascii for ' '
        	return 0; 
 
    //set col, row as part of the solution path in the maze
    if(maze->cells[row][col] != 83)
        maze->cells[row][col] = 46; //. path
    
    //calculate manhattan distance
    int upManhat = abs( (row-1) - (maze->endRow) ) + abs( col - (maze->endColumn) );
    int downManhat = abs( (row+1) - (maze->endRow) ) + abs( col - (maze->endColumn) );
    int leftManhat = abs( row - (maze->endRow) ) + abs( (col-1) - (maze->endColumn) );  
    int rightManhat = abs( row - (maze->endRow) ) + abs( (col+1) - (maze->endColumn) );
     
    //sorting algorithm bc a bunch of if statements? no thanks
    //this is insertion sort
    int arr[] = {leftManhat, downManhat, rightManhat, upManhat};
    int i;
//sorting
    for(i = 1; i < 4; i++)
    {
        int temp = arr[i];
        int j;
        for(j = i-1; i >= 0 && temp < arr[j] ; j--)
            arr[j+1] = arr[j];
        arr[j+1] = temp;
    }
    //done sorting
    
    //recrusive calls in order of smallest manhattan distance to largest, if the same
    //calls in order of left, down, right, up
    for(i = 0; i < 4; i++)
    {
        int s;
        if(arr[i] == leftManhat)
        { 
            if(maze->cells[row][col-1] != 83) //check that cell is not 'S'
            {
                s = solveMazeManhattanDFS(maze, col-1, row); //recursive call
                    if(s == 1) return 1;
            }
        }
        if(arr[i] == downManhat)
        {
            if(maze->cells[row+1][col] != 83)
             {
                s = solveMazeManhattanDFS(maze, col, row+1);
                    if(s == 1) return 1;
            }
        }
        if(arr[i] == rightManhat)
        {
            if(maze->cells[row][col+1] != 83)
            {
                s = solveMazeManhattanDFS(maze, col+1, row);
                    if(s == 1) return 1;
            }
        }
        if(arr[i] == upManhat)
        {
            if(maze->cells[row-1][col] != 83)
              {
                s = solveMazeManhattanDFS(maze, col, row-1);
                    if(s == 1) return 1;
            }
        } 
    }
 
    //unmark col, row as part of solution and mark as visited
   if(maze->cells[row][col] != 83)
   		maze->cells[row][col] = 126; //~ = visited
    
    return 0;
}




