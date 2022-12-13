#include "graph.h"
#include <cmath>
using namespace std;

void Graph::insertEdge(vector<string> line) {
    int dest = atoi(line[5].c_str());
    int source = atoi(line[3].c_str());
    double weight = getDistance(source, dest);
    Edge flight(source, dest, weight);
    //checks for existing edge
    if (airports[source].edges.find(dest) == airports[source].edges.end())    
        airports[source].edges.insert(pair<int, Edge>(dest, flight));
}

void Graph::insertNode(vector<string> line) {
    node airport;
    airport.id = atoi(line[0].c_str());
    airport.latitude = atof(line[6].c_str());
    airport.longitude = atof(line[7].c_str());
    string name = line[1];
    transform(name.begin(), name.end(), name.begin(), [](unsigned char c){return toupper(c); });
    airport.name = name;
    string code;
    code = line[4];
    transform(code.begin(), code.end(), code.begin(), [](unsigned char c){return toupper(c); });
    airport.code = code;
    airports.insert(pair<int, node>(airport.id, airport));
    idcode.insert(pair<int, string>(airport.id, airport.code));
    codeid.insert(pair<string, int>(airport.code, airport.id));
    codeToName.insert(pair<string, string>(airport.code, airport.name));
}

//  Haversine formula from (https://www.movable-type.co.uk/scripts/latlong.html)
double Graph::getDistance(int start, int dest) {
    double start_latitude = airports[start].latitude;
    double start_longitude = airports[start].longitude;
    double dest_latitude = airports[dest].latitude;
    double dest_longitude = airports[dest].longitude;
    //Earth's radius
    double radius = 6371000; 
    //Conversions to radians.
    double x = start_latitude * (M_PI/180);
    double y = dest_latitude * (M_PI/180);
    double z = (dest_latitude-start_latitude) * M_PI/180;
    double k = (dest_longitude-start_longitude) * M_PI/180;
    double a = ( sin(z/2)*sin(z/2) ) + cos(x) * cos(y) * ( sin(k/2)*sin(k/2) );
    double c = 2 * atan2(sqrt(a), sqrt((1-a)));
    double d = radius * c;
    //converts distance to miles from meters.
    return d/1609.344;  
}
