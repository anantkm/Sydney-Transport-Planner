// Graph ADT
/*
there are 3 structs in this ADT and below is the represetation. 
_____________________
|   Graph Struct     |   
|   (GraphRep)       |   
|number_of_stations  |   
|pointer_Station_head|---|-----------------------------------|-----------------------------------|----------....
|____________________|   |                                   |                                   |
                         |                                   |                                   :  
                _________|____________              _________|____________                       :  
                |  Station Struct[0]  |             |                     |
                |     (stations)      |             |  Station Struct[1]  |
                |number_of_stops      |             |                     |   
                |pointer_to_Stops list|---|         |                     |---|  
                |_____________________|   |         |_____________________|   |
                                          |                                   |
                        __________________|____________________               |
                        |          Stop Struct (schOfStn)      |              :
                        |                                      |              :
                        |schOfStn refrs 2 "Schedule of Station"|
                        |stop_number_unique to station         |   
                        |stop_number_unique to graph           |
                        |time at which the train stops in stn. |
                        |line number inputted at the beginning |
                        |from_stop_global_number               |
                        |from_station_number                   |
                        |next_stop_global_number               |
                        |next_station_number                   |
                        |time(mins) required to reach nxt stp  |
                        |pointer to next stop in this station. ----------> Another STOP ....                  
                        |______________________________________|   




*/

#include "Graph.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

//Structure to store the schedule information (Schedule is referred as Each stop at perticular station)
typedef struct schOfStn
{
   int localsch; //local_number.
   int globalsch;
   int time;
   int lineno;
   int fromstnglsch;
   int fromstnno;    // arrival _ time_ to_station.
   int nextstnglsch; //next global index station index.
   int tonxtstno;
   int disttonxt;
   struct schOfStn *nextsch;
} schOfStn;

//Structure to store the Graph.
typedef struct GraphRep
{
   struct stations *stninfohead; //pointing to the stations.
   int nS;                       // #vertices which is referred as stations.
} GraphRep;

//Structure to store the station info.
typedef struct stations
{
   int stnindex; //station index .
   int nL;       // no. of lines this station is part of.
   struct schOfStn *schhead;
} StationRep;


//function to create a new graph
Graph newGraph(int nS)
{
   assert(nS >= 0);
   int i = 0;
   Graph g = malloc(sizeof(GraphRep));
   assert(g != NULL);
   g->nS = nS;
   //allocate momory for each station and initialize the number of lines to 0(Zero).
   g->stninfohead = malloc(nS * sizeof(StationRep));
   assert(g->stninfohead != NULL);
   for (i = 0; i < nS; i++)
   {
      g->stninfohead[i].stnindex = i;
      g->stninfohead[i].nL = 0;
      g->stninfohead[i].schhead = NULL;
   }
   return g;
}

//function that returns number of Stations in the Graph. 
int numOfStations(Graph g)
{
   return g->nS;
}

//this inserts schedule into perticular station.
schOfStn *newSchedule(int nL, int globalschno, int arrtime, int lineno, int frmstnglobal, int fromstation, int tostnglobal, int tostation, int distto)
{
   schOfStn *newsch = malloc(sizeof(schOfStn));
   assert(newsch != NULL);
   newsch->localsch = nL;
   newsch->globalsch = globalschno;
   newsch->time = arrtime;
   newsch->lineno = lineno;
   newsch->fromstnglsch = frmstnglobal;
   newsch->fromstnno = fromstation;
   newsch->nextstnglsch = tostnglobal;
   newsch->tonxtstno = tostation;
   newsch->disttonxt = distto;
   newsch->nextsch = NULL;
   return newsch;
}

//inserting the lineinfo into the station.
void inserttoStation(Graph g, int stationno, int globalschno, int arrtime, int lineno, int frmstnglobal, int fromstation, int tostnglobal, int tostation, int distto)
{

   schOfStn *currentsch = g->stninfohead[stationno].schhead;
   schOfStn *trvslnode = currentsch;
   int currentnoline = g->stninfohead[stationno].nL;
   schOfStn *newsch = newSchedule(currentnoline, globalschno, arrtime, lineno, frmstnglobal, fromstation, tostnglobal, tostation, distto);
   if (currentsch == NULL)
   {
      g->stninfohead[stationno].schhead = newsch;
      g->stninfohead[stationno].nL++;
   }
   else
   {
      while (trvslnode->nextsch != NULL)
         trvslnode = trvslnode->nextsch;
      trvslnode->nextsch = newsch;
      g->stninfohead[stationno].nL++;
   }
}

//fucntion to check if any train gets to station on or before specified time.
bool canIArrive(Graph g, int stationno, int spctime)
{
   int i = 0;
   int count = 0;
   schOfStn *temp = g->stninfohead[stationno].schhead;
   int noSTN = g->stninfohead[stationno].nL;

   for (i = 0; i < noSTN; i++)
   {
      if (temp->time <= spctime)
         count++;
      temp = temp->nextsch;
   }
   if (count > 0)
      return true;
   else
      return false;
}

//function that returns time of  global schedule at perticular stantion.
int timeofgvngblsch(Graph g, int stnno, int gblsch)
{
   int numoflines = g->stninfohead[stnno].nL;
   int time = 0;
   schOfStn *temp = g->stninfohead[stnno].schhead;
   for (int i = 0; i < numoflines; i++)
   {
      if (temp->globalsch == gblsch)
         time = temp->time;
      temp = temp->nextsch;
   }
   return time;
}

//fucntion to get the  next glocalschedule (gotoschedule) from a given global schedule.
int nextgblscfrmgvnsc(Graph g, int stnno, int gblsch)
{
   int numoflines = g->stninfohead[stnno].nL;
   int gotosch = 0;
   schOfStn *temp = g->stninfohead[stnno].schhead;
   for (int i = 0; i < numoflines; i++)
   {
      if (temp->globalsch == gblsch)
         gotosch = temp->nextstnglsch;
      temp = temp->nextsch;
   }
   return gotosch;
}

//function that returs the dist to next stn from global schedule.
int distofgvngblsch(Graph g, int stnno, int gblsch)
{
   int numoflines = g->stninfohead[stnno].nL;
   int dist = 0;
   schOfStn *temp = g->stninfohead[stnno].schhead;
   for (int i = 0; i < numoflines; i++)
   {
      if (temp->globalsch == gblsch)
         dist = temp->disttonxt;
      temp = temp->nextsch;
   }
   return dist;
}

//function that returns dist of perticular local schedule at a stn.
int distofgvnlclsch(Graph g, int stnno, int lclsch)
{
   int numoflines = g->stninfohead[stnno].nL;
   int dist = 0;
   schOfStn *temp = g->stninfohead[stnno].schhead;
   for (int i = 0; i < numoflines; i++)
   {
      if (temp->localsch == lclsch)
         dist = temp->disttonxt;
      temp = temp->nextsch;
   }
   return dist;
}

//function that returns nextstn number from local schedule of perticular stn.
int nextstnoflcln(Graph g, int stnno, int localln)
{
   int numoflines = g->stninfohead[stnno].nL;
   int nextstn = 0;
   schOfStn *temp = g->stninfohead[stnno].schhead;
   for (int i = 0; i < numoflines; i++)
   {
      if (temp->localsch == localln)
         nextstn = temp->tonxtstno;
      temp = temp->nextsch;
   }
   return nextstn;
}
//function that returns nextstn number from global schedule of perticular stn.
int nextstnofgbl(Graph g, int stnno, int gblsch)
{
   int numoflines = g->stninfohead[stnno].nL;
   int nextstn = 0;
   schOfStn *temp = g->stninfohead[stnno].schhead;
   for (int i = 0; i < numoflines; i++)
   {
      if (temp->globalsch == gblsch)
         nextstn = temp->tonxtstno;
      temp = temp->nextsch;
   }
   return nextstn;
}

//function that returns from stn from localschedule
int fromstnoflcl(Graph g, int stnno, int localln)
{
   //printf("myrecieved values are stnno=%d, localln=%d\n", stnno, localln);
   int numoflines = g->stninfohead[stnno].nL;
   int frmstn = -1;
   schOfStn *temp = g->stninfohead[stnno].schhead;
   for (int i = 0; i < numoflines; i++)
   {
      if (temp->localsch == localln)
         frmstn = temp->fromstnno;
      temp = temp->nextsch;
   }
   temp = NULL;
   //printf("Returning value is %d\n", frmstn);
   return frmstn;
}

//time of given local schedule at perticular stn.
int timeofgvnlclsch(Graph g, int stnno, int lclsch)
{
   int numoflines = g->stninfohead[stnno].nL;
   int time = 0;
   schOfStn *temp = g->stninfohead[stnno].schhead;
   for (int i = 0; i < numoflines; i++)
   {
      if (temp->localsch == lclsch)
         time = temp->time;
      temp = temp->nextsch;
   }
   return time;
}

//reutrns globla schedule number from local schedule of pertiular stn.
int globalschfromlcl(Graph g, int stnno, int lclsch)
{
   int numoflines = g->stninfohead[stnno].nL;
   int gblsch = -1;
   schOfStn *temp = g->stninfohead[stnno].schhead;
   for (int i = 0; i < numoflines; i++)
   {
      if (temp->localsch == lclsch)
         gblsch = temp->globalsch;
      temp = temp->nextsch;
   }
   return gblsch;
}

//returns the latestest global scheule to destn from perticular station.
int latestdepschedule(Graph g, int frmstn, int tostn, int gblsch, int arrivaltonextstn)
{
   int i = 0;
   int latdeps = gblsch;
   int numofline = (g->stninfohead[frmstn].nL);
   int givendeptime = timeofgvngblsch(g, frmstn, gblsch);
   int givendistance = distofgvngblsch(g, frmstn, gblsch);
   for (i = 0; i < numofline; i++)
   {
      int nextstation = nextstnoflcln(g, frmstn, i);
      if (nextstation != STPSTN && nextstation == tostn)
      {
         int currenttime = timeofgvnlclsch(g, frmstn, i);
         int currentgblsch = globalschfromlcl(g, frmstn, i);
         int gotogblsch = nextgblscfrmgvnsc(g, frmstn, currentgblsch);
         int arrivetime = timeofgvngblsch(g, nextstation, gotogblsch);

         if ((currenttime > givendeptime) && (currenttime <= arrivaltonextstn))
         {
            if (arrivetime <= arrivaltonextstn)
            {
               latdeps = currentgblsch;
            }
         }
      }
   }
   givendeptime = timeofgvngblsch(g, frmstn, latdeps);
   givendistance = distofgvngblsch(g, frmstn, latdeps);
   for (i = 0; i < numofline; i++)
   {
      int nextstation = nextstnoflcln(g, frmstn, i);
      if (nextstation != STPSTN && nextstation == tostn)
      {
         int currenttime = timeofgvnlclsch(g, frmstn, i);
         int currentdist = distofgvnlclsch(g, frmstn, i);

         if (currenttime == givendeptime)
         {
            if (currentdist < givendistance)
            {
               latdeps = globalschfromlcl(g, frmstn, i);
            }
         }
      }
   }

   return latdeps;
}

 //returns number of stops of each station.
int numberoflines(Graph g, int stationno)
{
   return (g->stninfohead[stationno].nL);
}

//function to free the graph.
void freeGraph(Graph g)
{
   assert(g != NULL);

   int i, j;

   for (i = 0; i < g->nS; i++)
   {
      int numlines = g->stninfohead[i].nL;
      schOfStn *temp = g->stninfohead[i].schhead;
      schOfStn *temp1 = NULL;
      for (j = 0; j < numlines; j++)
      {
         temp1 = temp->nextsch;
         free(temp);
         temp = temp1;
      }
   }
   free(g->stninfohead);
   free(g);
}
