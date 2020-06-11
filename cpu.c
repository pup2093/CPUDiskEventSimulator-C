#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"




void printcpu(cpu* n){
	while (n != NULL){
		printf("%d", n->job);
		n = n->next;
	}
}

//Insert node at head of list
void pushcpu(cpu** head_ref, int new_job) 
{ 
    /* allocate node */
    cpu* new_node = (cpu*) malloc(sizeof(cpu)); 

   
    /*  put in the data  */
    new_node->job  = new_job; 

   
    /* Make next of new node as head */
    new_node->next = (*head_ref); 

   
    /*  move the head to point to the new node */
    (*head_ref) = new_node; 

    
} 


cpu* removecpu(cpu* head){
  cpu *temp =head;
  cpu *t;
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
     //free(temp);
     t->next=NULL; 
     free(temp);
  }    
  return head;

}

//void peek() note: peek will use similar functionality as printcpu, and then you simply return the job at the last node
int peekcpu(cpu* n){
	while (n->next != NULL){
		n = n->next;
	}
	return n->job;
}

int sizecpu(cpu* n){
	int j = 0;
	while(n != NULL){
		j++;
		n = n->next;
	}
	return j;

}


