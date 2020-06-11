//This file will include all functions and data structure implementations that are in the header file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eventqueue.h"
#include "cpu.h"
#include "disk1.h"
#include "disk2.h"

#define LINE_LENGTH 20
#define NUM_PARAMS 12

//Parameters from config file
int INIT_TIME = 0;
int FIN_TIME = 0;
int ARRIVE_MIN = 0;
int ARRIVE_MAX = 0;
int QUIT_PROB = 0; 
int CPU_MIN = 0;
int CPU_MAX = 0;
int DISK1_MIN = 0;
int DISK1_MAX = 0;
int DISK2_MIN = 0;
int DISK2_MAX = 0;

//define events 
#define JOB_ARRIVES 1
#define CPU_FINISHED 2
#define DISK1_FINISHED 3
#define DISK2_FINISHED 4
#define SIMULATION_FINISHED 5

//global variables 
int jobcount = 0;
int timecount = 0; 

int maxsizecpu = 0;
int maxsizedisk1 = 0;
int maxsizedisk2 = 0;


//Random number generator
int generateRandom(int lower, int upper)
{
    
    
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
    
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







int main(){


	

	

	FILE * file;
	char singleLine[64];
	file = fopen("DESlog.txt", "w"); 

	//create column headers in log file (time|job|event)
	fputs("Time Job Event\n", file);


	//Read from config file
	float SEED;
  	unsigned int conf_vals[NUM_PARAMS] = {};
  	const char *conf_types[NUM_PARAMS] = {"INIT_TIME", "FIN_TIME", "ARRIVE_MIN", "ARRIVE_MAX", "QUIT_PROB", "CPU_MIN", "CPU_MAX", "DISK1_MIN", "DISK1_MAX", "DISK2_MIN", "DISK2_MAX", "SEED"};
  
  	int i;
  	for (i=0;i<NUM_PARAMS;i++)
   	{
      printf( "%d : ", conf_vals[i] );
      puts( conf_types[i] );
    }


  	printf( "%f : SEED\n\n", SEED );

  	FILE * fp;
  	fp = fopen( "DESconfig.txt", "r" );///home/alex/CodeForC/
  
  	char search_str[LINE_LENGTH];
  	char line[LINE_LENGTH];
  
  	while ( fgets( line, LINE_LENGTH, fp ) != NULL )
    {
      
      sscanf( line, "SEED %f\n", &SEED );
      for (i=0;i<NUM_PARAMS;i++)
		{
	  	strcpy( search_str, conf_types[i] );
	  	strcat( search_str, " %d\n" );
	  	sscanf( line, search_str, &conf_vals[i] );
		}
    }
    INIT_TIME = conf_vals[0];
    FIN_TIME = conf_vals[1];
    ARRIVE_MIN = conf_vals[2];
    ARRIVE_MAX = conf_vals[3];
    QUIT_PROB = conf_vals[4];
    CPU_MIN = conf_vals[5];
    CPU_MAX = conf_vals[6];
    DISK1_MIN = conf_vals[7];
    DISK1_MAX = conf_vals[8];
    DISK2_MIN = conf_vals[9];
    DISK2_MAX = conf_vals[10];
    SEED = conf_vals[11];


  	fclose(fp);

  	for (i=0;i<NUM_PARAMS;i++)
    {
      printf( "%d : ", conf_vals[i] );
      puts( conf_types[i] );
    }
  	printf( "%f : SEED\n", SEED );






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
				if(sizecpu(cpuhead) > maxsizecpu){
					maxsizecpu = sizecpu(cpuhead);
				}
				cpuhead = removecpu(cpuhead);
		
			}else{
				timecount += generate_random_time(CPU_MIN, CPU_MAX);
	 			pushevent(&eventhead, CPU_FINISHED, timecount, peekcpu(cpuhead));
	 			if(sizecpu(cpuhead) > maxsizecpu){
					maxsizecpu = sizecpu(cpuhead);
				}
	 			cpuhead = removecpu(cpuhead);

			}
		}

	

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
		    		if(sizedisk1(disk1head) > maxsizedisk1){
						maxsizedisk1 = sizedisk1(disk1head);
					}
					disk1head = removedisk1(disk1head);

				}else{
					timecount += generate_random_time(DISK1_MIN, DISK1_MAX);
	 	    		pushevent(&eventhead, DISK1_FINISHED, timecount, peekdisk1(disk1head));
	 	    		if(sizedisk1(disk1head) > maxsizedisk1){
						maxsizedisk1 = sizedisk1(disk1head);
					}
	 	    		disk1head = removedisk1(disk1head);

				}

			}else if (sizedisk1(disk1head) > sizedisk2(disk2head)){ //send to disk2
				pushdisk2(&disk2head, eventhead->job);
				popevent(&eventhead);
				
				if(sizedisk2(disk2head) == 1){
					timecount += generate_random_time(DISK2_MIN, DISK2_MAX);
		    		pushevent(&eventhead, DISK2_FINISHED, timecount, disk2head->job);
		    		if(sizedisk2(disk2head) > maxsizedisk2){
							maxsizedisk2 = sizedisk2(disk2head);
					}
					disk2head = removedisk2(disk2head);

				}else{
					timecount += generate_random_time(DISK2_MIN, DISK2_MAX);
	 	    		pushevent(&eventhead, DISK2_FINISHED, timecount, peekdisk2(disk2head));
	 	    		if(sizedisk2(disk2head) > maxsizedisk2){
							maxsizedisk2 = sizedisk2(disk2head);
					}
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
		    			if(sizedisk1(disk1head) > maxsizedisk1){
							maxsizedisk1 = sizedisk1(disk1head);
						}
						disk1head = removedisk1(disk1head);

					}else{
						timecount += generate_random_time(DISK1_MIN, DISK1_MAX);
	 	    			pushevent(&eventhead, DISK1_FINISHED, timecount, peekdisk1(disk1head));
	 	    			if(sizedisk1(disk1head) > maxsizedisk1){
							maxsizedisk1 = sizedisk1(disk1head);
						}
	 	    			disk1head = removedisk1(disk1head);

					}
				}else if(choice > 5){

					pushdisk2(&disk2head, eventhead->job);
					popevent(&eventhead);
					
					if(sizedisk2(disk2head) == 1){
						timecount += generate_random_time(DISK2_MIN, DISK2_MAX);
		    			pushevent(&eventhead, DISK2_FINISHED, timecount, disk2head->job);
		    			if(sizedisk2(disk2head) > maxsizedisk2){
							maxsizedisk2 = sizedisk2(disk2head);
						}
						disk2head = removedisk2(disk2head);

					}else{
						timecount += generate_random_time(DISK2_MIN, DISK2_MAX);
	 	    			pushevent(&eventhead, DISK2_FINISHED, timecount, peekdisk2(disk2head));
	 	    			if(sizedisk2(disk2head) > maxsizedisk2){
							maxsizedisk2 = sizedisk2(disk2head);
						}
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


	fprintf(file, "%s", "Simulation Finished\n");
	fputs("\n", file);
	fputs("Statistics:\n", file);
	fprintf(file, "Maximum Size of CPU: %d\n", maxsizecpu);
	fprintf(file, "Maximum Size of Disk1: %d\n", maxsizedisk1);
	fprintf(file, "Maximum Size of Disk2: %d\n", maxsizedisk2);
    

    




	return 0;
}








