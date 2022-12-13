# CS225 Final Project

## Introduction

For our goal of the final project, we wanted to use graph algorithms to find out the shortest path between two airports with the minimum number of transfers, and compare the runtime and effectiveness of our algorithms using various airport data.<br>
The specific goals we wanted to meet are as follows:<br>
Use BFS traversal to find the least number of connecting flights given a starting and destination airport.<br>
Use Dijkstra’s algorithm to find the shortest flights between two airports and its distance.<br>

Link to our presentation: https://youtu.be/gSEWj8AqCoY<br>


## Technical Architecture
### Main files
`main.cpp` : combines all the algorithms and provides output for shortest path. Test cases provided here. <br>
`algorithms.cpp` : contains BFS and Djikstras algorithms. <br>
`graph.cpp` : creates a graph for BFS and Djikstras.<br> 
`edge.h` : edge class used to build graph. <br>

## Installation and running
- Clone the repository to a local folder.<br>
- Open in the CS225 Docker container.<br>
- Make the build directory.<br>
- Navigate into the `build` directory.<br>
- Run cmake .. <br>
- Move "input.txt", "output.txt", "airports.dat", and "routes_clean.csv" files in the "data" folder to the "build" folder.<br>
- In the "input.txt" file, enter your source IATA in the first two lines and the destination in the third line.<br>
- Run make<br>
- Results will show in terminal and output.txt!<br>

## Running Test Cases
- Comment out original code in main.<br>
- Uncomment desired test cases provided at the bottom of main. <br>
- Move related data files to the "build" folder. (instructions provided in comments of test cases)<br>
- Results shown in output.txt.<br>



