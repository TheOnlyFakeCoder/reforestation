#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<vector<int>> mapCreation(const double& areaHectare) {
    int conversion = 10000; // 10,000 meters squared is 1 hectare, 1.7 is the linear distance divided by 2
    int mapSquared = conversion*areaHectare; 
    int mapDimension = round(sqrt(mapSquared)/1.7);
    int emptyPlant = 0; // emptyPlantMeans no plant should be there. 
    double scaler = 1.6;
    vector<vector<int>> finalMap(round(mapDimension/scaler), vector<int>(round(mapDimension/scaler), emptyPlant));
    return finalMap;
    // Map meaning:
    // initializes a map full of zeros, it represents the possible dimensions.
    // It supposes squared dimensions for this terrain.
    // each jump between each consecutive value in the columns, corresponds to exactly 1.7 meters. 
    // it provides a way to see the behaviour of the algorithm, as well as understanding better competition.
}

vector<vector<int>> initializeUnfeasibleMap(const double& areaHectare) {
    vector<vector<int>> initialMap = mapCreation(areaHectare);
    size_t dimension = initialMap.size();
    int count = 0;
    for(size_t i = 0; i < dimension; i++) {
        if(i%2 == 0){
            for(size_t j = 0; j < dimension; j+=2){
                count +=1;
                initialMap[i][j] = 1;
            }
        } else {
            for(size_t j = 1; j < dimension; j+=2){
                count +=1;
                initialMap[i][j] = 1;
            }
        }

    }
    cout << "Total numbers of plants: " << to_string(count) << endl;

    return initialMap;
}
