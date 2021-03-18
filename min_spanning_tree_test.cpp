#include "Edge.h"
#include <vector>
#include <map>
#include <algorithm>

int min_spanning_tree(string starting_vertex, map<string, vector<Edge>> routes){
    map<string, bool> visited;
    vector<string> unvisited;
    string min_adjacent;
    string current_city;
    int compare_cost;
    int total_cost;
    string current;

    current_city = starting_vertex;

    for(auto elem : routes){    //populates the unvisited list with all available cities
        unvisited.push_back(elem.first);
    }
    //unvisited.erase(remove(unvisited.begin(), unvisited.end(), starting_vertex));

    while(!unvisited.empty()){
        min_adjacent.erase();
        compare_cost = 0;
        visited[current_city] = true;
        unvisited.erase(remove(unvisited.begin(), unvisited.end(), current_city));
        for(auto elem : routes[current_city]){
            if(!compare_cost || elem.cost < compare_cost){  //finds the cheapest adjacent city
                compare_cost = elem.cost;
                min_adjacent = elem.destination;
            } 
        }
        current_city = min_adjacent;
        cout << current_city << endl;
        //break;
    }




    //for(auto elem : unvisited){
    //    cout << elem << endl;
    //}

    //for(int i = 0; i < routes.size() - 1; i++){
    //    cout << "Howdy" << endl;
    //}

    return -1;
}

int main(){
    map<string, vector<Edge>> routes;
    
    //routes["Atlanta"].push_back({"Chicago", 90}); //test for finding minimum closest city
    routes["Atlanta"].push_back({"Boston", 90});
    routes["Atlanta"].push_back({"Denver", 160});
    routes["Boston"].push_back({"Chicago", 120});
    routes["Boston"].push_back({"Denver", 180});
    routes["Chicago"].push_back({"El Paso", 80});
    routes["Denver"].push_back({"Chicago", 40});
    routes["Denver"].push_back({"El Paso", 140});
    routes["El Paso"].push_back({"Boston", 100});

    min_spanning_tree("Atlanta", routes);

    return -1;
}