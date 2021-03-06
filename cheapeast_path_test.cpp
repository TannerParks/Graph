#include "Edge.h"
#include <vector>
#include <map>
#include <algorithm>

int cheapest_path(string start, string end, map<string, vector<Edge>> routes){
    map<string, int> cheapest_prices;   //record the cheapest prices for each city here
    map<string, string> cheapest_previous;  //cheapest previous city
    map<string, bool> visited;  //cities we've been to 
    vector<string> unvisited;   //cities we haven't been to yet
    vector<string> shortest_path;
    int price_thru_current;
    //int price_compare;
    //string min_price_city;
    string current_city;

    cheapest_prices.insert(pair<string, int>(start, 0));

    unvisited.push_back(start);

    current_city = start;

    while(!unvisited.empty()){
        //cout << "start of while loop" << endl;
        //price_compare = 0;
        visited[current_city] = true;
        //cout << "current city is " << current_city << " VISITED: " << visited[current_city] << endl;
        unvisited.erase(remove(unvisited.begin(), unvisited.end(), current_city));
        //cout << unvisited[0] << endl;
        for(auto elem : routes[current_city]){     //iterates through the routes of the current city
            //if(!price_compare || elem.cost < price_compare){
            //    price_compare = elem.cost;
            //    min_price_city = elem.destination;  //using these because I couldn't figure out how to just get the minimum
            //    //cout << min_price_city << " " << price_compare << endl;
            //}
            price_thru_current = cheapest_prices[current_city] + elem.cost;  //adds existing price of city to new price
            if(visited[elem.destination] != true){
                //cout << "Size of unvisited is " << unvisited.size() << endl;
                unvisited.push_back(elem.destination);
                //cout << visited[elem.destination] << endl;
                //cout << "Price for " << elem.destination << " is " << cheapest_prices[elem.destination] << endl;
                //cout << "Cost " << elem.cost << endl;
                //cout << "Price for " << elem.destination << " is " << cheapest_prices[elem.destination] << endl;
                //cout << "price from " << start << " to " << elem.destination << " is " << price_thru_current << endl;
                if(cheapest_prices[elem.destination] == 0 || price_thru_current < cheapest_prices[elem.destination]){
                    cheapest_prices[elem.destination] = price_thru_current;
                    cheapest_previous[elem.destination] = current_city;     //puts the cheapest previous city of the elem city into the cheapest_previous map
                    //cout << "Cheapest prices table for " << elem.destination << " " << cheapest_prices[elem.destination] << endl;
                    //cout << elem.destination << " cheapest price " << cheapest_prices[elem.destination] << " cheapest previous city " << cheapest_previous[elem.destination] << endl;

                }
                //cout << "       Cheapest prices table for " << elem.destination << " " << cheapest_prices[elem.destination] << endl;
            }
        }
        current_city = unvisited[0];
    }
    //cout << "out of while loop" << endl;
    
    current_city = end;
    while(current_city != start){
        //cout << "start of second while loop" << endl;
        shortest_path.push_back(current_city);  //there's no push_front so the order will be backwards
        if (cheapest_previous[current_city].empty()){
            cout << "There is no route from " << start << " to " << end << endl;
            return -1;
        }
        current_city = cheapest_previous[current_city]; //follow each city to its cheapest previous city
    }
    //cout << "out of second while loop" << endl;

    shortest_path.push_back(start);

    for (std::vector<string>::reverse_iterator city = shortest_path.rbegin(); city != shortest_path.rend(); ++city){
        cout << *city << " ";
    }
    
    //cout << "cheapest previous city  " << endl;
    //for(auto i : cheapest_previous){
    //    cout << i.first << " " << i.second << endl;
    //}
    //cout << endl << "cheapest prices " << endl;
    //for(auto i : cheapest_prices){
    //    cout << i.first << " " << i.second << endl;
    //}

    return -1;
}


int main(){
    map<string, vector<Edge>> routes;
    
    //routes["Atlanta"].push_back({"Chicago", 90}); //test for finding minimum closest city
    routes["Atlanta"].push_back({"Boston", 100});
    routes["Atlanta"].push_back({"Denver", 160});
    routes["Boston"].push_back({"Chicago", 120});
    routes["Boston"].push_back({"Denver", 180});
    routes["Chicago"].push_back({"El Paso", 80});
    routes["Denver"].push_back({"Chicago", 40});
    routes["Denver"].push_back({"El Paso", 140});
    routes["El Paso"].push_back({"Boston", 100});

    cheapest_path("Atlanta", "Chicago", routes);
    cheapest_path("Boston", "Atlanta", routes); //test for when there's no path


    return -1;
}