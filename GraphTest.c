/*A program to test the functionality of the Graph ADT */
  
#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"

int main(int argc, char* argv[]){
    if( argc != 2 ){
        printf("Usage: %s output\n", argv[0]);
        exit(1);
    }

    FILE *out;
    out = fopen(argv[1], "w");

    GraphRef G = newGraph(10);
    ListRef path = newList();
    int i;
    for( i = 1; i<= 9; i++){
        addEdge(G, i, i+1);
    }
    printGraph(out, G);

    BFS(G, 1); 

    fprintf(out, "Source of G is %d\n", getSource(G));

    fprintf(out, "Order of G is %d\n", getOrder(G));
    fprintf(out, "BFS called on Graph G with 1 as the source\n");

    getPath(path, G,  10);
    fprintf(out, "The path from 1 to 10 is:");
    printList(out, path);

    fprintf(out, "Parent of 10: %d\n", getParent(G, 10));
    fprintf(out, "Parent of 2: %d\n", getParent(G, 2));

    int dist = getDist(G, 1);
    fprintf(out, "Distance from 1 to 1 is %d\n", dist);
    fprintf(out, "Distance from 1 to 7 is %d\n", getDist(G, 7));

    freeList(&path);
    fclose(out);
    return(0);
}
