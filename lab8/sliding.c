#include "sliding.h"
/*  Slide all values of array up
*/
void slide_up(int* my_array, int rows, int cols){
int i,j,target_row;
for (j=0;j<cols;j++){
	for(i=1;i<rows;i++){
		if(my_array[i*cols+j]!=-1){
				while(target_row<i&&my_array[target_row*cols+j]!=-1){
					target_row++;
					if(target_row<i){
						my_array[target_row*cols+j]=my_array[i*cols+j];
						my_array[i*cols+j]=-1;
					}
				}
		}
	}
}
    return;
}
/*
valgrind invalid read of size 4 bc integer
gdb
break sliding.c:16
run
p i tells you value of i

next
display i
display j
then next it'll show it
*/
