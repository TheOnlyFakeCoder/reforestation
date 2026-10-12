#ifndef WRITER_H
#define WRITER_H
#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include "../include/reforestation.h"

using namespace std;

void writeSteadyValues(const vector<double>& steady, const string& filename) {
    ofstream outFile(filename, ios::binary);

    if(!outFile) {
        cout << "Error opening file \n";
        return;
    }

    size_t vectorSize = steady.size();
    outFile.write(reinterpret_cast<const char*>(&vectorSize), sizeof(vectorSize));
    outFile.write(reinterpret_cast<const char*>(steady.data()), vectorSize * sizeof(double));
}

void writeToFilePlants(const vector<Plant>& plants, const string& filename) {
    ofstream outFile(filename, ios::binary);

    if(!outFile) {
        cerr<< "Error opening file \n";
        return;
    }

    size_t vectorSize = plants.size();
    outFile.write(reinterpret_cast<const char*>(&vectorSize), sizeof(vectorSize));
    outFile.write(reinterpret_cast<const char*>(plants.data()), vectorSize * sizeof(Plant));
}

void writeToFilePolygons(const vector<Polygon>& polygons, const string& filename) {
    ofstream outFile(filename, ios::binary);

    if(!outFile) {
        cerr << "Error opening file \n";
        return;
    }

    // 1. Write how many polygons there are
    size_t vectorSize = polygons.size();
    outFile.write(reinterpret_cast<const char*>(&vectorSize), sizeof(vectorSize));

    // 2. Loop through each polygon safely and write its individual components
    for (const auto& poly : polygons) {
        // Write the fixed-size character array (ID)
        outFile.write(poly.getPolygonId(), 16);

        // Write the double area value
        double area = poly.getAreaHectare();
        outFile.write(reinterpret_cast<const char*>(&area), sizeof(area));

        // Write the quantity vector safely
        const vector<int>& quantities = poly.getQuantityPlanted();
        size_t qtySize = quantities.size();
        
        // First write how many integers are in this polygon's vector
        outFile.write(reinterpret_cast<const char*>(&qtySize), sizeof(qtySize));
        
        // Then write the actual integer elements from the vector
        if (qtySize > 0) {
            outFile.write(reinterpret_cast<const char*>(quantities.data()), qtySize * sizeof(int));
        }
    }
}

vector<Plant> readPlantsFile(const string& filename) {
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

vector<Polygon> readPolygonsFile(const string& filename) {
    ifstream inputFile(filename, ios::binary);
    if (!inputFile) {
        cerr << "Error opening file \n";
        return {};
    }

    size_t vectorSize = 0;
    inputFile.read(reinterpret_cast<char*>(&vectorSize), sizeof(vectorSize));

    vector<Polygon> polygons;
    polygons.reserve(vectorSize);

    for (size_t i = 0; i < vectorSize; ++i) {
        // 1. Read the fixed-size ID array
        char idBuffer[16];
        inputFile.read(idBuffer, sizeof(idBuffer));

        // 2. Read the area
        double area = 0.0;
        inputFile.read(reinterpret_cast<char*>(&area), sizeof(area));

        // 3. Read the quantity vector's size, then its elements
        size_t qtySize = 0;
        inputFile.read(reinterpret_cast<char*>(&qtySize), sizeof(qtySize));

        vector<int> quantities(qtySize);
        if (qtySize > 0) {
            inputFile.read(reinterpret_cast<char*>(quantities.data()), qtySize * sizeof(int));
        }

        // 4. Construct the polygon and add it to our vector
        polygons.emplace_back(idBuffer, area, quantities);
    }

    return polygons;
}

#endif