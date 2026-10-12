#include "../include/reforestation.h"
#include <iostream>
#include <vector>
using namespace std;

class Algorithm {
    public:
        void calculatePolygonsPenalty(const Polygon& polygon, const vector<vector<double>>& coeficients) {
            
        }
        // Idea: given a competition, find the probabilities of competition with 
        // each E_j divided by te sum of each row
        // Steady states could remove a lot of complexity if this coefficients truly
        // represent the competition because, simplifying the search for the order that should 
        // be applied

        vector<vector<double>> stochasticCoefficients(const vector<vector<double>>& coefficients) {
            vector<vector<double>> probabilites;
            vector<double> rowSums;

            for(size_t i = 0; i < coefficients[0].size(); i++) {
                double sum = 0;
            }

            return probabilites;
        }
        vector<double> markovSteadyState() {

        }
};

