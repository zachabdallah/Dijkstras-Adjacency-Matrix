#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <vector>
#include "Node.h"
#define V 15
int src, graph[15][15];
double connections[15][15];
int path[15];
void printSolution(double dist[]){
    cout << "Vertex \t Distace from Source" << endl;
    for (int i = 0; i < V; ++i){
        cout << i+1 << " \t\t\t\t" << dist[i] << endl;
    }
}
void printArray(double dist[], bool sptSet[]){
    for (int i = 0; i < V; ++i){
        cout << "v" << i << "    " << dist[i] << "   " << sptSet[i] << endl;
    }
}
int minIndex(double dist[], bool sptSet[]){
    int min = INT_MAX;
    int min_index;
    //printArray(dist, sptSet);
    for (int v = 0; v < V; ++v){
        if (sptSet[v] == false && dist[v] < min){ //changed <= to <
            //if we haven't yet visited the node
            //and the distance to that node is less than min
            min = dist[v];
            min_index = v;
        }   //only return the smallest one
    }
    //cout << "returning minimum index " << min_index << ": " << dist[min_index] << endl;
    //cout << "Nodes visited: ";
    for (int i = 0; i < V; ++i){
        if (sptSet[i] == true){
            //cout << i+1 << " ";
        }
    }//cout << endl;
    return min_index;
}
void dijkstra(double connections[V][V], int src){
    double dist[V]; //tell us the distance from src node
    bool sptSet[V]; //tell us if we've visited each node
    for (int i = 0; i < V; ++i){
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
    dist[src-1] = 0;
    
    for (int i = 0; i < V-1; ++i){
        int u = minIndex(dist, sptSet);
        //u is the index of the smallest available node traversal
        sptSet[u] = true; //mark it visited
        for (int v = 0; v < V; ++v){
            if (!sptSet[v] && connections[u][v] && dist[u] + connections[u][v] < dist[v]){//&& dist[u] != INT_MAX //i don't fully understand why this is here, dist[u] should never be INT_MAX
                dist[v] = dist[u] + connections[u][v];
                path[v] = u;
                //basically, when we start off by calling minIndex(), it returns the index of the source node because it's the only one that's dist = 0 while the others have a dist = infinity
                //when we return to our algorithm, we check to see if there exists an edge between our node and any other nodes. This is denoted (connection[u][v]) as a boolean value, because if there is no edge then the value will be 0
                //we also check to see if its cumulative distance along with this connected node is less than the connected nodes current distance from the source
                //if it is in fact less than the nodes current distance, than we can update it because we found a better path to it. (or even just found a path)
                
                //we also should note that when we call minIndex(), it basically only has access to our set of nodes that have been given a value in dijkstras, and will never return the index of a node with a value of infinity.
                //our set of nodes to explore doesn't actually exist; it's not an array or any data structure holding information. It's just that when we update distance values in dijkstras for loop, the only vertices that pass the vibe check in minIndex() have an actual weight value that isn't infinity.
            }
        }
    }
    printSolution(dist);
}
void printPath(int src, int dest, int path[], Node graph[]){
    cout << "from " << src << " to " << dest << endl;
    int temp = dest;
    vector<int> pathInOrder;
    while (temp != src){
        pathInOrder.push_back(temp);
        temp = path[temp-1]; // make temp the prev vertex as part of spt
    }//then send it in again until it equals the src
    pathInOrder.push_back(src);
    cout << "Here is your path: " << endl;
    for (int i = pathInOrder.size()-1; i >= 0; --i){
        cout << graph[pathInOrder[i]-1].getName() << endl;
    }
    cout << endl;
}

int main(){
    ifstream myFile;
    myFile.open("/Users/zachabdallah/Downloads/xcode/Dijkstra's Algorithm/Vertices.txt");
    int amount;
    string whitespace_spam = " ";
    if (myFile.is_open()){
        myFile >> amount; //take the first input of the file
        cout << "Amount of locations: " << V << endl << endl;
        myFile >> whitespace_spam;
    }
    else{
        cout << "file not found" << endl;
        return 0;
    }
    Node graph[amount];
    
    while (myFile.good()){ //.good() returns true if no error has occured, can still read the file, and the eof has not been reached
        //create a node with a number and a name
        int location_number = 0;
        string location_name = "not set in main";
        int cardinality = 0;
        //declare
        
        getline(myFile, location_name);
        string nextNodeInfo = "no info";
        for (int i = 0; i < V; ++i){
            //part 1 of loop -- (number, name, cardinality)
            myFile >> location_number;
            myFile.get(); //the line below was reading in a newline character so we're getting rid of it here
            getline(myFile, location_name);
            myFile >> cardinality;
            
            //part 2 of loop -- (neighbors and edge weights)
            int nextNode;
            double weight;
            int neighborArray[cardinality];
            double neighborWeights[cardinality];
            for (int i = 0; i < cardinality; ++i){
                //basically, we want to continue to add to information to the node based on how many other nodes it's connected to
                //Then, we create a node class with all of this information passed to it by 2 different arrays
                myFile >> nextNode;
                myFile >> weight;
                neighborArray[i] = nextNode;
                neighborWeights[i] = weight;
            }
            
            //part 3 of the loop -- create the node and put it in our graph array
            Node location(location_number, location_name, cardinality, neighborArray, neighborWeights); //create a node
            graph[i] = location; //put it in the array
            //graph[i].print();
            myFile >> whitespace_spam;
            
        }
    }
    for (int i = 0; i < amount; ++i){
        for (int z = 0; z < V; ++z){
            connections[i][z] = 0;
        }
        for (int x = 0; x < graph[i].getCardinality(); ++x){
            connections[i][graph[i].getNeighbor(x)-1] = graph[i].getWeight(x);
        }
        connections[i][i] = 0;
        for (int y = 0; y < V; ++y){
            //cout << connections[i][y] << " ";
        }
        //cout << endl;
    }//initialize the matrix
    
    char c;
    int dest;
    do {
        cout << "Where would you like to start? Enter node number: " << endl;
        cin >> src;
        while (src < 1 || src > amount){
            cout << "That node doesn't exist, try again." << endl;
            cout << "Node locations are between " << 1 << " and " << V << endl;
            cin >> src;
        }
        cout << "where do you want to go? " << endl;
        cin >> dest;
        while (dest < 1 || dest > amount){
            cout << "That node doesn't exist, try again." << endl;
            cout << "Node locations are between " << 1 << " and " << V << endl;
            cin >> dest;
        }
        dijkstra(connections, src);
        
        //cout << "Previous Indices as part of the shortest path from source: " << endl;
        for (int i = 0; i < V; ++i){
            //cout <<"Index: " << i << "         ";
            ++path[i];
            //cout <<i+1 << ": "<<  path[i] << " ";
            //cout << endl;
        }
        cout << endl << "Starting from " << graph[src-1].getName();
        cout << " and going to " << graph[dest-1].getName() << endl;
        printPath(src, dest, path, graph);
        cout << " do you want to repeat?" << endl;
        cin >> c;
    }while (c == 'y' || c == 'Y');
    cout << "alright, cya" << endl;
    return 0;
}
