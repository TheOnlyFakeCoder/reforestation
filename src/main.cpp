#include "../include/reforestation.h"
#include "competition.h"
#include "writer.h"
#include "algorithm.h"
#include "map.h"
#include <iostream>
#include <vector> 
#include <chrono>

using namespace std;

int main() {
    auto start = chrono::high_resolution_clock::now();
    vector<Plant> plants = readPlantsFile("../bins/plants.bin");
    for(int i = 0; i<plants.size(); i++){
        cout << plants[i] << endl;
    }

    int totalPerHectare = 658;
    double budget = 12500;

    vector<Polygon> polygons = readPolygonsFile("../bins/polygons.bin");
    for(int i = 0;i<polygons.size(); i++) {
        cout << polygons[i] << endl;
    }



    vector<vector<double>> surveilance = {
        {100, 94.35, 92.65},
        {100, 95.87, 90.82},
        {100, 82.45, 74.53},
        {100, 95.17, 91.38},
        {100, 92.72, 82.87},
        {100, 89.86, 81.94},
        {100, 95.76, 91.98},
        {100, 88.60, 85.25},
        {100, 82.14, 81.79},
        {100, 88.43, 72.63},
    };




    Wasted waste = Wasted(polygons,plants);

    cout << waste << endl;


    vector<vector<double>> coefficientsMatrix = getCompetitionMatrix(plants);
    MatrixHandler().printMatrixElements(coefficientsMatrix);
    vector<double> steadyStates = Algorithm().markovSteadyState(coefficientsMatrix);

    cout << "\nSteady Values" << endl;
    MatrixHandler().printVectorElements(steadyStates);
    
    Algorithm().polygonsPenaltyPrint(polygons, coefficientsMatrix);

    for(size_t i = 0; i < polygons.size(); i++) {
        double sum = 0;
        for(size_t j = 0; j < polygons[i].getQuantityPlanted().size(); j ++) {
            sum += polygons[i].getQuantityPlanted()[j];
        }
        cout << "sum without coeficients P" <<to_string(i+1) << ": " << to_string(sum/polygons[i].getAreaHectare()) <<endl;
    }

    MatrixHandler().printMatrixElements(initializeUnfeasibleMap(polygons[0].getAreaHectare()));

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    cout << "Execution Time in ms " << duration.count() << endl;
    return 0;
}