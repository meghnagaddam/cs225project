#include "algorithms.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


int main(){
    
    Map flightmap("routes_clean.csv", "airports.dat");
    //input file
    ifstream ifs;
    //output file
    ofstream ofs;
    ifs.open("input.txt");
    ofs.open("output.txt");

    //Get location to start BFS from
    string startBFSlocation;
    //Initialize starting BFS index as invalid.
    int startBFS = -1;
    while (startBFS < 0) {
        getline(ifs, startBFSlocation);
        //converts index to airport ID.
        startBFS = flightmap.toIATA(startBFSlocation);
    }

    //Find BFS airport and search.
    cout << ">>>>>>>>>>> BFS Start Location <<<<<<<<<<<" << endl << "                  " << flightmap.convertToName(startBFSlocation) << endl << endl;
    ofs << ">>>>>>>>>>> BFS Start Location <<<<<<<<<<<" << endl << "                  " << startBFSlocation << endl << endl;
    vector<string> bfs = flightmap.BFS(startBFS);
    int count = 0;
    for (size_t i = 0; i < bfs.size() - 1; i++) {
        //Just in case IATA column is empty (avoids possible errors)
        if (bfs[i] != "") {
            ofs << bfs[i] << ", ";
            count++;
            if (count == 20) {
                ofs << endl;
                count = 0;
            }
        }
    }
    ofs << bfs[bfs.size() - 1] << endl;
    ofs << endl;
    cout << "BFS Success!" << endl << endl;

    //Continues to find optimal paths until end of input.txt
    while (ifs.peek() != EOF) {

        //Find starting airport
        string startingAirport;
        int startingAirportIndex = -1; 

        while (startingAirportIndex < 0) {
            //Check to see if input.txt still has valid airports.
            if (ifs.peek() == EOF) {
                cout<<"Please add valid USA airports."<<endl;
                return 0;
            }
            getline(ifs, startingAirport);
            //Convert index to ID.
            startingAirportIndex = flightmap.toIATA(startingAirport);
        }
    
        cout << ">>>>>>>>>>> Source Airport <<<<<<<<<<<" << endl << "                  " << flightmap.convertToName(startingAirport) << endl << endl;
        ofs << ">>>>>>>>>>> Source Airport <<<<<<<<<<<" << endl << "                  " << startingAirport << endl << endl;

        //Find final airport.
        string finalAirport;
        //Initialize as invalid index.
        int finalAirportIndex = -1; 
        while (finalAirportIndex < 0) {
            //make sure valid airport exists in input.txt
            if (ifs.peek() == EOF) { 
                cout<<"Please add valid destination US airport to input.txt"<<endl;
                return 0;
            }
            getline(ifs, finalAirport);
            //Convert index to airport ID.
            finalAirportIndex = flightmap.toIATA(finalAirport);
        }
        cout << ">>>>>>>>>>> Destination Airport <<<<<<<<<<<" << endl << "                  " << flightmap.convertToName(finalAirport) << endl << endl;
        ofs << ">>>>>>>>>>> Destination Airport <<<<<<<<<<<" << endl << "                  " << finalAirport << endl << endl;


        //Use BFS again from start airport to final airport.
        vector<string> bfsPath = flightmap.BFS(startingAirportIndex, finalAirportIndex);
        //No route found from starting airport to destination.
        if (bfsPath.empty() == true) {
            cout << "There are no possible commercial flight routes that connect " << startingAirport << " and " << finalAirport << endl;
            ofs << "There are no possible commercial flight routes that connect " << startingAirport <<" and " << finalAirport << endl;
            cout << endl;
            ofs << endl;
            //Stops search.
            continue;
        }
        cout << "To minimize total number of layovers, the path you should take is: " << endl;
        ofs << "To minimize total number of layovers, the path you should take is: " << endl;
        for (size_t i = 0; i < bfsPath.size() - 1; i++) {
            string s = bfsPath[i];
            cout << flightmap.convertToName(s) << " to ";
            ofs << s << " to ";
        }
        cout << bfsPath[bfsPath.size() - 1] << endl;
        ofs << bfsPath[bfsPath.size() - 1] << endl;

        //Dijskstras algorithm
        tuple<vector<string>,double> dijkstra = flightmap.dijkstra(startingAirportIndex, finalAirportIndex);
        cout << endl << "To minimize total distance flown, the ideal path is: " << endl;
        ofs << endl << "To minimize total distance flown, the ideal path is: " << endl;
        for (size_t i = 0; i < get<0>(dijkstra).size() - 1; i++) {
            cout << flightmap.convertToName(get<0>(dijkstra)[i]) << " to ";
            ofs << get<0>(dijkstra)[i] << " to ";
        }
        cout << get<0>(dijkstra)[get<0>(dijkstra).size() - 1] << endl;
        ofs << get<0>(dijkstra)[get<0>(dijkstra).size() - 1] << endl;
        cout << endl << ">>>>>>>>>>> Total Distance Flown <<<<<<<<<<<" << endl << "                  " << get<1>(dijkstra) << " miles" << endl << endl;
        ofs << endl << "Total distance flown: " << get<1>(dijkstra) << " miles" << endl;
    }

    ifs.close();
    ofs.close();

    return 0;
    


/*

    //USE BELOW FOR TEST CASES
    //CHOOSE FROM THE FOLLOWING INPUT FILES:
    // test0.txt -- makes sure inputs are recognized even if they are not all capitalized, also checks output for no possible flights connecting ORD to PIE
    // test1.txt -- there should be  direct flight from ord to lax, which will also be the shortest path from ord to lax
    // test2.txt  -- since there are no direct flights from ORD to MDW, dijsktras will output MSP since MN is the next closest airport
    

    Map flightmap("routes_small.csv", "airports_small.dat"); //this uses a smaller dataset to ensure outputs are correct
    //input file
    ifstream ifs;
    //output file
    ofstream ofs;
    ifs.open("test0.txt"); //change to desired test file 
    ofs.open("output.txt"); //will output conducted test 

    //Get location to start BFS from
    string startBFSlocation;
    //Initialize starting BFS index as invalid.
    int startBFS = -1;
    while (startBFS < 0) {
        getline(ifs, startBFSlocation);
        //converts index to airport ID.
        startBFS = flightmap.toIATA(startBFSlocation);
    }

    //Find BFS airport and search.
    cout << ">>>>>>>>>>> BFS Start Location <<<<<<<<<<<" << endl << "                  " << flightmap.convertToName(startBFSlocation) << endl << endl;
    ofs << ">>>>>>>>>>> BFS Start Location <<<<<<<<<<<" << endl << "                  " << startBFSlocation << endl << endl;
    vector<string> bfs = flightmap.BFS(startBFS);
    int count = 0;
    for (size_t i = 0; i < bfs.size() - 1; i++) {
        //Just in case IATA column is empty (avoids possible errors)
        if (bfs[i] != "") {
            ofs << bfs[i] << ", ";
            count++;
            if (count == 20) {
                ofs << endl;
                count = 0;
            }
        }
    }
    ofs << bfs[bfs.size() - 1] << endl;
    ofs << endl;
    cout << "BFS Success!" << endl << endl;

    //Continues to find optimal paths until end of input.txt
    while (ifs.peek() != EOF) {

        //Find starting airport
        string startingAirport;
        int startingAirportIndex = -1; 

        while (startingAirportIndex < 0) {
            //Check to see if input.txt still has valid airports.
            if (ifs.peek() == EOF) {
                cout<<"Please add valid USA airports."<<endl;
                return 0;
            }
            getline(ifs, startingAirport);
            //Convert index to ID.
            startingAirportIndex = flightmap.toIATA(startingAirport);
        }
    
        cout << ">>>>>>>>>>> Source Airport <<<<<<<<<<<" << endl << "                  " << flightmap.convertToName(startingAirport) << endl << endl;
        ofs << ">>>>>>>>>>> Source Airport <<<<<<<<<<<" << endl << "                  " << startingAirport << endl << endl;

        //Find final airport.
        string finalAirport;
        //Initialize as invalid index.
        int finalAirportIndex = -1; 
        while (finalAirportIndex < 0) {
            //make sure valid airport exists in input.txt
            if (ifs.peek() == EOF) { 
                cout<<"Please add valid destination US airport to input.txt"<<endl;
                return 0;
            }
            getline(ifs, finalAirport);
            //Convert index to airport ID.
            finalAirportIndex = flightmap.toIATA(finalAirport);
        }
        cout << ">>>>>>>>>>> Destination Airport <<<<<<<<<<<" << endl << "                  " << flightmap.convertToName(finalAirport) << endl << endl;
        ofs << ">>>>>>>>>>> Destination Airport <<<<<<<<<<<" << endl << "                  " << finalAirport << endl << endl;


        //Use BFS again from start airport to final airport.
        vector<string> bfsPath = flightmap.BFS(startingAirportIndex, finalAirportIndex);
        //No route found from starting airport to destination.
        if (bfsPath.empty() == true) {
            cout << "There are no possible commercial flight routes that connect " << startingAirport << " and " << finalAirport << endl;
            ofs << "There are no possible commercial flight routes that connect " << startingAirport <<" and " << finalAirport << endl;
            cout << endl;
            ofs << endl;
            //Stops search.
            continue;
        }
        cout << "To minimize total number of layovers, the path you should take is: " << endl;
        ofs << "To minimize total number of layovers, the path you should take is: " << endl;
        for (size_t i = 0; i < bfsPath.size() - 1; i++) {
            string s = bfsPath[i];
            cout << flightmap.convertToName(s) << " to ";
            ofs << s << " to ";
        }
        cout << bfsPath[bfsPath.size() - 1] << endl;
        ofs << bfsPath[bfsPath.size() - 1] << endl;

        //Dijskstras algorithm
        tuple<vector<string>,double> dijkstra = flightmap.dijkstra(startingAirportIndex, finalAirportIndex);
        
        cout << endl;
        cout << "Dijkstra Success!" << endl << endl;
        cout << endl << "To minimize total distance flown, the ideal path is: " << endl;
        ofs << endl << "To minimize total distance flown, the ideal path is: " << endl << endl;
        for (size_t i = 0; i < get<0>(dijkstra).size() - 1; i++) {
            cout << flightmap.convertToName(get<0>(dijkstra)[i]) << " to ";
            ofs << get<0>(dijkstra)[i] << " to ";
        }
        
        cout << get<0>(dijkstra)[get<0>(dijkstra).size() - 1] << endl;
        ofs << get<0>(dijkstra)[get<0>(dijkstra).size() - 1] << endl;
       
    }

    ifs.close();
    ofs.close();

    return 0;

    */
}
