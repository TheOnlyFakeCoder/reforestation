#include "reforestation.h"
#include "writer.h"
#include <iostream>
#include <vector> 
#include <chrono>

using namespace std;

int main() {
    auto start = chrono::high_resolution_clock::now();
    vector<Plant> plants = readFile("plants.bin");
    for(int i = 0; i<plants.size(); i++){
        cout << plants[i] << endl;
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    cout << "Execution Time in ms " << duration.count() << endl;
    return 0;
}