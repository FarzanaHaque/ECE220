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
int solveMazeManhattanDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
    return 0;
}
