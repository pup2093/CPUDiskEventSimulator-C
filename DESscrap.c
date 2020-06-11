//This file will include all functions and data structure implementations that are in the header file
#include <stdio.h>
#include <stdlib.h>

#define INIT_TIME 0
#define FIN_TIME 100000
#define ARRIVE_MIN 10
#define ARRIVE_MAX 40
#define QUIT_PROB 0.2  //you'll generate a raondom number between 0 and 1 and compare to QUIT_PROB
#define CPU_MIN 5
#define CPU_MAX 25
#define DISK1_MIN 10
#define DISK1_MAX 30
#define DISK2_MIN 11
#define DISK2_MAX 31

//define events 
#define JOB_ARRIVES 1
#define CPU_FINISHED 2
#define DISK1_FINISHED 3
#define DISK2_FINISHED 4
#define SIMULATION_FINISHED 5

//global variables 
int jobcount = 0;
int timecount = 0; //might need a global time variable that is to be updated





//Note: After writing all data structures and functions in this file, make sure to put all of their definitions in the header file


//Data Structures 

//event queue
typedef struct node{

	int event; //event is an int because we made them named constants. When we need to log the file, of course we will write a string of event name corresponding to event constant 
	int time; //priority, which is time of event 
	int job; //job #
	struct node *next; //pointer to next node
	
} Event; 


// Function to Create A New Node
Event* newEvent(int e, int t, int j)     //(event, time(priority), job)
{
    Event* temp = (Event*)malloc(sizeof(Event));
    temp->event = e;
    temp->time = t;
    temp->job = j; 
    temp->next = NULL;
 
    return temp;
}

// Return the value at head without removing from list (Probably won't need this function for this program)
int peekevent(Event** head)
{
    return (*head)->event;
}
 
 // Removes the element with the
// highest priority from the list (lowest time)
void popevent(Event** head)
{
    Event* temp = *head;
    (*head) = (*head)->next;
    free(temp);
}

// Function to push according to priority. 
void pushevent(Event** head, int e, int t, int j)
{
    Event* start = (*head);
 
    // Create new Node
    Event* temp = newEvent(e, t, j);
 
    // Special Case: The head of list has lesser
    // priority than new node. So insert new
    // node before head node and change head node.
    if ((*head)->time > t) {
 
        // Insert New Node before head
        temp->next = *head;
        (*head) = temp;
    }
    else {
 
        // Traverse the list and find a
        // position to insert new node
        while (start->next != NULL &&
               start->next->time < t) {
            start = start->next;
        }
 
        // Either at the ends of the list
        // or at required position
        temp->next = start->next;
        start->next = temp;
    }
}
 
// Function to check is list is empty
int isEmptyevent(Event** head)
{
    return (*head) == NULL;
}
 




//FIFO queues (cpu, disk1, disk2)
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





//Random number generator
int generateRandom(int lower, int upper)
{
    
    
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
    
}









//Event Handlers
//first define all handlers as functions. Probably will move into a separte function file along with a header file later
//Note: the event-handler functions will include writing to the log file
void handle_job_arrival(cpu* cpuh, Event *eventh, FILE *file){ //transfers job into cpu
	fprintf(file, "%d", eventh->time);
    fputs(" ", file);
	fprintf(file, "%d", eventh->job);
	fputs(" jobarrives\n", file); 

	//add job to cpu queue
	pushcpu(&cpuh, eventh->job);

	//pop event
	popevent(&eventh);  //we can pop  at this point
    
    //generate new job
	timecount += generate_random_time(ARRIVE_MIN, ARRIVE_MAX);
	jobcount++;
	pushevent(&eventh, JOB_ARRIVES, timecount, jobcount);

	if(sizecpu(cpuh) == 1){ //if empty, process immediately. if size == 1, then that event is the only one in there
		
		timecount += generate_random_time(CPU_MIN, CPU_MAX);
		pushevent(&eventh, CPU_FINISHED, timecount, cpuh->job);
		cpuh = removecpu(cpuh);
		
	}else{
		timecount += generate_random_time(CPU_MIN, CPU_MAX);
	 	pushevent(&eventh, CPU_FINISHED, timecount, peekcpu(cpuh));
	 	cpuh = removecpu(cpuh);

	}

	/*generate new job
	timecount += generate_random_time(ARRIVE_MIN, ARRIVE_MAX);
	jobcount++;
	pushevent(&eventh, JOB_ARRIVES, timecount, jobcount);*/


}

void handle_finish_cpu(disk1 *disk1h, disk2* disk2h, Event *eventh, FILE *file){ //this includes random generation of cpu service time. Recall, once job finishes at cpu, if probability greater than .2, then it exits, if less then goes to disk

	fprintf(file, "%d", eventh->time);
    fputs(" ", file);
	fprintf(file, "%d", eventh->job);
	fputs(" jobfinishescpu\n", file);

	//probability that it exits system or gets sent to disk
	int probability = generate_probability(1,10);
	if(probability <= 2){ //job exits system and since its already removed from cpu, there's nothing to do
		;

	}else if (sizedisk1(disk1h) < sizedisk2(disk2h)){ //send to disk1
		pushdisk1(&disk1h, eventh->job);
		if(sizedisk1(disk1h) == 1){
			timecount += generate_random_time(DISK1_MIN, DISK1_MAX);
		    pushevent(&eventh, DISK1_FINISHED, timecount, disk1h->job);
			disk1h = removedisk1(disk1h);

		}else{
			timecount += generate_random_time(DISK1_MIN, DISK1_MAX);
	 	    pushevent(&eventh, DISK1_FINISHED, timecount, peekdisk1(disk1h));
	 	    disk1h = removedisk1(disk1h);

		}

	}else if (sizedisk1(disk1h) > sizedisk2(disk2h)){ //send to disk2
		pushdisk2(&disk2h, eventh->job);
		if(sizedisk2(disk2h) == 1){
			timecount += generate_random_time(DISK2_MIN, DISK2_MAX);
		    pushevent(&eventh, DISK2_FINISHED, timecount, disk2h->job);
			disk2h = removedisk2(disk2h);

		}else{
			timecount += generate_random_time(DISK2_MIN, DISK2_MAX);
	 	    pushevent(&eventh, DISK2_FINISHED, timecount, peekdisk2(disk2h));
	 	    disk2h = removedisk2(disk2h);

		}
	}

}

void handle_finish_disk1(cpu *cpuh, Event *eventh, FILE *file){ //once finished at disk, it gets transfered back to cpu
	fprintf(file, "%d", eventh->time);
    fputs(" ", file);
	fprintf(file, "%d", eventh->job);
	fputs(" jobfinishesdisk1\n", file);


	pushcpu(&cpuh, eventh->job);


}

void handle_finish_disk2(cpu *cpuh, Event *eventh, FILE *file){ //once finished at disk, it gets transfered back to cpu
	fprintf(file, "%d", eventh->time);
    fputs(" ", file);
	fprintf(file, "%d", eventh->job);
	fputs(" jobfinishesdisk2\n", file);


	pushcpu(&cpuh, eventh->job);


}



//Generators 
int generate_random_time(int min, int max){

	//srand(time(0)); note: put srand() in main outside of this function so it only calls srand() once
    int num = (rand() % (max - min + 1)) + min;
    return num;
    

}

int generate_probability(int min, int max){ //change to double later, maybe

	int num = (rand() % (max - min + 1)) + min;
    return num;
}




//Algorithm for running simulation. Later on, put this algorithm in separate file RunDES.c
int main(){


	//First take care of creating instances of linked list for each component, random number generator, and initialization before doing the while loop

	//create three linked lists for cpu, disk1, and disk2

	FILE * file;
	char singleLine[64];
	file = fopen("DESlog.txt", "w"); 

	//create column headers in log file (time|job|event)
	fputs("Time Job Event\n", file);

	//intitialize
	srand(time(0));
	jobcount = 1;
	Event* eventhead = newEvent(JOB_ARRIVES, 0, jobcount); //(event, time, job)
	pushevent(&eventhead, SIMULATION_FINISHED, FIN_TIME, 666);

	cpu* cpuhead = NULL;
  	disk1* disk1head = NULL;
  	disk2* disk2head = NULL;



	 //simulation loop
	while(!isEmptyevent(&eventhead) && (eventhead->event != SIMULATION_FINISHED)){


	if(peekevent(&eventhead) == JOB_ARRIVES){
	 //transfers job into cpu
	
	fprintf(file, "%d", eventhead->time);
    fputs(" ", file);
	fprintf(file, "%d", eventhead->job);
	fputs(" jobarrives\n", file); 

	//add job to cpu queue
	pushcpu(&cpuhead, eventhead->job);

	//pop event
	popevent(&eventhead);  //we can pop  at this point
    
    //generate new job
	timecount += generate_random_time(ARRIVE_MIN, ARRIVE_MAX);
	jobcount++;
	pushevent(&eventhead, JOB_ARRIVES, timecount, jobcount);

	if(sizecpu(cpuhead) == 1){ //if empty, process immediately. if size == 1, then that event is the only one in there
		
		timecount += generate_random_time(CPU_MIN, CPU_MAX);
		pushevent(&eventhead, CPU_FINISHED, timecount, cpuhead->job);
		cpuhead = removecpu(cpuhead);
		
	}else{
		timecount += generate_random_time(CPU_MIN, CPU_MAX);
	 	pushevent(&eventhead, CPU_FINISHED, timecount, peekcpu(cpuhead));
	 	cpuhead = removecpu(cpuhead);

	}
}

	/*generate new job
	timecount += generate_random_time(ARRIVE_MIN, ARRIVE_MAX);
	jobcount++;
	pushevent(&eventh, JOB_ARRIVES, timecount, jobcount);*/




	 //this includes random generation of cpu service time. Recall, once job finishes at cpu, if probability greater than .2, then it exits, if less then goes to disk
	if(peekevent(&eventhead) == CPU_FINISHED){
	fprintf(file, "%d", eventhead->time);
    fputs(" ", file);
	fprintf(file, "%d", eventhead->job);
	fputs(" jobfinishescpu\n", file);

	//probability that it exits system or gets sent to disk
	int probability = generate_probability(1,10);
	if(probability <= 3){ //job exits system and since its already removed from cpu, there's nothing to do. Maybe print Jobexits event to log file, not event queue!
		popevent(&eventhead);

	}else if (sizedisk1(disk1head) < sizedisk2(disk2head)){ //send to disk1
		pushdisk1(&disk1head, eventhead->job);
		popevent(&eventhead);
		if(sizedisk1(disk1head) == 1){
			timecount += generate_random_time(DISK1_MIN, DISK1_MAX);
		    pushevent(&eventhead, DISK1_FINISHED, timecount, disk1head->job);
			disk1head = removedisk1(disk1head);

		}else{
			timecount += generate_random_time(DISK1_MIN, DISK1_MAX);
	 	    pushevent(&eventhead, DISK1_FINISHED, timecount, peekdisk1(disk1head));
	 	    disk1head = removedisk1(disk1head);

		}

	}else if (sizedisk1(disk1head) > sizedisk2(disk2head)){ //send to disk2
		pushdisk2(&disk2head, eventhead->job);
		popevent(&eventhead);
		if(sizedisk2(disk2head) == 1){
			timecount += generate_random_time(DISK2_MIN, DISK2_MAX);
		    pushevent(&eventhead, DISK2_FINISHED, timecount, disk2head->job);
			disk2head = removedisk2(disk2head);

		}else{
			timecount += generate_random_time(DISK2_MIN, DISK2_MAX);
	 	    pushevent(&eventhead, DISK2_FINISHED, timecount, peekdisk2(disk2head));
	 	    disk2head = removedisk2(disk2head);

		}
	}else{
		int choice = generate_probability(1,10);
			if(choice <= 5){

				pushdisk1(&disk1head, eventhead->job);
				popevent(&eventhead);
				if(sizedisk1(disk1head) == 1){
					timecount += generate_random_time(DISK1_MIN, DISK1_MAX);
		    		pushevent(&eventhead, DISK1_FINISHED, timecount, disk1head->job);
					disk1head = removedisk1(disk1head);

				}else{
					timecount += generate_random_time(DISK1_MIN, DISK1_MAX);
	 	    		pushevent(&eventhead, DISK1_FINISHED, timecount, peekdisk1(disk1head));
	 	    		disk1head = removedisk1(disk1head);

				}
			}else if(choice > 5){

				pushdisk2(&disk2head, eventhead->job);
				popevent(&eventhead);
				if(sizedisk2(disk2head) == 1){
					timecount += generate_random_time(DISK2_MIN, DISK2_MAX);
		    		pushevent(&eventhead, DISK2_FINISHED, timecount, disk2head->job);
					disk2head = removedisk2(disk2head);

				}else{
					timecount += generate_random_time(DISK2_MIN, DISK2_MAX);
	 	    		pushevent(&eventhead, DISK2_FINISHED, timecount, peekdisk2(disk2head));
	 	    		disk2head = removedisk2(disk2head);

				}



			}

		

	}

}

	if(peekevent(&eventhead) == DISK1_FINISHED){ //once finished at disk, it gets transfered back to cpu
	fprintf(file, "%d", eventhead->time);
    fputs(" ", file);
	fprintf(file, "%d", eventhead->job);
	fputs(" jobfinishesdisk1\n", file);


	pushcpu(&cpuhead, eventhead->job);
	popevent(&eventhead);


}

	if(peekevent(&eventhead) == DISK2_FINISHED){ //once finished at disk, it gets transfered back to cpu
	fprintf(file, "%d", eventhead->time);
    fputs(" ", file);
	fprintf(file, "%d", eventhead->job);
	fputs(" jobfinishesdisk2\n", file);


	pushcpu(&cpuhead, eventhead->job);
	popevent(&eventhead);


}


		
		
		



			

			



	}

	fprintf(file, "%s", "Simulation Finished");
    

    




	return 0;
}








