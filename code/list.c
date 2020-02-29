// this was originally list ADT taken from the COMP9024 lecture. later this was modified to suite the program needs.
/*
__________________|____________________
|     Input Schedule Struct (Node)     |   
|                                      |   
|Unique_no_to_stop (starts from 100)   |   
|station number                        |
|time at which the train stops in stn. |
|line number                           |
|pointer to next stop in this Line ----------> Another Node                   
|______________________________________|   

*/

#include "list.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int globalnumber = 100; //this global number which is assigned to each schedule induvidually.

//function to calculate the time to travel to next station.
int calcmins(int t1, int t2)
{
  int min1 = t1 % 100;
  t1 = t1 / 100;
  t1 = t1 * 60;
  int totalmin1 = t1 + min1;

  int min2 = t2 % 100;
  t2 = t2 / 100;
  t2 = t2 * 60;
  int totalmin2 = t2 + min2;

  if (totalmin1 > totalmin2)
  {
    return (totalmin1 - totalmin2);
  }
  else
  {
    return (totalmin2 - totalmin1);
  }
}

//defining node of Linked list.
typedef struct Node
{
  int glnumber;      //global number which is unique to each stop.
  int stnindex;      // station number
  int timevar;       // variable holds the time at which train makes stop at perticular station.
  int lineno;        // line is the that user inputs.
  struct Node *next; // variable that points to next node.
} Node;

//function that creates a node and assigns values. 
Node *makeNode(int si, int t, int l)
{
  Node *new = malloc(sizeof(Node));
  assert(new != NULL); // checking if the node is created.
  new->glnumber = globalnumber;
  new->stnindex = si;
  new->timevar = t;
  new->lineno = l;
  new->next = NULL;
  globalnumber = globalnumber + 1; //incrementing the global number everytime schedule is created.
  return new;
}
//modified to insert the node at the end.
Node *insertLL(List L, int si, int t, int l)
{
  //printf("I'm in makenode si=%d and t=%d\n",si,t);
  List newlist = NULL; //variable of type List. declared for later usage.
  List traversenode = L;
  newlist = makeNode(si, t, l);
  if (L == NULL)
  {
    L = newlist;
  }
  else
  {
    while (traversenode->next != NULL)    // travering till the end of the list.
      traversenode = traversenode->next;   
    traversenode->next = newlist;
  }
  return L;
}

//this function updates graph from linked list 
void updateGraph(Graph g, List L, int nS)
{
  int minsnxt = 0;
  List tempnode = L;
  List prevnode = NULL;
  int i = 0;
  for (i = 0; i < nS; i++)
  {
    if (i == 0) //for the first schedule.
    {
      minsnxt = calcmins(tempnode->timevar, tempnode->next->timevar);
      inserttoStation(g, tempnode->stnindex, tempnode->glnumber, tempnode->timevar, tempnode->lineno, SRTSTN, SRTSTN, tempnode->next->glnumber, tempnode->next->stnindex, minsnxt);
    }
    else if (tempnode->next == NULL)  // for the last schedule. 
    {
      minsnxt = STPSTN;
      inserttoStation(g, tempnode->stnindex, tempnode->glnumber, tempnode->timevar, tempnode->lineno, prevnode->glnumber, prevnode->stnindex, STPSTN, STPSTN, minsnxt);
    }
    else    // for the rest of the schedules. 
    {
      minsnxt = calcmins(tempnode->timevar, tempnode->next->timevar);
      inserttoStation(g, tempnode->stnindex, tempnode->glnumber, tempnode->timevar, tempnode->lineno, prevnode->glnumber, prevnode->stnindex, tempnode->next->glnumber, tempnode->next->stnindex, minsnxt);
    }

    prevnode = tempnode; // holding the address of the previous node. This helps in finding from staion. 
    tempnode = tempnode->next;
  }
}

//function to free the list initially used to create the graph. Taken from the leture.
void freeLL(List L)
{
  if (L != NULL)
  {
    freeLL(L->next);
    free(L);
  }
}
