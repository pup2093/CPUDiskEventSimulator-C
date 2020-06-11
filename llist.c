#include <stdio.h>
#include <stdlib.h>

//This linked list (which is made from a struct) is used for the cpu, disk1, and disk2

typedef struct cpu {
	int job;
	struct cpu *next; 
} cpu;

typedef struct disk1 {
	int job;
	struct disk1 *next; 
} disk1;

typedef struct disk2 {
	int job; 
	struct disk2 *next; 
} disk2;



//function to print linked list
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
     while(temp->next != NULL && temp != NULL)
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


//Now create identical functions for disk1 and disk2

//disk1 functions

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


void removedisk1(disk1* head){
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

//disk2 functions

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


void removedisk2(disk2* head){
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
     free(t->next);
     t->next=NULL; 
  }    

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






int main()
{

  


  cpu* cpuhead = NULL;
  disk1* disk1head = NULL;
  disk2* disk2head = NULL;


  pushcpu(&cpuhead, 6);
  pushcpu(&cpuhead, 8);
  pushcpu(&cpuhead, 9);

  cpuhead = removecpu(cpuhead);
  //cpuhead = removecpu(cpuhead);
  //cpuhead = removecpu(cpuhead);

  //pushdisk1(&disk1head, 12);


  //printcpu(cpuhead);
  printf("\n");

  //printf("%d", peekcpu(cpuhead));



  printcpu(cpuhead);
  
  //printdisk1(disk1head);

  //printf("%d", sizedisk1(disk1head));

  
  return 0;
}