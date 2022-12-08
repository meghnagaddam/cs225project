#include <iostream>
#include <map>
#include <list>
#include "graph.h"

 

int main(){
    Graph g;
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    std::cout << "Following is Depth First Traversal (starting from vertex 2) \n"<<std::endl;
 
    // Function call
    g.DFS(2);
    return 0;
}