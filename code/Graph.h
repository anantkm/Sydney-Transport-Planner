// Graph ADT interface ... COMP9024 19T3
#include <stdbool.h>

#define SRTSTN 999999
#define STPSTN 999998
#define VERY_HIGH_VALUE 999997

typedef struct GraphRep *Graph;

Graph newGraph(int);
void inserttoStation(Graph, int, int, int, int, int, int, int, int, int);
int numOfStations(Graph);
int timeofgvngblsch(Graph, int, int);
int nextgblscfrmgvnsc(Graph, int, int);
int distofgvngblsch(Graph, int, int);
int distofgvnlclsch(Graph, int, int);
int nextstnoflcln(Graph, int, int);
int timeofgvnlclsch(Graph, int, int);
int globalschfromlcl(Graph, int, int);
int latestdepschedule(Graph, int, int, int, int);
int fromstnoflcl(Graph, int, int);
bool canIArrive(Graph, int, int);
int numberoflines(Graph, int);
int nextstnofgbl(Graph, int, int);
void freeGraph(Graph);
