#include "algorithms.h"

using namespace std;

//constructing a map with airports and routes 
Map::Map(const string &routes, const string &airports) {
    route_file = routes;
    airport_file = airports;
    insertAirports();
    insertFlights();
} 

//adds airpors to the map
void Map::insertAirports() {
    ifstream infile(airport_file.c_str());
    string lines;
    //seperates each line into vectors, and puts airport onto map
    while(getline(infile, lines)) {
        vector<string> line = parse(lines);
        flights_.insertNode(line);
    }
    infile.close();
}

//adds flights connecting airports on map
void Map::insertFlights() {
    ifstream infile(route_file.c_str());
    string lines;

    //seperates each line into vectors, and connects airports on map (without distances calculated)
    while(getline(infile, lines)) {
        vector<string> line = parse(lines);
        flights_.insertEdge(line);
    }
    infile.close();
}

int Map::toIATA(string location) {
    if (location == "") {
        return -1;
    } 
    unordered_map<string, int>::iterator it;
    int id = -1;
    transform(location.begin(), location.end(), location.begin(), [](unsigned char c){return toupper(c); });
    it = flights_.codeid.find(location);
    if (it != flights_.codeid.end()) {
        id = it->second;
    }
    return id;
}

string Map::convertToName(string code) {
    if (code == "") {
        return "";
    }
    unordered_map<string, string>::iterator it;
    string name = "";
    transform(code.begin(), code.end(), code.begin(), [](unsigned char c){return toupper(c); });
    it = flights_.codeToName.find(code);
    if (it != flights_.codeToName.end()) {
        name = it->second;
    }
    return name;
}

//parses csv files to be used in algorithms
vector<string> Map::parse(const string &line) {
    char curr;
    bool quote = false;
    string out = "";
    vector<string> strout;

    for(size_t i = 0; i < line.size(); ++i) {
        curr = line[i];
        //vector pushed to based on commas in csv
        if(!quote) {
            if(curr == ',') {
                strout.push_back(out);
                out = string();
            }
            else if(curr == '"')
                quote = true;
            else
                out += curr;
        }
        else {
            if(curr == '"' && i + 1 < line.size()) {
                if(line[i+1] == '"') {
                    out += '"';
                    ++i;
                }
                else
                    quote = false;
            }
            else
                out += curr;
        }
    }
    return strout;
}

//BFS with only starting vertex input.
vector<string> Map::BFS(int start) {
    //Mark all airports as not visited, makes size high enough to avoid out of bounds error.
    vector<bool> visited(12000, false);
    //BFS queue.
    queue<int> airportQ;
    //Queue to track order of visited airports.
    queue<int> searchQ;
    //Converts visited order queue to IATA codes.
    vector<string> codes;
    airportQ.push(start);
    searchQ.push(start);
    //Tracks current airport we are visiting.
    int current = start;
    //BFS
    while (airportQ.empty() == false) {
        current = airportQ.front();
        //Loop through all flights out of current airport.
        for (auto it = flights_.airports[current].edges.begin(); it != flights_.airports[current].edges.end(); it++) {
            //Checks to see if next airport has not been visited yet.
            if (visited[it->first] == false) {  
                searchQ.push(it->first);
                airportQ.push(it->first);
                visited[it->first] = true;
            }
        }
        airportQ.pop();
    }
    while (searchQ.empty() == false) {
        codes.push_back(flights_.idcode[searchQ.front()]);
        searchQ.pop();
    }
    return codes;
}

//BFS with start vertex and ending vertex input.
vector<string> Map::BFS(int start, int end) {
    //Initialize vector with size large enough to avoid out of bounds, and mark every airport as not visited.
    vector<bool> visited(12000, false);
    //BFS queue.
    queue<int> airportQ;
    //Tracks order of visited airports.
    vector<int> previous(12000);
    //Insert starting airport into tracker.
    previous[start] = start;
    airportQ.push(start);
    //Tracks current airport being visited.
    int curr = start;
    //Conversion to IATA codes.
    vector<string> codes;
    //BFS
    while (airportQ.empty() == false) {
        curr = airportQ.front();
        //Loop through current airport's possible flights.
        for (auto it = flights_.airports[curr].edges.begin(); it != flights_.airports[curr].edges.end(); it++) {
            //Checks to see if next airport has not been visited.
            if (visited[it->first] == false) {
                //Make previous airport the current one being looked at.
                previous[it->first] = curr;
                //Add next airport to queue.
                airportQ.push(it->first);
                //Mark it as visited.
                visited[it->first] = true;
            }
        }
        //If destination is reached, BFS is done.
        if (curr == end) {
            break;
        }
        airportQ.pop();
    }
    //Return if no route could be found to destination.
    if (curr != end) {
        vector<string> v;
        return v;
    }
    //Backtrack to starting airport.
    stack<int> reversePath;
    while (curr != start) {
        reversePath.push(curr);
        curr = previous[curr];
    }
    reversePath.push(start);
    //convert airport IDs to Airport Code
    while (reversePath.empty() == false) {
        codes.push_back(flights_.idcode[reversePath.top()]);
        reversePath.pop();
    }
    return codes;
}

//Use Dijkstra to find shortest route from starting airport to final airport.
tuple<vector<string>,double> Map::dijkstra(int start, int end) {
    //Just in case there are no flights to either starting or ending airports.
    if (flights_.airports[start].edges.empty() || flights_.airports[end].edges.empty()) { 
        tuple<vector<string>,double> temp;
        return temp;
    }
    //Distances of flights.
    vector<double> distanceFromSourceAirport(12000, 0.0);
    //Tracks previous airports visited.
    vector<int> previous(12000);
    //Tracks unvisited airports.
    vector<int> unvisited;
    for (auto it = flights_.airports.begin(); it != flights_.airports.end(); it++) {
        //Sets all distances to unreasonably high number as a placeholder that won't mark it as an ideal path.
        distanceFromSourceAirport[it->first] = 1000000;
        unvisited.push_back(it->first);
    }
    distanceFromSourceAirport[start] = 0;
    previous[start] = start;
    //current airport being checked.
    int curr;
    while (unvisited.empty() == false) {
        double minDistance = 1000000;
        //Index of vertex with shortest distance from starting airport.
        int minIndex;
        //Loops to find vertex with shortest distance from starting airport.
        for (size_t i = 0; i < unvisited.size(); i++) {
            if (distanceFromSourceAirport[unvisited[i]] < minDistance) {
                minDistance = distanceFromSourceAirport[unvisited[i]];
                minIndex = i;
            }
        }
        curr = unvisited[minIndex];
        unvisited.erase(unvisited.begin()+minIndex);
        if (curr == end) 
            break;
        //looks through departures from current airport
        for (auto it=flights_.airports[curr].edges.begin(); it!=flights_.airports[curr].edges.end(); it++) {   
            //distanceFromSourceAirport through current to departure airport 
            double newDistance = distanceFromSourceAirport[curr] + (it->second).getWeight(); 
            //update distance if shorter flight
            if (newDistance < distanceFromSourceAirport[it->first]) {   
                distanceFromSourceAirport[it->first] = newDistance;
                previous[it->first] = curr;  
            }
        }
    }
    //in case no path is found
    if (curr != end) { 
        tuple<vector<string>,double> T;
        return T;
    }

    //trace back path from destination to start
    stack<int> reversePath;
    while (curr != start) {
        reversePath.push(curr);
        curr = previous[curr];
    }
    reversePath.push(start);
    //convert airport IDs to Airport Code
    vector<string> path;
    while (!reversePath.empty()) {
        // int ap = reversePath.top();
        path.push_back(flights_.idcode[reversePath.top()]);
        reversePath.pop();
    }
    //tuple of path and total distance to get shortest path
    tuple<vector<string>,double> shortestPath(path, distanceFromSourceAirport[end]);    
    return shortestPath;
}


