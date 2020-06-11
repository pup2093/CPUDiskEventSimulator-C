#include <stdio.h>
#include <stdlib.h>
#include "eventqueue.h"

//event queue


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
 
    
    // insert new
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