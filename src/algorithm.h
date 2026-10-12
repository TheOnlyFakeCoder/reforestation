#include "../include/matrix_handler.h"
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
            vector<vector<double>> probabilities;
            vector<double> rowSums;
            size_t n = coefficients.size(); // Use actual matrix size

            for(size_t i = 0; i < n; i++) {
                double sum = 0;
                for(size_t j = 0; j < n; j++) {
                    sum += coefficients[i][j];
                }
                rowSums.push_back(sum);
            }

            for(size_t i = 0; i < n; i++) {
                vector<double> probsRow; // Fix: Reset/declare inside the loop
                for(size_t j = 0; j < n; j++) {
                    double singularProb = (rowSums[i] > 0) ? (coefficients[i][j] / rowSums[i]) : 0.0;
                    probsRow.push_back(singularProb);
                }
                probabilities.push_back(probsRow);
            }

            return probabilities;
        }

        vector<double> markovSteadyState(const vector<vector<double>>& coefficients) {
            vector<vector<double>> P = stochasticCoefficients(coefficients);
            size_t n = P.size();
            if (n == 0) return {};
            
            vector<double> v(n, 1.0 / n);
            vector<double> v_next(n, 0.0);

            for (int iter = 0; iter < 10000; ++iter) {
                fill(v_next.begin(), v_next.end(), 0.0);
                
                for (size_t i = 0; i < n; ++i) {
                    for (size_t j = 0; j < n; ++j) {
                        v_next[j] += v[i] * P[i][j];
                    }
                }

                double diff = 0.0;
                for (size_t i = 0; i < n; ++i) {
                    diff += abs(v_next[i] - v[i]);
                }

                v = v_next;

                if (diff < 1e-18) {
                    break; 
                }
            }

            return v;
        }
};

