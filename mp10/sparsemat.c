#include "sparsemat.h"




#include <stdio.h>
#include <stdlib.h>








sp_tuples * load_tuples(char* input_file){


    
    FILE *f;
f=fopen(input_file,"r");
if(f== NULL){
    printf("Cannot open %s\n", input_file);
return NULL;
}
sp_tuples *st;
st=(sp_tuples*)malloc(sizeof(sp_tuples));
int row,col;
fscanf(f,"%d %d",&row,&col);
int nonzeros=0;




sp_tuples_node *head;
head=(sp_tuples_node*)malloc(sizeof(sp_tuples_node));
head=NULL;
st->tuples_head=head; //will head pointer keep on changing
    sp_tuples_node *new;
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
return st;         
}


void printList(sp_tuples_node * Node) {
    int j = 1;
        printf("data = ");
    while( Node != NULL){
        printf("node %i: %d %d %lf \n", j, Node->row, Node-> col, Node->value);
        Node = Node->next;
        j++;
    }
        printf("\n");
}




///
double gv_tuples(sp_tuples * mat_t,int row,int col)




{
    sp_tuples_node *current = (sp_tuples_node *)malloc(sizeof(sp_tuples_node));
    current = mat_t->tuples_head;
    while(current != NULL)
    {
        if(current->row == row && current->col == col)
            return current->value;
        current = current->next;
    }
    return 0;
}












void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    sp_tuples_node *new=(sp_tuples_node*)malloc(sizeof(sp_tuples_node));
    new->row=row;
    new->col=col;
    new->value=value;
    new->next=NULL; ///this might be bad
if(mat_t->tuples_head==NULL){
    mat_t->tuples_head=new;
    return;
}
else if(row<mat_t->tuples_head->row||(row==mat_t->tuples_head->row&&col<mat_t->tuples_head->col))
{
    new->next=mat_t->tuples_head;
    mat_t->tuples_head=new;
}


else
{
    sp_tuples_node *previous=(sp_tuples_node*)malloc(sizeof(sp_tuples_node));
    sp_tuples_node *temp=(sp_tuples_node*)malloc(sizeof(sp_tuples_node));    
previous=mat_t->tuples_head;
temp=mat_t->tuples_head->next;
    while(temp!=NULL && (row>temp->row ||(row==temp->row && col>temp->col))){
        previous=temp;
        temp=temp->next;
    }
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
}


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
    sp_tuples *retmat = (sp_tuples *)malloc(sizeof(sp_tuples));
    retmat->m = matA->m;
    retmat->n = matA->n;
    //all entries = 0???????????
    int i,j;
    sp_tuples_node * newNode = NULL;
    sp_tuples_node *current = NULL;
    sp_tuples_node *headC = current;
    for(i = 0; i < matA->m; i++)
    {
        for(j = 0; j< matA->n; j++)
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
    //for every non-zero entry in A
    for(i = 0; i < matA->m; i++)
    {
        for(j = 0; j< matA->n; j++)
        {
            if(currentA->value != 0 && currentA->row == i && currentA->col == j)
            {
                current->value+=currentA->value;
                currentA = currentA->next;
                
            }
            if(currentB->value != 0 && currentB->row == i && currentB->col == j)
            {
                current->value+=currentB->value;
                currentB = currentB->next;
            }
            current = current->next;
        }
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





