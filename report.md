**Group 1234 Final Report**

youtube link: https://www.youtube.com/watch?v=gSEWj8AqCoY&feature=youtu.be 

**Leading Question:**

Given a user’s desired start and destination airports, how can we construct an optimal suggested route based on the shortest path between airports? 

**Motivation and Background on Data Formatting:**

For our initial goal of the final project, we wanted to use graph algorithms to find out the shortest path between two airports with the minimum number of transfers, and compare the runtime and effectiveness of our algorithms using various airport data. 
The specific goals we wanted to meet are as follows:
1. Use BFS traversal to find the least number of connecting flights given a starting and destination airport.
2. Use Dijkstra’s algorithm to find the shortest flights between two airports and its distance.
3. Use Kosaraju’s algorithm to find strongly connected components on our graph or airplane routes. 
**Due to time constraints, we were unable to successfully implement Kosaraju’s algorithm in our final program.** 

By implementing Breadth-First Search and Dijkstra's algorithms, we were ultimately able to traverse the graph and provide a successful output to the user. We completed two traversals, each with its respective output, where the user is able to input a source and destination airport. After running the executable, the user is able to see an output of the traversal in the terminal.

In regards to the implemented dataset, we decided to use data from openflights.org, and our project mainly focuses on two subsets of the data – the airport and route subsets. Routes.txt was cleaned to only include data on the source and destination airports of each route in the United States, while airports.txt included specific details on each airport in the U.S. such as its main cities served, latitude and longitude. Since the airport IATA code is the common feature between the two datasets, we use it to match and locate information for each airport in each file. It was very important to ensure that all the airports in routes.txt had a corresponding entry in airports.txt in order to retrieve its latitude and longitude coordinates. We removed any airports that did not satisfy this requirement. This included null values present in the data for some airport ID’s, so we removed those respective airports as they were unusable. We also utilized a “parse” function, which takes a single CSV line and separates the values in a vector, while cleaning out any quotation marks from the output vector. For example, our input “ ‘item1’, ‘item2’, …” would output vector([0]: item1, [1]: item2, [2]: ...) and so on. 

**Background on Calculating Distance:**

Since the OpenFlights datasets do not offer data regarding the distance of the flight routes, we used the Haversine formula to calculate the distance with the provided set of latitude and longitude coordinates. 


The Haversine formula can tell us the great circle distance between two points on a sphere (earth), given their longitude and latitude. In the formula, phi1 and phi2 represent the latitude of airport 1 and airport 2, respectively. Lambda 1 and 2 represent the longitude of airport 1 and 2, respectively. 


**BFS:**

The first major algorithm we implemented was the The Breadth First Search (BFS) algorithm, which we used to find the least number of connecting flights given a starting and destination airport. It contains two main objectives: it can travel through the vertices(airports) of the graph, or the airports between two specific airports, and returns a vector of strings that stores the airportID of the vertices (airports) it travels and respective path, which will later convert it to the name of the airports. BFS uses a queue to traverse the entire graph, and initially marks all airports as not visited, initializing BFS by enqueuing or adding our source node. After, we enter a loop which processes the added node in the case that the queue is not empty. Then we add the nodes adjacent neighbors to the back of the queue, continuing along the loop. If the current node equals the destination node, then our destination is reached, in which we stop. However, if the current node does not equal the destination node, that means that no path could be found between start and destination airports using BFS. In the end, we returned the airport IDs and path. 


**Dijkstra’s Algorithm:**

Dijkstra's algorithm is used in our project to output the shortest path between two airports of interest, using the distance between two airports as edge weights. Using the initial values inputted by the user, Dijkstra’s algorithm successfully outputs the shortest distance traveled. In our implementation of this algorithm, we used a visited set, a tentative distance value for each node, and a priority queue. Specifically for our project, the parameters are the start and destination, two ints representing the nodes for which we are trying to find the shortest path in between. Right in the beginning, we check the edge cases, then we use three vectors (distanceFromStart, previous, and unvisited) to keep track of our relative sets’ tentative distance value for each node. Before anything else, we set all distances to infinity, since we don’t know any distance yet. At this stage, our relative vector is empty. Then we will start to deal with each specific node such as adding them to the priority queue. Afterwards, we traceback the path from destination node to start node and convert airport ID’s to its respective airport codes. 
The key condition is that the currently checked paths are smaller than the stored paths in terms of the number of connections. In other cases, the current stored paths remain unchanged. The whole algorithm should ensure that each airport can only be the base airport once.

**Kosaraju’s Algorithm:**

Although we did not successfully implement Kosaraju’s algorithm, we wanted to briefly describe our motivation behind its usage. We wanted to use Kosaraju’s algorithm to find strongly connected components on our graph or airplane routes. A strongly connected component (SCC) means that each vertice (airport) in this SCC can reach other vertices in the SCC. Our implementation attempted to find the most connected components of the entire graph data structure. 

**Test Cases:**
	We decided to implement our testing in our main.cpp file. You will see there is code commented out starting at line 132 in main.cpp. That code is specific to running test0.txt,test1.txt,test2.txt, which are cases that we came up with to ensure our algorithms were working correctly, and that our input was being taken in as well. Test0.txt makes sure inputs are recognized even if they are not all capitalized, and also ensures output for Dijkstra's is no possible flights connecting ORD to PIE.  In Test1.txt there should be a direct flight from ORD to LAX, which will also be the shortest path from ord to lax since there exists a direct route from ORD to LAX according to openflights data.  Since there are no direct flights from ORD to MDW, in Test2.txt Dijsktra’s will output MSP since Minneapolis is the next closest airport. The tests are also run with airports_small.dat and routes_small.csv. These smaller datasets allowed us to go through and predict our output before testing, to ensure functionality, since there are so many routes in our original dataset. 

**Answer to Leading Question:**

After the code runs successfully, it outputs the path with the least number of connecting flights, the path with the shortest distance traveled, and its respective total flight distance. We input different sets of start and destination airports which all generated successful results, given a smaller dataset. These also serve as our test cases. Our project was able to process the data from the openflights datasets and find the most efficient path between the inputted airports. 
	One thing that we learned in the project was how important running times can be. For example, in a project like this with such a huge dataset, we had to parse through all the data that you have to use for each algorithm, so having a good runtime and writing good code is really important for testing purposes. This is why we also decided to use a smaller dataset for the test cases. 
	If we had more time, we would have implemented more algorithms including kosaraju’s and calculated the time complexity to find the most effective one, enhancing the user experience where they can more efficiently change input and visualize the distance. 


