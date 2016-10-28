#include "game.h"
/*
for make_game i create a game with rows & cols specified by the user, set score to 0 and all the cells to -1
for remake game, i do the same thing but with a different game
for get_cell, if the user input a valid row & col within the rows and cols of the current game, i return the cell, otherwise i return null
for move w, i go thru each column, set lcr (last combined row) to =0, go through each of the m elements within the column, check if the current value is empty
if not i find target_row through a for loop, target_row is the first row that is empty and is less than current row number
if target row is less than current row #, i move current row value into target row and clear row
if the  row above != lcr we know tile hasn't already been merged so then we check to see if targetrow and above target row are same values
we merge with the above row being the sum and the target row value being -1
now we update lcr to row above target row

move_a is exactly the same but we switch cols & rows, eg we do outter for loop each of the m rows, we check the col to the left of target col is not equal to lcc etc
move_s (down) & move_d (right) are very similar but now i decided to start from the bottom right corner
and we initalize lcc=((cur_game->cols)) instead of -1, because it's also out of the legal limits of the board aka col=-1 isn't on the board & neither is col=(cur_game->cols)

legal_move_check goes through the game board and if there's any empty cells it'll return 1 because you still have legal moves left
otherwise if the board is filled, you need to check to see if any of the moves(s,a,d,w) are valid, if they're valid, calling them returns a 1, so you make moves= the or of all 4 moves
and return moves 
*/

game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
mygame->rows=rows;
mygame->cols=cols;
mygame->score=0;
for(int i=0;i<rows*cols;i++){
mygame->cells[i]=-1; //set every cell to empty
}
    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct

(*_cur_game_ptr)->rows=new_rows;
(*_cur_game_ptr)->cols=new_cols;
(*_cur_game_ptr)->score=0;
for(int i=0;i<new_rows*new_cols;i++){
(*_cur_game_ptr)->cells[i]=-1;
}
	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
if ((row<cur_game->rows) && (col<cur_game->cols) &&row>=0 && col >=0)
{
return (cur_game->cells)+(row*(cur_game->cols)+col);
}
    return NULL;
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //YOUR CODE STARTS HERE
int i,j,target_row,lcr,flag=0;
//flag set to 1 if valid move
for (j=0;j<(cur_game->cols);j++){
	lcr=-1; //have to make initialize, decided -1 whenever starting new column 
	for(i=0;i<cur_game->rows;i++){
		if(*get_cell(cur_game,i,j)!=-1){//current row value not empty
			for(target_row=0;(target_row<i)&&(*get_cell(cur_game,target_row,j)!=-1);target_row++){
			}//find first available target row
			
			if(target_row<i){//target row less than i
				*get_cell(cur_game,target_row,j)=*get_cell(cur_game,i,j);//copy current row value into target row
				*get_cell(cur_game,i,j)=-1; //clear target row value
				flag=1; //so we'll return 1 bc successful slide
			}
			if((target_row-1)!=lcr){//row above target row not equal to lcr 
				if(*get_cell(cur_game,target_row,j)==(*get_cell(cur_game,target_row-1,j))){//value above & below target row same
				*get_cell(cur_game,target_row-1,j)=2*(*get_cell(cur_game,target_row,j));//row above= sum
				*get_cell(cur_game,target_row,j)=-1;//clear target row
				lcr=target_row-1; //lcr assigned to row above
				cur_game->score+=(*get_cell(cur_game,target_row-1,j)); //increment score
				flag=1;
				}
			
			}

		} 
	}
} 
    return flag;

};

int move_a(game * cur_game) //slide left
{
int i,j,target_col,lcc,flag=0;
for (i=0;i<(cur_game->rows);i++){
	lcc=-1; //have to make initialize, decided -1 whenever starting new row
	for(j=0;j<cur_game->cols;j++){
		if(*get_cell(cur_game,i,j)!=-1){
			for(target_col=0;(target_col<j)&&(*get_cell(cur_game,i,target_col)!=-1);target_col++){
			}
			if(target_col<j){
				*get_cell(cur_game,i,target_col)=*get_cell(cur_game,i,j);
				*get_cell(cur_game,i,j)=-1;
				flag=1;
			}
			if((target_col-1)!=lcc){
				if(*get_cell(cur_game,i,target_col)==(*get_cell(cur_game,i,target_col-1))){
				*get_cell(cur_game,i,target_col-1)=2*(*get_cell(cur_game,i,target_col));
				*get_cell(cur_game,i,target_col)=-1;	
				lcc=target_col-1;
				cur_game->score+=(*get_cell(cur_game,i,target_col-1));
				flag=1;
				}
			}
			
		}
	}
}
    return flag;
};

int move_d(game * cur_game){ //slide to the right
int i,j,target_col,lcc,flag=0;
//starting from bottom right corner to top left corner
for (i=(cur_game->rows)-1;i>=0;i--){
	lcc=((cur_game->cols)); //value when starting new column
	for(j=(cur_game->cols)-1;j>=0;j--){
		if(*get_cell(cur_game,i,j)!=-1){
			for(target_col=(cur_game->cols)-1;(target_col>j)&&(*get_cell(cur_game,i,target_col)!=-1);target_col--){
			}
			if(target_col>j){
				*get_cell(cur_game,i,target_col)=*get_cell(cur_game,i,j);
				*get_cell(cur_game,i,j)=-1;
				flag=1;
			}
			if((target_col+1)!=lcc){
				if(*get_cell(cur_game,i,target_col)==(*get_cell(cur_game,i,target_col+1))){
				cur_game->cells[i*(cur_game->cols)+target_col+1]= (*get_cell(cur_game,i,target_col)+(*get_cell(cur_game,i,target_col)));
				cur_game->cells[i*(cur_game->cols)+target_col]=-1;
				lcc=target_col+1;
				cur_game->score+=(*get_cell(cur_game,i,target_col+1));
				flag=1;
				}
			}
			
		}
	}
}
    return flag;
};
int move_s(game * cur_game) //slide down
{
   //starting from bottom right corner to top left corner
int i,j,target_row,lcr,flag=0;
for (j=(cur_game->cols)-1;j>=0;j--){
	lcr=((cur_game->rows)); //have to initialize to value of last row
	for(i=((cur_game->rows)-1);i>=0;i--){//have to start with i=1 bc otherwise won't every have targetrow<i
		if(*get_cell(cur_game,i,j)!=-1){
			for(target_row=(cur_game->rows)-1;(target_row>i)&&(*get_cell(cur_game,target_row,j)!=-1);target_row--){
			}
			if(target_row>i){
				*get_cell(cur_game,target_row,j)=*get_cell(cur_game,i,j);
				*get_cell(cur_game,i,j)=-1;
				flag=1;
			}
			if((target_row+1)!=lcr){
				if(*get_cell(cur_game,target_row,j)==(*get_cell(cur_game,target_row+1,j))){
				*get_cell(cur_game,target_row+1,j)=2*(*get_cell(cur_game,target_row,j));
				*get_cell(cur_game,target_row,j)=-1;
				lcr=target_row+1;
				cur_game->score+=(*get_cell(cur_game,target_row+1,j));
				flag=1;
				}
			}
			
		}
	}
}
   
    return flag;
};




int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
int i,j,moves=0; //moves contains the return value
for(i=0;i<(cur_game->rows);i++){
	for(j=0;j<(cur_game->cols);j++){
		if((cur_game->cells[i*(cur_game->cols)+j])==-1){//empty cell on board
			moves=1;//then tehre's still legal moves
			return moves;		
		}
	}
}
moves=(move_a(cur_game) || move_s(cur_game) || move_d(cur_game) || move_w(cur_game)); //if any of the moves return 1, then there's still legal moves
	return moves; 
  
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
