#include<stdio.h>
#include<stdbool.h>
  
// No. of vertices in graph 
#define V 5 
  
void printSolution(int path[]); 
  
/* it checks if the vertex v can be added at 
   index 'pos' in the Hamiltonian Cycle constructed so far */
bool isSafe(int v, bool graph[V][V], int path[], int pos) 
{ 
    /* it checks if this vertex is an adjacent vertex of the previously 
       added vertex. */
    if (graph [ path[pos-1] ][ v ] == 0) 
        return false; 
  
    // it checks if the vertex has already been included. 
    for (int i = 0; i < pos; i++) 
        if (path[i] == v) 
            return false; 
  
    return true; 
} 
  
/* A recursive function to solve hamiltonian cycle problem */
bool hamCycleUtil(bool graph[V][V], int path[], int pos) 
{ 
    /* base case: If all vertices are included in Hamiltonian Cycle */
    if (pos == V) 
    { 
        // And if there is an edge from the last included vertex to the 
        // first vertex 
        if ( graph[ path[pos-1] ][ path[0] ] == 1 ) 
           return true; 
        else
          return false; 
    } 
  
    // Try different vertices as a next candidate in Hamiltonian Cycle. 
    // We are not trying with 0 as we are assuming it to be the starting point in hamCycle() 
    for (int v = 1; v < V; v++) 
    { 
        /* it will check if this vertex can be added to Hamiltonian Cycle */
        if (isSafe(v, graph, path, pos)) 
        { 
            path[pos] = v; 
  
            /* recursion to construct rest of the path */
            if (hamCycleUtil (graph, path, pos+1) == true) 
                return true; 
  
            /* If vertex v doesn't lead to a solution, 
               then we have to remove it */
            path[pos] = -1; 
        } 
    } 
  
    /* If no vertex can be added to Hamiltonian Cycle constructed so far, 
       then return false */
    return false; 
} 
  
/*We will solve the Hamiltonian Cycle problem here with the help of Backtracking.
Here, we will use hamCycleUtil() to solved our problem. we will get false as output if there is no Hamiltonian Cycle
possible, otherwise we will get True as output and then we will print the path. */

bool hamCycle(bool graph[V][V]) 
{ 
    int *path = malloc(V*sizeof(*path)); 
    for (int i = 0; i < V; i++) 
        path[i] = -1; 
  
    /* Let us put vertex 0 as the first vertex in the path. If there is 
       a Hamiltonian Cycle, then the path can be started from any point 
       of the cycle as the graph is not directed */
    path[0] = 0; 
    if ( hamCycleUtil(graph, path, 1) == false ) 
    { 
        printf("\nSolution does not exist"); 
        return false; 
    } 
  
    printSolution(path); 
    return true; 
} 
  
/* A utility function to print solution */
void printSolution(int path[]) 
{ 
    printf ("Solution Exists:"
            " Following is one Hamiltonian Cycle \n"); 
    for (int i = 0; i < V; i++) 
        printf(" %d ", path[i]); 
  
    // Let us now print the first vertex again to show the complete cycle 
    printf(" %d ", path[0]); 
    printf("\n"); 
} 
  
// main program to test above functions
int main() 
{ 
   /* Let us create the following graph 
      (0)--(1)--(2) 
       |   / \   | 
       |  /   \  | 
       | /     \ | 
      (3)-------(4)    */
   bool graph1[V][V] = {{0, 1, 0, 1, 0}, 
                      {1, 0, 1, 1, 1}, 
                      {0, 1, 0, 0, 1}, 
                      {1, 1, 0, 0, 1}, 
                      {0, 1, 1, 1, 0}, 
                     }; 
  
    // Print the solution 
    hamCycle(graph1); 
  
   /* Let us create the following graph 
      (0)--(1)--(2) 
       |   / \   | 
       |  /   \  | 
       | /     \ | 
      (3)       (4)    */
    bool graph2[V][V] = {{0, 1, 0, 1, 0}, 
                      {1, 0, 1, 1, 1}, 
                      {0, 1, 0, 0, 1}, 
                      {1, 1, 0, 0, 0}, 
                      {0, 1, 1, 0, 0}, 
                     }; 
  
    // Print the solution 
    hamCycle(graph2); 
  
    return 0; 
} 
