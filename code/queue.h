// Priority Queue ADO header ... COMP9024 19T3

#include "Graph.h"
#include <stdbool.h>

#define MAX_NODES 50000


void   PQueueInit();
void   joinPQueue(int);
int leavePQueue(int[]);
bool   PQueueIsEmpty();