#pragma once
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <cmath>
#include <cctype>
#include <algorithm>
#include "edge.h"

using namespace std;

//nodes to create graph for airports and flights
struct node {
    int id;
    string code;
    string city;
    string name;
    double latitude;
    double longitude;
    unordered_map<int, Edge> edges;
};

//class to create graph that connects airports and flights
class Graph {
    public:
        map<int, node> airports;
        unordered_map<int, string> idcode; //  converts airport ID to aiport IATA code
        unordered_map<string, int> codeid; //  converts airport IATA code to ID
        unordered_map<string, string> codeToName; // converts IATA code to airport name
        void insertEdge(vector<string> line);
        void insertNode(vector<string> line);
        double getDistance(int start, int dest);   
};
