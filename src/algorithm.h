#include "../include/matrix_handler.h"
#include "../include/reforestation.h"
#include <iostream>
#include <vector>
using namespace std;

class Algorithm {
    public:
        // Idea: given a competition, find the probabilities of competition with 
        // each E_j divided by te sum of each row
        // Steady states could remove a lot of complexity if this coefficients truly
        // represent the competition because, simplifying the search for the order that should 
        // be applied
        vector<vector<double>> stochasticCoefficients(const vector<vector<double>>& coeficients) {
            vector<vector<double>> probabilities;
            vector<double> rowSums;
            size_t n = coeficients.size(); // Use actual matrix size

            for(size_t i = 0; i < n; i++) {
                double sum = 0;
                for(size_t j = 0; j < n; j++) {
                    sum += coeficients[i][j];
                }
                rowSums.push_back(sum);
            }

            for(size_t i = 0; i < n; i++) {
                vector<double> probsRow; // Fix: Reset/declare inside the loop
                for(size_t j = 0; j < n; j++) {
                    double singularProb = (rowSums[i] > 0) ? (coeficients[i][j] / rowSums[i]) : 0.0;
                    probsRow.push_back(singularProb);
                }
                probabilities.push_back(probsRow);
            }

            return probabilities;
        }

        vector<double> markovSteadyState(const vector<vector<double>>& coeficients) {
            vector<vector<double>> P = stochasticCoefficients(coeficients);
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

        double calculatePolygonsPenalty(const Polygon& polygon, const vector<vector<double>>& coeficients) {
            const vector<double> steadyStates = markovSteadyState(coeficients);
            const vector<int> quantityPolygons = polygon.getQuantityPlanted();
            double polygonPenalty = 0;
            for(size_t i = 0; i < quantityPolygons.size(); i++) {
                polygonPenalty += quantityPolygons[i]*steadyStates[i];
            }
            polygonPenalty /= polygon.getAreaHectare();
            return polygonPenalty;
        }

        void polygonsPenaltyPrint(const vector<Polygon>& polygons, const vector<vector<double>>& coeficients) {
            size_t numberPolygons = polygons.size();
            for(size_t i = 0; i < numberPolygons; i++){
                double penalty = calculatePolygonsPenalty(polygons[i], coeficients);
                cout << "Penalty for P" <<to_string(i+1) << ": " << to_string(penalty) <<endl;
            }
        }
};
