/*************************************************************************
*  Author: Fernando Carrillo (fcarril1)
*  Assignment: pa4
*  Filename: Findpath.c
*  Class: CMPS 101 Patrick Tantalo
*
*  Description: The FindPath program reads in a formated infile that has
*  the amount of edges, edge connetions and paths to calculate. Using an
*  adjacency list FindPath uses Breadth First Search to calculate the 
*  the shortest path between two edges and prins the result to an outfile 
***********************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"
#include"List.h"

#define MAX_LEN 250

int main(int argc, char * argv[]){

   int n=0, hitZero = 0, source, dest;
   FILE *in, *out;
   char line[MAX_LEN];
   char tokenlist[MAX_LEN];
   char* token;
   GraphRef G;
   ListRef L = newList();

   /* check command line for correct number of arguments */
   if( argc != 3 ){
      printf("Usage: %s infile outfile\n", argv[0]);
      exit(1);
   }

   /* open files for reading and writing */
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   /* ListRef P = newList(); */
   
   /* Gets number of vertices in the file via the first line */
   fgets(line, MAX_LEN, in);
   token = strtok(line, " \n");
   n = atoi(&token[0]);

   G = newGraph(n);

   /* Iterates though and reads in ever vertice. */
   do{
      fgets(line, MAX_LEN, in);
      strcat(line, " ");
      token = strtok(line, " \n");
      tokenlist[0] = '\0';

      source = atoi(&token[0]);
      if (source >= 1000) dest = atoi(&token[5]);
      else if (source >= 100) dest = atoi(&token[4]);
      else if (source >= 10) dest = atoi(&token[3]);
      else dest = atoi(&token[2]); 
      hitZero = source + dest;

      if(hitZero != 0)addEdge(G, source, dest);
      token = strtok(NULL, " \n");

   }while(hitZero != 0);

   /* Prints out the Adjacency List for Graph G */
   printGraph(out, G);

   /* Prints Paths */
   do{
      fgets(line, MAX_LEN, in);
      strcat(line, " ");
      token = strtok(line, " \n");
      tokenlist[0] = '\0';

      source = atoi(&token[0]);
      if (source >= 1000) dest = atoi(&token[5]);
      else if (source >= 100) dest = atoi(&token[4]);
      else if (source >= 10) dest = atoi(&token[3]);
      else dest = atoi(&token[2]);
      hitZero = source + dest;

      if(hitZero != 0){
         BFS(G, source);
         getPath(L, G, dest);

         fprintf(out, "\nThe distance from %d and %d is ", source, dest);
         if (getFront(L) == NIL) fprintf( out, "Infinity\n");
         else fprintf(out, "%d\n", getDist(G, dest));
      
         if (getFront(L) == NIL) fprintf(out, "No %d-%d path exists\n", source, dest);
         else {
            fprintf(out, "A shortest %d-%d path is:", source, dest);
            printList(out, L);
         }
      
         makeEmpty(L);
         token = strtok(NULL, " \n");
       }      
   }while(hitZero != 0);
   
   /* free memory */
   makeEmpty(L);
   freeList(&L);
   freeGraph(&G);

   /* close files */
   fclose(in);
   fclose(out);

   return(0);
}
