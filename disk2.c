#include <stdio.h>
#include <stdlib.h>
#include "disk2.h"





void printdisk2(disk2* n){
	while (n != NULL){
		printf("%d", n->job);
		n = n->next;
	}
}

//Insert node at head of list
void pushdisk2(disk2** head_ref, int new_job) 
{ 
    /* allocate node */
    disk2* new_node = (disk2*) malloc(sizeof(disk2)); 
   
    /*  put in the data  */
    new_node->job  = new_job; 

   
    /* Make next of new node as head */
    new_node->next = (*head_ref); 
   
    /*  move the head to point to the new node */
    (*head_ref) = new_node; 

    
} 


disk2* removedisk2(disk2* head){
  disk2 *temp =head;
  disk2 *t;
  if(head->next==NULL)
  {
    free(head);
    head=NULL;
  }
  else
  {
     while(temp->next != NULL)
     {
        t=temp;
        temp=temp->next;
     }
     t->next=NULL; 
     free(temp);
  }    
  return head;

}

//void peek() note: peek will use similar functionality as printcpu, and then you simply return the job at the last node
int peekdisk2(disk2* n){
	while (n->next != NULL){
		n = n->next;
	}
	return n->job;
}

int sizedisk2(disk2* n){
	int j = 0;
	while(n != NULL){
		j++;
		n = n->next;
	}
	return j;

}
