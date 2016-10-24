#include "sliding.h"
/*  Slide all values of array up
*/
void slide_up(int* my_array, int rows, int cols){
int i,j,target_row=0;
int a;
for (j=0;j<cols;j++){
	//target_row=0; //have to make zero again
	for(i=1;i<rows;i++){//have to start with i=1 bc otherwise won't every have targetrow<i
		if(my_array[i*cols+j]!=-1){
			for(target_row=0;(target_row<i)&&(my_array[target_row*cols+j]!=-1);target_row++){
			}
			if(target_row<i){
				my_array[target_row*cols+j]=my_array[i*cols+j];
				my_array[i*cols+j]=-1;
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
