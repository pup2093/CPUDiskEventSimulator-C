/*#ifndef DISK1_H_
#define DISK1_H_*/

typedef struct disk1 {
	int job;
	struct disk1 *next; 
} disk1;


void printdisk1(disk1*);
void pushdisk1(disk1**, int);
disk1* removedisk1(disk1*);
int peekdisk1(disk1*);
int sizedisk1(disk1*);

//#endif