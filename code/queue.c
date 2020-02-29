// Priority Queue ADO implementation ... COMP9024 19T3

//this program was submitted as a part of the assignment. I have taken the program modified to pop station number that highest departure time. 

#include "queue.h"

#include "assert.h"

#include <stdio.h>

typedef struct
{
  int item[MAX_NODES]; // array of vertices currently in queue
  int length;          // #values currently stored in item[] array
} PQueueT;

static PQueueT PQueue; // defines the Priority Queue Object

// set up empty priority queue
void PQueueInit()
{
  PQueue.length = 0;
}

// insert vertex v into priority queue
// no effect if v is already in the queue
void joinPQueue(int v)
{
  assert(PQueue.length < MAX_NODES); // ensure queue ADO is not full
  int i = 0;
  while (i < PQueue.length && PQueue.item[i] != v) // check if v already in queue
    i++;
  if (i == PQueue.length)
  { // v not found => add it at the end
    PQueue.item[PQueue.length] = v;
    PQueue.length++;
  }
}

// remove the highest priority vertex from PQueue
// remember: highest priority = lowest value priority[v]
// returns the removed vertex
int leavePQueue(int priority[])
{
  assert(PQueue.length > 0); // ensure queue has atleast one element.

  int i = 0;
  int v = 0;
  int min = priority[PQueue.item[0]]; //assigning priority of the first element of the queue as highest priority
  int pos = 0;
  if (PQueue.length > 1)
  { //if the size of the queue is more than 1, we have to verify it else 0th element has highest priority.
    for (i = 0; i < PQueue.length; i++)
    {
      if ((priority[PQueue.item[i]]) > min)
      {
        min = priority[PQueue.item[i]];
        pos = i;
      }
    }
  }
  v = PQueue.item[pos]; //assigning the element to be returned.
  if (pos == (PQueue.length - 1))
  { //if the element is in top position then simply reduce the size of the queue.
    PQueue.length--;
  }
  else
  { //else copy the top element and reduce the size of the queue
    PQueue.item[pos] = PQueue.item[(PQueue.length - 1)];
    PQueue.length--;
  }
  return v; // in any case return the v.
}

// check if priority queue PQueue is empty
bool PQueueIsEmpty()
{
  //if the lenghth of the queue is 0 which implies it is empty.

  if (PQueue.length == 0)
    return true;
  else
    return false;
}
