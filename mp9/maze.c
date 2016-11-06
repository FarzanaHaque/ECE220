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


int solveMazeManhattanDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
    
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




/*
int solveMazeManhattanDFS(maze_t * maze, int col, int row)
{
int erow=maze->endRow;
int ecol=maze->endColumn;
if(col==ecol&&row==erow)
return 1;
if(col<0||col>=maze->width||row<0||row>=maze->height)
return 0;
if(maze->cells[row][col]!= EMPTY &&  maze->cells[row][col]!=START)
return 0;

if(maze->cells[row][col]!=START)
maze->cells[row][col]=PATH;

int Manleft,Mandown,Manright,Manup=-1;
//initializing manhattan distances
if(col>0){
Manleft=abs(row-erow)+abs(col-1-ecol);
}
if(row<erow-1){
Mandown=abs(row+1-erow)+abs(col-ecol);
}
if(col<ecol-1){
Manright=abs(row-erow)+abs(col+1-ecol);
}
if(row>0){
Manup=abs(row-1-erow)+abs(col-ecol);
}
   if (Manleft <= Manup && Manleft <= Mandown && Manleft <= Manright) {
      if (maze->cells[row][col-1] !=EMPTY && solveMazeManhattanDFS(maze, col-1, row)) return 1; //check left
      //manight second smallest
      if (Manright <= Manup && Manright <= Mandown) {
         if (maze->cells[row][col+1] !=EMPTY  && solveMazeManhattanDFS(maze, col+1, row)) return 1;   //check right
         //left, right, up, down
         if (Manup <= Mandown) {








           if (maze->cells[row-1][col] !=EMPTY && solveMazeManhattanDFS(maze, col, row-1)) return 1;
           if ( maze->cells[row+1][col] !=EMPTY && solveMazeManhattanDFS(maze, col, row+1)) return 1;
         }
         //left, right, down, up
         else {
           if (maze->cells[row+1][col] != EMPTY && solveMazeManhattanDFS(maze, col, row+1)) return 1;
           if (maze->cells[row-1][col] !=EMPTY && solveMazeManhattanDFS(maze, col, row-1)) return 1;
         }




      }




//if(col==48&&row==1)
    //printf("end111111\n");
    //manup second smallest
     if (Manup <= Mandown && Manup <= Mandown) {
       //left, up, right, down
        if (maze->cells[row-1][col] !=EMPTY && solveMazeManhattanDFS(maze, col, row-1)) return 1; //check up
       if (Manright <= Mandown) {
           if (maze->cells[row][col+1] !=EMPTY && solveMazeManhattanDFS(maze, col+1, row)) return 1;
           if (maze->cells[row+1][col] !=EMPTY && solveMazeManhattanDFS(maze, col, row+1)) return 1;
       }
       else {//left, up, down, right
           if (maze->cells[row+1][col] !=EMPTY && solveMazeManhattanDFS(maze, col, row+1)) return 1;
           if (maze->cells[row][col+1] !=EMPTY && solveMazeManhattanDFS(maze, col+1, row)) return 1;
       }
     }
     else { //mandown is second smallest
       if (maze->cells[row+1][col] !=EMPTY && solveMazeManhattanDFS(maze, col, row+1)) return 1; //check down
       //left, down, up, right
       if (Manup <= Manright){
         if (maze->cells[row-1][col] !=EMPTY && solveMazeManhattanDFS(maze, col, row-1)) return 1;
         if (maze->cells[row][col+1] !=EMPTY && solveMazeManhattanDFS(maze, col+1, row)) return 1;
       }
       else {//left, down, right, up
         if ( maze->cells[row][col+1] !=EMPTY && solveMazeManhattanDFS(maze, col+1, row)) return 1;
         if (maze->cells[row-1][col] !=EMPTY && solveMazeManhattanDFS(maze, col, row-1)) return 1;
       }
     }
   }


//if(col==48&&row==1)printf("222222\n");
   //if manright is smallest
   if (Manright <= Manup && Manright <= Mandown && Manright <= Manleft) {
     if (solveMazeManhattanDFS(maze, col+1, row)) return 1; //check right
     if(Manleft <= Manup && Manleft <=Mandown) {
      //if left is second smallest
       if(solveMazeManhattanDFS(maze, col-1, row)) return 1; //check left
       //right, left, up, down
       if(Manup <= Mandown) {
           if (solveMazeManhattanDFS(maze, col, row-1)) return 1;
           if (solveMazeManhattanDFS(maze, col, row+1)) return 1;
       }
       else { //right, left, down, up)
          if (solveMazeManhattanDFS(maze, col, row+1)) return 1;
          if (solveMazeManhattanDFS(maze, col, row-1)) return 1;
       }
     }




     //if up is second smallest
    if(Manup <= Manleft && Manup <= Mandown) {
     if (solveMazeManhattanDFS(maze, col, row-1)) return 1; //check up
     //right, up, left, down
     if (Manleft <= Mandown) {
         if (solveMazeManhattanDFS(maze, col-1, row)) return 1;
         if (solveMazeManhattanDFS(maze, col, row+1)) return 1;
     }
     else {//right, up, down, left
        if (solveMazeManhattanDFS(maze, col, row+1)) return 1;
         if (solveMazeManhattanDFS(maze, col-1, row)) return 1;
     }
    }
    //if down is second smallest
    if (Mandown <= Manleft && Mandown <= Manup) {
      if (solveMazeManhattanDFS(maze, col, row+1)) return 1; //check down
      //right, down, left, up
      if (Manleft <= Manup) {
        if (solveMazeManhattanDFS(maze, col-1, row)) return 1;
        if (solveMazeManhattanDFS(maze, col, row-1)) return 1;
      }
      else { //right, down, up, left
        if (solveMazeManhattanDFS(maze, col, row-1)) return 1;
        if (solveMazeManhattanDFS(maze, col-1, row)) return 1;
      }
    }




   }














   //if manup is smallest
   if (Manup <= Mandown && Manup <= Manleft && Manup <= Manright) {
     if (solveMazeManhattanDFS(maze, col, row-1)) return 1; //check up
     //if left is second smallest
     if(Manleft <= Manright && Manleft <= Mandown){
       if (solveMazeManhattanDFS(maze, col-1, row)) return 1;//check left
       //up, left, down, right
       if(Mandown <= Manright) {
         if (solveMazeManhattanDFS(maze, col, row+1 )) return 1;
         if (solveMazeManhattanDFS(maze, col+1, row)) return 1;
       }
       else {//up, left, right, down
         if (solveMazeManhattanDFS(maze, col+1, row )) return 1;
         if (solveMazeManhattanDFS(maze, col, row+1)) return 1;
       }
     }
     //if right is second smallest
     if (Manright <= Mandown && Manright <= Manleft){
      if (solveMazeManhattanDFS(maze, col+1, row)) return 1; //check right
      //up, right, left, down
      if(Manleft <= Mandown) {
        if (solveMazeManhattanDFS(maze, col-1, row )) return 1;
        if (solveMazeManhattanDFS(maze, col, row+1)) return 1;
      }
      else { //up, right, down, left
        if (solveMazeManhattanDFS(maze, col, row+1 )) return 1;
        if (solveMazeManhattanDFS(maze, col-1, row)) return 1;
      }




     }
     else {//else down is second smallest
       if (solveMazeManhattanDFS(maze, col, row+1)) return 1; //check down
       //up, down, left, right.
       if (Manleft <= Manright){
         if (solveMazeManhattanDFS(maze, col-1, row)) return 1;
         if (solveMazeManhattanDFS(maze, col+1, row)) return 1;
       }
       else { //up, down, right, left
         if (solveMazeManhattanDFS(maze, col+1, row)) return 1;
         if (solveMazeManhattanDFS(maze, col-1, row)) return 1;
       }




     }
   }




  //else mandown is smallest
   else {
    if (solveMazeManhattanDFS(maze, col, row+1)) return 1; //check down
    //if left is second smallest
    if (Manleft <= Manright && Manleft <= Manup) {
      if (solveMazeManhattanDFS(maze, col-1, row)) return 1;//check left
      //down, left, right, up
      if (Manright <= Manup) {
        if(solveMazeManhattanDFS(maze, col+1, row)) return 1;
        if(solveMazeManhattanDFS(maze, col, row-1)) return 1;
      }
      else { //down, left, up, right
        if(solveMazeManhattanDFS(maze, col, row-1)) return 1;
        if(solveMazeManhattanDFS(maze, col+1, row)) return 1;
      }
    }
    //if right is second smallest
    if (Manright <= Manup && Manright <=Manleft) {
       if (solveMazeManhattanDFS(maze, col+1, row)) return 1; //check right
       //down, right, left, up
       if (Manleft <=Manup) {
         if(solveMazeManhattanDFS(maze, col-1, row)) return 1;
         if(solveMazeManhattanDFS(maze, col, row-1)) return 1;
       }
       else{//down, right, up, left
         if(solveMazeManhattanDFS(maze, col, row-1)) return 1;
         if(solveMazeManhattanDFS(maze, col-1, row)) return 1;
       }
    }
    //else up is the second smallest
    else {
      if(solveMazeManhattanDFS(maze, col, row-1)) return 1;//check up
      //down, up, left, right
      if(Manleft <= Manright) {
        if(solveMazeManhattanDFS(maze, col-1, row)) return 1;
        if(solveMazeManhattanDFS(maze, col+1, row)) return 1;
      }
      else {//down, up, right, left
        if(solveMazeManhattanDFS(maze, col+1, row)) return 1;
        if(solveMazeManhattanDFS(maze, col-1, row)) return 1;
      }
    }




   }


    //if no directions produce solutions, backtrack.
    if (maze->cells[row][col] != 83) {
    maze->cells[row][col] = VISITED; //mark current position as visited instead of solution
    }


    return 0;
}

/*

/*
int solve1,solve2,solve3,solve4=0;
if(col>0){
solve1=solveMazeManhattanDFS(maze,col-1,row);
if(solve1)
return 1;//solveMazeManhattanDFS(maze,col-1,row);
}
if(row<erow-1){
solve2=solveMazeManhattanDFS(maze,col,row+1);
if (solve2)
return 1;//solveMazeManhattanDFS(maze,col,row+1);
}
if(col<ecol-1){
solve3=solveMazeManhattanDFS(maze,col+1,row);
if(solve3)
return 1;//solveMazeManhattanDFS(maze,col+1,row);
}
if(row>0){
solve4=solveMazeManhattanDFS(maze,col,row-1);
if(solve4)
return 1;//solveMazeManhattanDFS(maze,col,row-1);
}

maze->cells[row][col]=EMPTY;

return 0; */

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

if(!(solve1 || solve2 || solve3 || solve4) && maze->cells[row][col]!=START){
	maze->cells[row][col]=VISITED;
	//return 0;
}*/

//return 0; //idt this is necessary
//}




