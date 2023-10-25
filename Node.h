#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Node
{
private:
    string name;
    int location_number;
    int cardinality;
    int *neighbors;
    double *weightedEdges;
public:
    //getters
    string getName(){
        return name;
    }
    int getLocationNumber(){
        return location_number;
    }
    int getCardinality(){
        return cardinality;
    }
    int getNeighbor(int i){
        return neighbors[i];
    }
    double getWeight(int i){
        return weightedEdges[i];
    }
    //setters
    void setName(string name){
        this->name = name;
    }
    void setCardinality(int number){
        this->cardinality = number;
    }
    void setNeighbor(int num, int i){
        this->neighbors[i] = num;
    }
    Node(){
        this->location_number = -1;
        this->name = "name not set";
        this->cardinality = -1;
    }
    Node(int number, string name, int cardinality, int neighborsArray[], double weightsArray[]){
        this->location_number = number;
        this->name = name;
        this->cardinality = cardinality;
        neighbors = (int*) malloc(sizeof(int) * cardinality);
        weightedEdges = (double*) malloc(sizeof(double) * cardinality);
        for (int i = 0; i < cardinality; ++i){
            neighbors[i] = neighborsArray[i];
            weightedEdges[i] = weightsArray[i];
        }
        
    }
    void print(){
        cout << "Location number: " << this->location_number << endl;
        cout << "Name           : " << this->name << endl;
        cout << "Cardinality    : " << this->cardinality << endl;
        for (int i = 0; i < cardinality; ++i){
            cout << neighbors[i] << " " << weightedEdges[i]  << endl;
        }
    }
    //no need for setLocationNumber because that's how we're initializing the Node();
};
