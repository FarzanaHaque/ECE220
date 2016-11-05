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
    free(maze->cells);
	free(maze);
	maze=NULL; //is this part necessary??

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
void InsertionSort(int array[], int n)
{
int us, s;
int usItem;
/* loop through us items */
for (us = 1; us < n; us++)
{
usItem = array[us];
/* loop through items until we find a spot for usItem */
for (s = us-1; (s >= 0) && (array[s] > usItem); s--)
array[s+1] = array[s]; /* shift s items */
array[s+1] = usItem; /* insert us item */
}
}
int solveMazeManhattanDFS(maze_t * maze, int col, int row)
{
int erow=maze->endRow;
int ecol=maze->endColumn;
if(col==ecol&&row==erow)
return 1;
if(col<0||col>=maze->width||row<0||row>=maze->height)
return 0;
if(maze->cells[row][col]!=' ')
return 0;

maze->cells[row][col]='.';
int solve1,solve2,solve3,solve4=0;
if(col>0){
solve1=solveMazeManhattanDFS(maze,col-1,row);
if(solve1)
return solveMazeManhattanDFS(maze,col-1,row);}
if(row<erow-1){
solve2=solveMazeManhattanDFS(maze,col,row+1);
if (solve2)
return solveMazeManhattanDFS(maze,col,row+1);}
if(col<ecol-1){
solve3=solveMazeManhattanDFS(maze,col+1,row);
if(solve3)
return solveMazeManhattanDFS(maze,col+1,row);
}
if(row>0){
solve4=solveMazeManhattanDFS(maze,col,row-1);
if(solve4)
return solveMazeManhattanDFS(maze,col,row-1);
}

maze->cells[row][col]=' ';

return 0;



/*
int left,down,right,up=-1;
int man[4]; //max 4 elements
man[0]=man[1]=man[2]=man[3]=-1;
//if new location is valid, calculate distance & insert into man stack
if(col>0){
left=abs(row-erow)+abs(col-1-ecol);
InsertionSort(man,left);}
if(row<erow-1){
down=abs(row+1-erow)+abs(col-ecol);
InsertionSort(man,down);}
if(col<ecol-1){
right=abs(row-erow)+abs(col+1-ecol);
InsertionSort(man,right);}
if(row>0){
up=abs(row-1-erow)+abs(col-ecol);
InsertionSort(man,up);}

int solve1,solve2,solve3,solve4=0; //set to false

if(man[0]!=-1){
if(left!=-1 &&left==man[0]){
maze->cells[row][col]='.';
left=-1; //lets you know later on if this doesn't work, it's already been checked
solve1=solveMazeManhattanDFS(maze,col-1,row);
}
if(down!=-1&&down==man[0]){
maze->cells[row][col]='.';
down=-1;
solve1=solveMazeManhattanDFS(maze,col,row+1);
if(solve1)
return solveMazeManhattanDFS(maze,col,row+1);
}
if(right!=-1&&right==man[0]){
maze->cells[row][col]='.';
right=-1;
solve1=solveMazeManhattanDFS(maze,col+1,row);
if(solve1)
return solveMazeManhattanDFS(maze,col+1,row);
}
if(up!=-1&&up==man[0]){
maze->cells[row][col]='.';
up=-1;
solve1=solveMazeManhattanDFS(maze,col,row-1);
if(solve1)
return solveMazeManhattanDFS(maze,col,row-1);
}
}

if(man[1]!=-1){
if(solve1!=1){
	if(left!=1 &&left==man[1]){
		maze->cells[row][col]='.';
		solve2=solveMazeManhattanDFS(maze,col-1,row);
		left=-1;
	if (solve2==1)
		return solveMazeManhattanDFS(maze,col-1,row);
	}
	if(down!=-1&&down==man[1]){
	maze->cells[row][col]='.';
	solve2=solveMazeManhattanDFS(maze,col,row+1);
	down=-1;
	if (solve2==1)
		return solveMazeManhattanDFS(maze,col,row+1);
	}
	if(right!=-1&&right==man[1]){
	maze->cells[row][col]='.';
	solve2=solveMazeManhattanDFS(maze,col+1,row);
	right=-1;
	if(solve2)
		return solveMazeManhattanDFS(maze,col+1,row);
	}
	if(up!=-1&&up==man[1]){
	maze->cells[row][col]='.';
	solve2=solveMazeManhattanDFS(maze,col,row-1);
	up=-1;
		if(solve2)
			return solveMazeManhattanDFS(maze,col,row-1);
	}

}
}

if(man[2]!=-1){
if(solve1!=1 && solve2!=1){
	if(left!=1 &&left==man[2]){
		maze->cells[row][col]='.';
		solve3=solveMazeManhattanDFS(maze,col-1,row);
		left=-1;
	if(solve3)
	return solveMazeManhattanDFS(maze,col-1,row);
	}
	if(down!=-1&&down==man[2]){
	maze->cells[row][col]='.';
	solve3=solveMazeManhattanDFS(maze,col,row+1);
	down=-1;
	if(solve3)
	return solveMazeManhattanDFS(maze,col,row+1);
	}
	if(right!=-1&&right==man[2]){
	maze->cells[row][col]='.';
	solve3=solveMazeManhattanDFS(maze,col+1,row);
	right=-1;
	if(solve3)
	return solveMazeManhattanDFS(maze,col+1,row);
	}
	if(up!=-1&&up==man[2]){
	maze->cells[row][col]='.';
	solve3=solveMazeManhattanDFS(maze,col,row-1);
	up=-1;
	if(solve3)
	return solveMazeManhattanDFS(maze,col,row-1);
	}

}
}

if(man[3]!=-1){
if(solve1!=1 && solve2!=1 && solve3!=1){
	if(left!=1 &&left==man[3]){
		maze->cells[row][col]='.';
		solve4=solveMazeManhattanDFS(maze,col-1,row);
		left=-1;
	if(solve4)
	return solveMazeManhattanDFS(maze,col-1,row);
	}
	if(down!=-1&&down==man[3]){
	maze->cells[row][col]='.';
	solve4=solveMazeManhattanDFS(maze,col,row+1);
	down=-1;
	if(solve4)
	return solveMazeManhattanDFS(maze,col,row+1);
	}
	if(right!=-1&&right==man[3]){
	maze->cells[row][col]='.';
	solve4=solveMazeManhattanDFS(maze,col+1,row);
	right=-1;
	if(solve4)
	return solveMazeManhattanDFS(maze,col+1,row);
	}
	if(up!=-1&&up==man[3]){
	maze->cells[row][col]='.';
	solve4=solveMazeManhattanDFS(maze,col,row-1);
	up=-1;
	if(solve4)
	return solveMazeManhattanDFS(maze,col,row-1);
	}

}
}

if(!(solve1 || solve2 || solve3 || solve4)){
	maze->cells[row][col]=' ';
	return 0;
}
*/
return 0; //idt this is necessary

}




