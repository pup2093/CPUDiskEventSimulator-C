#include <stdio.h>
#include <stdlib.h>
#include "disk1.h"


void printdisk1(disk1* n){
	while (n != NULL){
		printf("%d", n->job);
		n = n->next;
	}
}

//Insert node at head of list
void pushdisk1(disk1** head_ref, int new_job) 
{ 
    /* allocate node */
    disk1* new_node = (disk1*) malloc(sizeof(disk1)); 
   
    /*  put in the data  */
    new_node->job  = new_job; 

   
    /* Make next of new node as head */
    new_node->next = (*head_ref); 
   
    /*  move the head to point to the new node */
    (*head_ref) = new_node; 

    
} 


disk1* removedisk1(disk1* head){
  disk1 *temp =head;
  disk1 *t;
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
     free(t->next);
     t->next=NULL; 
  }  
  return head;  

}

//void peek() note: peek will use similar functionality as printcpu, and then you simply return the job at the last node
int peekdisk1(disk1* n){
	while (n->next != NULL){
		n = n->next;
	}
	return n->job;
}

int sizedisk1(disk1* n){
	int j = 0;
	while(n != NULL){
		j++;
		n = n->next;
	}
	return j;

}