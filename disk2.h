/*#ifndef DISK2_H_
#define DISK2_H_*/

typedef struct disk2 {
	int job; 
	struct disk2 *next; 
} disk2;


void printdisk2(disk2*);
void pushdisk2(disk2**, int);
disk2* removedisk2(disk2*);
int peekdisk2(disk2*);
int sizedisk2(disk2*);

//#endif