/**********************************************************************************
*  Fernando Carrillo (fcarril1)
*  Assignment: pa4
*  Graph.c
*  Implementation file for Graph ADT
***********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include "Graph.h"

/********************** Private Structs: not exported ***************************/

typedef struct Graph{
   ListRef * adjacency;
   char * color;
   int * discover;
   int * finish;
   int * parent;
   int order;
   int size;
   int source;
}Graph;

/************************ Constructors-Destructors ******************************/
GraphRef newGraph(int n){
    int i;
    GraphRef G = malloc(sizeof(Graph));
    G->adjacency = calloc(n+1, sizeof(ListRef));
    G->color = calloc(n+1, sizeof(char));
    G->discover = calloc(n+1, sizeof(int));
    G->finish = calloc(n+1, sizeof(int));
    G->parent = calloc(n+1, sizeof(int));
    for ( i = 1; i<= n ; i++){
        G->adjacency[i] = newList();
        G->color[i] = 'w';
        G->discover[i] = INF;
        G->finish[i] = INF;
        G->parent[i] = NIL;
    }
    G->order = n;
    G->size = 0;
    G->source = NIL;
    return G;
}

void freeGraph(GraphRef* pG){
    if (pG==NULL || *pG==NULL) return;
    int i, n = getOrder(*pG);
    for (i = 1;i <= n; i++){
       freeList(&(*pG)->adjacency[i]);
    }
    free((*pG)->adjacency);
    free((*pG)->color);
    free((*pG)->discover);
    free((*pG)->finish);
    free((*pG)->parent);
    free(*pG);
    *pG = NULL;
}

/*************************** Access functions ***********************************/ 
int getOrder(GraphRef G){
    return G->order;
}
int getSize(GraphRef G){
    return G->size;
} 

int getSource(GraphRef G){
    return G->source;
}

int getParent(GraphRef G, int u){
    if (u < 1 || u > getOrder(G)){
        printf("Called getParent on out of bound u\n");
        exit(1);
    }
    else return G->parent[u];
}

int getDist(GraphRef G, int u){
     if (u < 1 || u > getOrder(G)){
         printf("Called getDiscover on out of bound u\n");
         exit(1);
     }
     else return G->discover[u];
}

int getFinish(GraphRef G, int u){
     if (u < 1 || u > getOrder(G)){
         printf("Called getFinish on out of bound u\n");
         exit(1);
     }
     else return G->finish[u];
}

/*
*  getPathc
*  Appends to the List L the vertices of the shortest path in G from source
*  to u, or appends L the value NIL if no such path exists.
*/
void getPath(ListRef L, GraphRef G, int u) {
   if (getSource(G) == NIL) {
      printf("Graph Error: calling getPath() before BFS is called");
      exit(1);
   }
   else {
      if (G->source == u) {
         insertBack (L, u);
      }
      else if (G->parent[u] == NIL) {
      }
      else {
         getPath(L, G, G->parent[u]);
         insertBack(L, u);
      }
   }
}

/************************** Manipulation procedures *******************************/ 
void makeNull(GraphRef G){
    int i;
    for(i = 1; i<=getOrder(G); i++){
       makeEmpty(G->adjacency[i]);
       G->color[i] = 'w';
       G->discover[i] = INF;
       G->parent[i] = NIL;
    }
    G->order = 0;
    G->size = 0;
    G->source = NIL;
}
 
void addEdge(GraphRef G, int u, int v){
    addArc(G, u, v);
    addArc(G, v, u);
    G->size++;
}

void addArc(GraphRef G, int u, int v){
    ListRef row = G->adjacency[u];

    /* Inserts vetex v into row u in the adjacency array */
    if (isEmpty(row)){
        insertFront(row, v);
        return;
    }
    else{
        moveTo(row, 0);
        while (!offEnd(row)){
            if (v == getCurrent(row)) return;
            if (v > getCurrent(row)){
                moveNext(row);
            }else{
                insertBeforeCurrent(row, v);
                return;
            }
        }
        insertBack(row, v);
    }

}

void BFS(GraphRef G, int s){
   int i, u, tmp;
   G->source = s;
   for ( i = 1;i <= getOrder(G); i++){
      G->color[i] = 'w';
      G->discover[i] = INF;
      G->parent[i] = NIL;
   }
   G->color[s] = 'g';
   G->discover[s] = 0;
   G->parent[s] = NIL;
   ListRef Q = newList();
   insertFront( Q, s );
   while( !isEmpty(Q) ){
      u = getFront(Q);
      deleteFront(Q);
      moveTo(G->adjacency[u], 0);
      while ( !offEnd(G->adjacency[u]) ){
         tmp = getCurrent(G->adjacency[u]);
         if ( G->color[tmp] == 'w'){
            G->color[tmp] = 'g';
            G->discover[tmp] = G->discover[u] + 1;
            G->parent[tmp] = u;
            insertBack( Q, tmp );
         }
         moveNext(G->adjacency[u]);
      }
      G->color[u] = 'b';
   }
   freeList(&Q);
}

/***************************** Other operations *******************************/ 
void printGraph(FILE* out, GraphRef G){
    int i;
    for(i = 1; i <= getOrder(G); i++){
        fprintf(out, "%d:", i);
        printList(out, G->adjacency[i]); 
    }
}
