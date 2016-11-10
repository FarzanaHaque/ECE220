#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>





sp_tuples * load_tuples(char* input_file)
{
FILE *f;
f=fopen(input_file,"r+");
if(f== NULL){
	printf("Cannot open %s\n", input_file);
return NULL;
}
sp_tuples *st;
st=(sp_tuples*)malloc(sizeof(sp_tuples));
//sp_tuples_node *head;
//head=(sp_tuples_node*)malloc(sizeof(sp_tuples_node));
int row,col;
fscanf(f,"%d %d",&row,&col);
//int current=st->tuples_head; //does it need to be *?
int nonzeros=0;
sp_tuples_node *current;
current=(sp_tuples_node*)malloc(sizeof(sp_tuples_node));
st->tuples_head=current;
while(!feof(f)){
	sp_tuples_node *new;
	new=(sp_tuples_node*)malloc(sizeof(sp_tuples_node));
	fscanf(f,"%d %d %lf\n",&(new->row),&(new->col),&(new->value));
	if(new->value!=0){
		current->next=new;
		current=new;
		nonzeros++;
	}
	if(new->value==0)
	free(new);
}
current->next=NULL;
st->nz=nonzeros;
return st;
}



double gv_tuples(sp_tuples * mat_t,int row,int col)

{
    return 0;
}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    return;
}



void save_tuples(char * file_name, sp_tuples * mat_t)
{

	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
sp_tuples *retmat;
retmat=(sp_tuples*)malloc(sizeof(sp_tuples));
	return retmat;
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
sp_tuples *retmat;
retmat=(sp_tuples*)malloc(sizeof(sp_tuples));
    return retmat;

}


	
void destroy_tuples(sp_tuples * mat_t){
	
    return;
}  






