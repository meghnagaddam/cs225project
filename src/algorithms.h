#pragma once
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <queue>
#include <stack>
#include <tuple>

#include "graph.h"
using namespace std;

class Map {
    public:
        Map(const string &airportFile, const string &routeFile);
        vector<string> BFS(int start);
        vector<string> BFS(int start, int destination);
        tuple<vector<string>,double> dijkstra(int start, int destination);
        int toIATA(string location);
        string convertToName(string code);
        void insertAirports();
        void insertFlights();
        vector<string> parse(const string &line);
    
    private:
        string route_file;
        string airport_file;
        Graph flights_;
        
};
