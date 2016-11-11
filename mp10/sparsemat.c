#include "sparsemat.h"




#include <stdio.h>
#include <stdlib.h>
/*
For load_tuples, we open the text file and return null if we can't
we intiialze a tuple, scan the first 2 integers for the row & col of the tuple
intialize non zeros to 0;
we set up the head and new nodes
we scan each line of the file and putting row,col & value to new
and if new->value != zero we settuples and increment non zeros by one
at the end we set our tuples's nz to nonzeros and return our tuple

for gv we traverse our tuple until we reach a node with the given row col, otherwise if we reach the end & row,col is within bounds we know it's zero

for set tuples, we set a new node with the given values if head is null,set to new node ,if new node has coordinates less than current head, set it to head and it's next is old head
otherwise we go through the list to find where we should put it

save tuples is similar to load_tuples in that it modifies a file but this time it's writing instead reading
we tried implement add & multiply but it didn't work
destroy just frees all the memory
*/





sp_tuples * load_tuples(char* input_file){


    
    FILE *f;
f=fopen(input_file,"r");
if(f== NULL){
    printf("Cannot open %s\n", input_file);
return NULL;
}
sp_tuples *st;
st=(sp_tuples*)malloc(sizeof(sp_tuples));

fscanf(f,"%i %i",&(st->m),&(st->n));//rows & cols
int nonzeros=0;




sp_tuples_node *head;
head=(sp_tuples_node*)malloc(sizeof(sp_tuples_node));
head=NULL;
st->tuples_head=head; 
    sp_tuples_node *new; //temp node for each line
    new=(sp_tuples_node*)malloc(sizeof(sp_tuples_node));
while(!feof(f)){
    fscanf(f,"%d %d %lf\n",&(new->row),&(new->col),&(new->value));
    if(new->value!=0){
set_tuples(st, new->row, new->col, new->value);
        nonzeros++;
    }


}
new->next=NULL;//is this necessary?
st->nz=nonzeros;
fclose(f);
free(new);
free(head);//these were just for the function
return st;         
}


double gv_tuples(sp_tuples * mat_t,int row,int col)




{
if(row<0 || col<0 || row+1>mat_t->n ||col+1>mat_t->m)
return 0; //means out of bound
    sp_tuples_node *current = (sp_tuples_node *)malloc(sizeof(sp_tuples_node));
    current = mat_t->tuples_head;
    while(current != NULL)
    {
        if(current->row == row && current->col == col)
            return current->value;
        current = current->next;
    }
    return 0; //it's empty
}


void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    sp_tuples_node *new=(sp_tuples_node*)malloc(sizeof(sp_tuples_node));
    new->row=row;
    new->col=col;
    new->value=value;
    new->next=NULL; ///this might be bad
if(mat_t->tuples_head==NULL){//if head is null,set to new node
    mat_t->tuples_head=new;
    return;
}
else if(row<mat_t->tuples_head->row||(row==mat_t->tuples_head->row&&col<mat_t->tuples_head->col))//if new node has coordinates less than current head, set it to head and it's next is old head
{
    new->next=mat_t->tuples_head;
    mat_t->tuples_head=new;
}


else //go through list
{
    sp_tuples_node *previous=(sp_tuples_node*)malloc(sizeof(sp_tuples_node));
    sp_tuples_node *temp=(sp_tuples_node*)malloc(sizeof(sp_tuples_node));    
previous=mat_t->tuples_head;
temp=mat_t->tuples_head->next;
    while(temp!=NULL && (row>temp->row ||(row==temp->row && col>temp->col))){
        previous=temp;
        temp=temp->next;
    }
	/*if(row==temp->row && col==temp->col){//if coordinates equal
	sp_tuples_node *delete=(sp_tuples_node*)malloc(sizeof(sp_tuples_node));
	delete=temp;
	new->next=temp->next;
	temp=new;
	previous->next=temp;
	free(delete);
	}*/
    if(temp==NULL)
    {
        previous->next=new;
    }
    else
    {
        new->next=temp;
        previous->next=new;
    }
}


    return;
free(new);
free(previous);
free(temp); //bbecause we ussed up memory
}



/*Implement this function for Lab 10*/
/*
void removeDuplicates(node* head){
//head doesn't change what it's point to so only single pointer
node* current= head;
node* delete=NULL;
//node* temp;
while (current!=NULL && current->next !=NULL){
//add the AND state because other in the if it'll check current->next->data and it'll result in segfault
	if(current->data == current->next->data){
		delete=current->next;
		current->next=current->next->next;
		free(delete); //free AFTER getting info from that node
	}
	else
		current=current->next;
}
}*/
//while(temp!=NULL && (row>temp->row ||(row==temp->row && col>temp->col))){
	/*if(current->data == current->next->data){
		delete=current->next;
		current->next=current->next->next;
		free(delete); //free AFTER getting info from that node
	}*/

//helper functions
int nodeExists(sp_tuples * mat_t, int row, int col, double value)
{
    sp_tuples_node *current = (sp_tuples_node *)malloc(sizeof(sp_tuples_node));
    current = mat_t->tuples_head;
    //sp_tuples_node *prev = NULL;
    while(current != NULL)
    {
        if(current->row == row && current->col == col)
        {
            return 1;
        }
        current = current->next;
    }
    return 0;
}




void deleteNode(sp_tuples * mat_t, int row, int col)
{
    sp_tuples_node *current = (sp_tuples_node *)malloc(sizeof(sp_tuples_node));
    current = mat_t->tuples_head;
    sp_tuples_node *prev = (sp_tuples_node *)malloc(sizeof(sp_tuples_node));
    prev = NULL;
    sp_tuples_node *delete = (sp_tuples_node *)malloc(sizeof(sp_tuples_node));
    delete = NULL;
    while(current != NULL)
    {
        if(current->row == row && current->col == col)
        {
            delete = current;
            prev->next = current->next;
            free(delete);
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }
    return;
}




void save_tuples(char * file_name, sp_tuples * mat_t)
{
    FILE *outf;
    
    if( (outf = fopen(file_name, "w")) == NULL)
    {
        printf("Unable to open file %s for writing\n", file_name);
    }
    
    fprintf(outf, "%i %i\n", mat_t->m, mat_t->n);
    
    sp_tuples_node *current = mat_t->tuples_head;
    while(current != NULL)
    {
        fprintf(outf, "%i %i %lf\n", current->row, current->col, current->value);
        current = current->next;
    }
    
    fclose(outf);
    
    return;
}












sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
    //initiate matrix c with same size as a and b and all entries = 0
if(matA->n!=matB->m||matA->m!=matB->m)// ||(matA->nz=matB->nz && matA->nz==0) if both are empty?
return NULL;
    sp_tuples *retmat = (sp_tuples *)malloc(sizeof(sp_tuples));
    retmat->m = matA->m;
    retmat->n = matA->n;
    //all entries = 0???????????
    //int i,j;
    //sp_tuples_node * newNode = NULL;
    sp_tuples_node *current = NULL;
sp_tuples_node *a=matA->tuples_head;
    sp_tuples_node *headC = NULL;
while(a!=NULL)
{
current->row=a->row;
current->col=a->col;
current->value=a->value;
if(headC==NULL)
{headC=current;} //might have other pointer stuff to deal with
a=a->next;
current=current->next;
}

    return retmat;
}












sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){
       sp_tuples *retmat = (sp_tuples *)malloc(sizeof(sp_tuples));
       retmat->m = matA->m;
    retmat->n = matB->m;
   //all entries = 0???????????
    int i,j;
    sp_tuples_node *newNode = NULL;
    sp_tuples_node *current = NULL;
    sp_tuples_node *headC = current;
    for(i = 0; i < matA->m; i++) //A: mAxnA
    {
        for(j = 0; j< matB->m; j++) //B: mBxnB
        {
            newNode->row = i;
            newNode->col = j;
            newNode->value = 0;
            current->next = newNode;
            current = current->next;
        }
    }
    
    retmat->tuples_head = headC;
    current = headC;
    
        
    sp_tuples_node *currentA = matA->tuples_head;
    sp_tuples_node *currentB = matB->tuples_head;
//I THINK THIS IS WRONGGGGGGGGGGGGGG WTF.
    //for every non-zero entry in A
    for(i = 0; i < matA->m; i++)
    {    
        //for every non-zero entry in B
        for(j = 0; j< matA->n; j++)
        {
            //for every non-zero entry in A
            if(currentA->value != 0 && currentA->row == i && currentA->col == j)
            {
                //for every nonzero element in B with row iB = jA
                if(currentB->value != 0 && currentB->row == currentA->col)
                {
                    current->value += current->value + currentA->value + currentB->value;
                    currentA = currentA->next;
                    currentB = currentB->next;
                }
            }
            current = current->next;
        }
    }




    return retmat;
}




void destroy_tuples(sp_tuples * mat_t){
      //free list
     sp_tuples_node *head = mat_t->tuples_head;
     sp_tuples_node *delete;
    while(head!=NULL){
        delete = head;
        head = head->next;
        free(delete);
    }
    free(mat_t);
    mat_t = NULL;
    
    return;
} 





