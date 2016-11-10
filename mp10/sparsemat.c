#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>
/*
 q = list;
  while(q->next != NULL && strcmp(q->next->str, data) < 0) {
   q = q->next;
  }
  p->next = q->next;
  q->next = p;*/

void insert( sp_tuples_node ** head, sp_tuples_node* new ){
int nr=new->row;
int nc=new->col;

sp_tuples_node* curr;
curr=(sp_tuples_node*)malloc(sizeof(sp_tuples_node));
curr=*head;
while(curr->next!=NULL && (nr>curr->row||(nr==curr->row&&nc>curr->col))){
			curr=curr->next;
	}
	new->next=curr->next;
	curr->next=new;
   
   
   
 free(curr);
}

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
sp_tuples_node *a;
a=mat_t->tuples_head;
while(a!=NULL||(a->row==row &&a->col==col)){
a=a->next;
}
    return a->value;
}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    return;
}



void save_tuples(char * file_name, sp_tuples * mat_t)
{
FILE *f;
f=fopen(file_name,"w");
if(f== NULL){
	printf("Cannot open %s\n", file_name);
return NULL;
}

	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
if(matA->m!=matB->m || matA->n!=matB->n || (matA->nz==0 && matB->nz==0))
return NULL;

sp_tuples *retmat;
retmat=(sp_tuples*)malloc(sizeof(sp_tuples));
retmat->m=matA->m;
retmat->n=matA->n;


sp_tuples_node *a;
//a=(sp_tuples_node*)malloc(sizeof(sp_tuples_node));
a=matA->tuples_head;
retmat->nz=matA->nz;
sp_tuples_node *c;
c=(sp_tuples_node*)malloc(sizeof(sp_tuples_node));
while(a!=NULL){


c->row=a->row;
c->col=a->col;
c->value=a->value;
//printf("a_val=%lf",a->value);
//printf("c=%lf\n",c->value);	
a=a->next;
c=c->next;

}
sp_tuples_node *b;
b=(sp_tuples_node*)malloc(sizeof(sp_tuples_node));
b=matB->tuples_head;
while(b!=NULL){

	if(!(gv_tuples(retmat,b->row,b->col))){
		c=(sp_tuples_node*)malloc(sizeof(sp_tuples_node));
		c->row=b->row;
		c->col=b->col;
		}
	c->value+=b->value;

b=b->next;
c=c->next;

} 


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






