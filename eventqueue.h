/*#ifndef EVENTQUEUE_H_
#define EVENTQUEUE_H_*/

typedef struct node{

	int event; //event is an int because we made them named constants. When we need to log the file, of course we will write a string of event name corresponding to event constant 
	int time; //priority, which is time of event 
	int job; //job #
	struct node *next; //pointer to next node
	
} Event; 

//function declarations

Event* newEvent(int, int, int);
int peekevent(Event**);
void popevent(Event**);
void pushevent(Event**, int, int, int);
int isEmptyevent(Event**);

//#endif
