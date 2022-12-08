## Leading Question 
For our final project, we want to explore the OpenFlights dataset to gain insight into how air travel can optimally interconnect people from around the world.  (https://openflights.org/data.html). Using the algorithms described below, a real life application would be generating a route visiting 5 major U.S. tourist destinations. We would use the nearest airport to each corresponding location and construct a route based on the shortest path. 

## Data Format
We will utilize data from (https://openflights.org/data.html), specifically airports.dat and routes.dat. The routes.dat dataset as a txt file is 2.4 MB, while the airport.dat dataset as a txt file is 1.1 MB. We plan to use a subset of this data, filtering only United States airports and evidently routes in the United States. The airports.dat file consists of each airport entry on its own separate line, consisting of 14 rows each containing potentially important information about the airport. From this file, we will use the 2nd and 5th rows (airport name and IATA code) to identify data to an airport. We will use the IATA code in our calculation as the code is the same in the routes.dat file, and convert to the airport name when outputting the solution, since most users will not know IATA codes. Also, we will use the 7th and 8th rows (latitude and longitude) to calculate the distance between airports. Finally, from the routes.dat data, which consists of the same dataset format as airports.dat, with each line being a route between two different airports. We will use rows 3 and 5 (source IATA and destination IATA) to identify the airports that are linked as well as row 8 (number of stops) to make sure we only include direct routes (stops = 0), as we will calculate stops ourselves. With this information, we will create an undirected and weighted graph consisting of airports as the vertices (|V|) and airplane routes between them as weighted edges (|E|) with the distance as the weight. We will also use row 4 of the airports.dat file (country) to filter only U.S airports.

## Data Correction
We will use a combination of excel and python to clean our data. The numpy library in python will allow us to get rid of any empty/null values so that the input data is error free. We will also make sure the values are in a certain plausible range to ensure incorrect data will not affect our algorithm. We will then parse through the data in excel and get rid of any values that are not in the United States as our project is only marking destinations in the US. 

## Data Storage
We will start by downloading data from openflights.org, and filter the data through excel, and convert to .csv files. The airports and routes we will use for our project will be stored in the form of a graph so we are able to use nodes and edges in order to calculate optimal distances. The optimal space complexity for this would be O(|V|+|E|) where |V| is the number of nodes (airports) and |E| is the possible edges (routes). Worst case, if every node is connected to the other, the space complexity would be O(|V|2).




## Algorithm 
 
Graph Algorithms
DFS Traversal 
Description: DFS (Depth-first search) is an algorithm for searching a graph data structure. Given a directed graph, the DFS algorithm will find all possible destinations from a given start node.
Function efficiency: The time complexity of the DFS traversal in graphs is O(|V| + |E|), where |V| represents the number of vertices (airports) and |E| represents the number of edges (routes). 
Function input: The input to the traversal algorithm will be the graph and the target node/target airport.
Function output: The output to the traversal algorithm will be the collection of nodes that connect to the target node/target airport. 
 
 
Shortest Path Algorithms
Dijsktra’s algorithm
Description: Djisktra’s algorithm allows us to find the shortest path from a single source node to another node. We will use the longitude and latitude of the airports to calculate the distance between the airports. This distance will then serve as the weight of the edges. Using Dijkstra’s algorithm, we will find the shortest distance between two airports (nodes). 
Function efficiency: Dijkstra's algorithm has worst case complexity of O((|V| + |E|) log |V|), where |V| represents the number of vertices (airports) and |E| represents the number of edges (routes)
Function input: Dijkstra's algorithm takes in a starting node, in our case we will pass in an ID which we use to uniquely identify each node (IATA). There will also be an end node input.
Function output: Dijkstra's algorithm outputs a vector of size |V|. Vector distance will contain the shortest distance from the input node to every node in the graph. The main point of using Dijkstra’s algorithm is to output a shortest path given a starting node. 

Kosaraju’s Algorithm
Description: Kosaraju’s algorithm is used to find strongly connected components on our graph or airplane routes. A strongly connected component (SCC) means that each vertice (airport) in this SCC can reach other vertices in the SCC. In our application of Kosaraju’s algorithm, if two vertices (airports) are in the same SCC, it means that they can reach each other. This algorithm has a lot of similarities to the DFS algorithm.  
Function efficiency: Kosaraju’s runtime is the same as DFS which is O(|V|+ |E|), where |V| represents the number of vertices (airports) and |E| represents the number of edges (routes). 
Function input: The input to the traversal algorithm will be the target node/target airport.
Function output: Kosaraju will output a vector of the strongly connected components on the graph from DFS traversal. 
 

## Tentative Timeline
11/3 - 11/9: Set up the skeleton for DFS, clean and filter datasets and convert into graphs
11/10 - 11/16: Set up skeleton for Dijsktra’s and write Dijsktra’s algorithm, & if time allows - testing for algorithms thus far
11/17 - 11/23: Set up skeleton for Kosaraju’s and write Kosaraju’s algorithm 
11/24 - 11/30: Finish any remaining algorithms and testing, build final project (tentative due to thanksgiving break, we will try to work on this as much as possible)
12/1 - 12/7: Finish any goals remaining from thanksgiving break week. Complete final presentation and project. 



