#include <iostream>
#include <vector>
#include <cmath> 
#include "../include/reforestation.h"

using namespace std;

vector<vector<double>> getCompetitionMatrix(vector<Plant> plants) {
    // This function aims to get a coefficient matrix
    // Height avg is given by the mean of the two heights reported
    // Height difference given by each plants difference
    // density difference given by the difference of each perHectare
    // Competition Matrix is given by 1/(1+ HeightDiff+DensityDiff)
    vector<double> avgHeights;
    for(size_t i = 0;i<plants.size();i++) {
        double avgHeight = (plants[i].getHeight()[1] + plants[i].getHeight()[0])/2.0;
        avgHeights.push_back(avgHeight);
    }

    vector<vector<double>> heightsDiffs;
    for(size_t i = 0; i<avgHeights.size(); i++) {
        vector<double> rowHeights;
        for(size_t j = 0; j< avgHeights.size();j++){
            double diffs =abs(avgHeights[i] - avgHeights[j]);
            rowHeights.push_back(diffs);
        }
        heightsDiffs.push_back(rowHeights);
    }

    vector<int> densities;
    for(size_t i = 0; i<plants.size(); i++) {
        densities.push_back(plants[i].getPerHectare());
    }

    vector<vector<int>> densitiesDiffs;
    for(size_t i = 0;i<densities.size(); i++) {
        vector<int> rowDiffs;
        for(size_t j = 0; j< densities.size(); j++) {
            int diff = abs(densities[i] - densities[j]);
            rowDiffs.push_back(diff);
        }
        densitiesDiffs.push_back(rowDiffs);
    }

    vector<vector<double>> coefficients;
    for(size_t i = 0; i< densitiesDiffs[0].size();i++) {
        vector<double> rowCoefficients;
        for(size_t j = 0; j<densitiesDiffs[0].size();j++) {
            double coefficient = 1/(1+ densitiesDiffs[i][j]+ heightsDiffs[i][j]);
            rowCoefficients.push_back(coefficient);
        }
        coefficients.push_back(rowCoefficients);
    }
    return coefficients;
}

void printMatrixElements(const vector<vector<double>> matrix) {
    for (const auto& row : matrix) {
        cout << "[ ";
        for (double val : row) {
            cout << val << " ";
        }
        cout << "]\n";
    }
}

void printVectorElements(const vector<double> vec) {
    cout << "[ ";
    for (const auto& val: vec) {
        cout << val << " ";
    } 
    cout << "]" << endl;
}