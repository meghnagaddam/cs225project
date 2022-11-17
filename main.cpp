#include <iostream>
#include <map>
#include <list>

class Graph{
    public:
        std::map<int,bool> visited;
        std::map<int,std::list<int> > adj;
        void addEdge(int v, int w); // function to add an edge to graph
        void DFS(int v);
}; 

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}
 

void Graph::DFS(int v)
{
    visited[v] = true;
    std::cout << v << " ";
    std::list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFS(*i);
}

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