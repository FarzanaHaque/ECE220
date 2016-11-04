#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
	int data;
     	struct node_t *next;
} node;
/*
//insert new node at front & change head ptr to newnode
void addNode (node** head) {
pass a pointer by reference
right now head pointing to node1
but want new node to point to what head point to 
head should now point address of pointer (node**)
node is a struct, *node is the address of struct/pointer



}*/
void printList(node * Node) {
	int j = 1;
        printf("data = ");
	while( Node != NULL){
		printf(" %d", Node->data);
		Node = Node->next;
		j++;
	}
        printf("\n");
}

/*Implement this function for Lab 10*/
void reverse(node** head){
///can only pass variables (aka pointers) not addresses
//so since we change what's in head, we can't head we must change the pointer for head
//double start bc need to change head is pointing too (a double pointer)
node* current = *head;
node* prev= NULL;
node* next;
while (current != NULL){ //transverse linked list
next=current->next;
current=current->next=prev;
prev=current;
current=next;
//LOOOOK OVER THIS PART TO SEE WHY WORKS!!!!
}

*head=prev;
//head=*node location, but need to change head location =**node 

}

/*Implement this function for Lab 10*/
void removeDuplicates(node* head){
//head doesn't change what it's point to so only single pointer
node* current= head
//node* temp;
while (current!=NULL && current>next !=NULL){
//add the AND state because other in the if it'll check current->next->data and it'll result in segfault
	if(current->data == current->next->data){
		current->next=current->next->next;
		free(current->next); //free AFTER getting info from that node
	}
	else
		current=current->next;
}
}

int main() {
    node * head = NULL;
    node * temp;
    int i = 0;
    int j = 0;
    //Create Sorted linked list with repeats
    for(i = 9; i > 0; i--) {
        if(i%3==0){
            for(j = 0; j < 3; j++){
                temp = head;
	        head = (node *) malloc(sizeof(node));
	        head->data = i;
	        head->next = temp;     
            }
        }else{
            temp = head;
            head = (node *) malloc(sizeof(node));
            head->data = i;
            head->next = temp;
        }
    }
    printf("Printing the original list:\n");
    printList(head);
    removeDuplicates(head);
    printf("Printing the removeDuplicates list:\n");
    printList(head);
    reverse(&head);
    printf("Printing the reverse list:\n");
    printList(head);
    //free list
    while(head!=NULL){
        temp = head;
        head = head->next;
        free(temp);
    }
    return 0;
}
