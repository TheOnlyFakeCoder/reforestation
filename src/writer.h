#ifndef WRITER_H
#define WRITER_H
#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include "reforestation.h"

using namespace std;

void writeToFile(const vector<Plant>& plants, const string& filename) {
    ofstream outFile(filename, ios::binary);

    if(!outFile) {
        cerr<< "Error opening file \n";
        return;
    }

    size_t vectorSize = plants.size();
    outFile.write(reinterpret_cast<const char*>(&vectorSize), sizeof(vectorSize));
    outFile.write(reinterpret_cast<const char*>(plants.data()), vectorSize * sizeof(Plant));
}

vector<Plant> readFile(const string& filename) {
    ifstream inputFile(filename, ios::binary);
    if(!inputFile) {
        cerr << "Error opening file \n";
        return {};
    }


    vector<Plant> plants;

    size_t vectorSize = 0;
    inputFile.read(reinterpret_cast<char*>(&vectorSize), sizeof(vectorSize));

    plants.resize(vectorSize);

    inputFile.read(reinterpret_cast<char*>(plants.data()), vectorSize*sizeof(Plant));
    
    return plants;
}

#endif