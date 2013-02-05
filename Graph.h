/**********************************************************************
*  Fernando Carrillo (fcarril1)
*  Assignment: pa4
*  Graph.h
*  Header file for Graph ADT
**********************************************************************/
#include "List.h"
#if !defined(_GRAPH_H_INCLUDE)
#define _GRAPH_H_INCLUDE_
#define INF -1
#define NIL 0

/*** Exported Types *********************/

typedef struct Graph * GraphRef;

/* Constructors-Destructors */ 
GraphRef newGraph(int n); 
void freeGraph(GraphRef* pG);
 
/* Access functions */ 
int getOrder(GraphRef G); 
int getSize(GraphRef G);
int getSource(GraphRef G);
int getParent(GraphRef G, int u); 
int getDist(GraphRef G, int u);
void getPath(ListRef L, GraphRef G, int u);

/* Manipulation procedures */ 
void makeNull (GraphRef G);
void addEdge (GraphRef G, int u, int v);
void addArc(GraphRef G, int u, int v);
void BFS(GraphRef G, int s);
 
/* Other Functions */  
void printGraph(FILE* out , GraphRef G); 
#endif

