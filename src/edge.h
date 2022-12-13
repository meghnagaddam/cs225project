#pragma once
#include <string>
#include <limits.h>

using namespace std;

//edge class to be used in graph.
class Edge {
    public:
        //Unweighted graph.
        Edge(int s, int d) {
            source = s;
            dest = d;
            weight = 1.0;
        }
        
        //Weighted graph.
        Edge(int s, int d, double w) {
            source = s;
            dest = d;
            weight = w;
        }
        
        //returns weight
        double getWeight() {
            return weight;
        }

        //return weight
        void setWeight(double w) {
            weight = w;
        }

        //Returns source
        int getSourceId() {
            return source;
        }

        //returns dest
        int getDestId() {
            return dest;
        }

        //compares weights
        bool operator<(const Edge& other) const {
            return weight < other.weight;
        }

        //compares 2 edges
        bool operator==(Edge& other) const {
            if (source != other.source || dest != other.dest) {
                return false;
            }
            return true;
        }
    
    private:
        // Starting edge vertex id.
        int source; 
        // Ending edge vertex id.
        int dest;
        // Edge distance.
        double weight; 
};
