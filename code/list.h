// Linked list interface ... COMP9024 19T3
#include <stdbool.h>
#include "Graph.h"

typedef struct Node *List;

List insertLL(List, int, int, int);
void updateGraph(Graph, List, int);
void freeLL(List);
int calcmins ( int, int);
