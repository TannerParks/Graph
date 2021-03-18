#include "Edge.h"
#include <vector>
#include <map>
#include <algorithm>

int cheapest_path(string start, string end, map<string, vector<Edge>> routes){
    map<string, int> cheapest_prices;   //record the cheapest prices for each city here
    map<string, string> cheapest_previous;  //cheapest previous city
    map<string, bool> visited;  //cities we've been to 
    vector<string> unvisited;   //cities we haven't been to yet
    vector<string> shortest_path;   //this is where we store the cities we'll be traveling too 
    int price_thru_current;     //use this to adjust prices in the loop below
    string current_city;    //use this to update what city we're checking the price of

    cheapest_prices.insert(pair<string, int>(start, 0));    //since we're in the starting city it wont cost anything to travel there

    unvisited.push_back(start); //puts the starting city into the unvisited list so the while loop can start

    current_city = start;

    while(!unvisited.empty()){
        visited[current_city] = true;   //mark current city as visited so we can erase it from the unvisited list until it's empty and the loop stops
        unvisited.erase(remove(unvisited.begin(), unvisited.end(), current_city));
        for(auto elem : routes[current_city]){     //iterates through the routes of the current city
            price_thru_current = cheapest_prices[current_city] + elem.cost;  //adds existing price of city to new price
            if(visited[elem.destination] != true){
                unvisited.push_back(elem.destination);
                if(cheapest_prices[elem.destination] == 0 || price_thru_current < cheapest_prices[elem.destination]){
                    cheapest_prices[elem.destination] = price_thru_current;
                    cheapest_previous[elem.destination] = current_city;     //puts the cheapest previous city of the elem city into the cheapest_previous map
                }
            }
        }
        current_city = unvisited[0];
    }
    current_city = end;
    while(current_city != start){
        shortest_path.push_back(current_city);  //there's no push_front so the order will be backwards
        if (cheapest_previous[current_city].empty()){   //if there aren't any paths to the destination...
            cout << "There is no route from " << start << " to " << end << endl; 
            return -1;  //...return
        }
        current_city = cheapest_previous[current_city]; //follow each city to its cheapest previous city
    }

    shortest_path.push_back(start);

    cout << "The cheapest route to " << end << " from " << start << " is:" << endl;
    for (std::vector<string>::reverse_iterator city = shortest_path.rbegin(); city != shortest_path.rend(); ++city){ //reverses the order of the shortest path
        cout << *city << " ";
    }
    cout << endl << "For a total price of $" << cheapest_prices[end] << endl;

    return -1;
}

void display_destinations(vector<Edge> place){
    for(auto elem : place){
        cout << elem.destination << " " << elem.cost << endl;
    }    
}

int main(){
    map<string, vector<Edge>> routes;

    routes["Atlanta"].push_back({"Boston", 100});
    routes["Atlanta"].push_back({"Denver", 160});
    routes["Boston"].push_back({"Chicago", 120});
    routes["Boston"].push_back({"Denver", 180});
    routes["Chicago"].push_back({"El Paso", 80});
    routes["Denver"].push_back({"Chicago", 40});
    routes["Denver"].push_back({"El Paso", 140});
    routes["El Paso"].push_back({"Boston", 100});
    
    display_destinations(routes["Atlanta"]);
    display_destinations(routes["Boston"]);
    display_destinations(routes["Chicago"]);
    display_destinations(routes["Denver"]);
    display_destinations(routes["El Paso"]);

    cheapest_path("Atlanta", "Chicago", routes);
    cheapest_path("Boston", "Atlanta", routes);

    //display_destinations(routes["Atlanta"]);
    //display_destinations(routes["Boston"]);
    //display_destinations(routes["Chicago"]);
    //display_destinations(routes["Denver"]);

    return -1;
}
