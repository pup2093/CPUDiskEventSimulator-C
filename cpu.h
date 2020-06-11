/*#ifndef CPU_H_
#define CPU_H_*/

typedef struct cpu {
	int job;
	struct cpu *next; 
} cpu;


void printcpu(cpu*);
void pushcpu(cpu**, int);
cpu* removecpu(cpu*);
int peekcpu(cpu*);
int sizecpu(cpu*);

//#endif 