#ifndef REFORESTATION_H
#define REFORESTATION_H
#include <iostream>
#include <cstring> 
#include <array>
#include <vector>

using namespace std;

class Plant {
    private:
        char specie[32];
        double unitaryCost;
        int perHectare;
        array<int, 2> height;

    public:
        const char* getSpecie () const { return specie; }

        double getUnitaryCost () const { return unitaryCost; }

        int getPerHectare () const { return perHectare; }

        array<int,2> getHeight () const { return height; }        

        void setSpecie (const char* _specie) {
            strncpy(specie,_specie, sizeof(specie));
            specie[sizeof(specie) - 1] = '\0';
        }
        void setUnitaryCost (double _unitaryCost) { unitaryCost = _unitaryCost; }

        Plant() : unitaryCost(0), perHectare(0) {
            specie[0] = '\0';
        }

        Plant(const char* _specie, double _unitaryCost, int _perHectare, array<int,2> _height) : unitaryCost(_unitaryCost), perHectare(_perHectare), height(_height){
            strncpy(specie,_specie, sizeof(specie));
            specie[sizeof(specie) - 1] = '\0';

        } 

        friend ostream& operator<<(ostream& os, const Plant plant) {
            os << "Plants Name: " << plant.specie 
            << " | Cost: " << plant.unitaryCost
            << " | Per Hectare: " << plant.perHectare;
            return os;
        }

        ~Plant() {}
};

class Polygon {
    private:
        char polygon[16];
        double areaHectare;
        vector<int> quantityPlanted;

    public:

        const char* getPolygonId() const { return polygon; }
        double getAreaHectare() const { return areaHectare; }
        vector<int> getQuantityPlanted() const  {return quantityPlanted;}
        Polygon(): areaHectare(0), quantityPlanted({}) {
            polygon[0] = '\0';
        }

        Polygon(const char* _polygon, const double _areaHectare, const vector<int> _quantityPlanted): areaHectare(_areaHectare), quantityPlanted(_quantityPlanted) {
            strncpy(polygon, _polygon, sizeof(_polygon));
            polygon[sizeof(polygon)-1] = '\0';
        }

        friend ostream& operator<<(ostream& os, const Polygon& poly) {
            os << "Polygon " << poly.polygon
               << " | Area in Hectare " << poly.areaHectare
               << " | Quantity Planted: [";
            
            // Print out the vector elements cleanly
            for (size_t i = 0; i < poly.quantityPlanted.size(); ++i) {
                os << poly.quantityPlanted[i];
                if (i + 1 < poly.quantityPlanted.size()) {
                    os << ", ";
                }
            }
            os << "]";
            
            return os; // Mandatory: return the stream reference
        }

        ~Polygon() {}
};

class Wasted {
    private:
        vector<Polygon> polygons;
        vector<Plant> plants;
        vector<vector<double>> wastePerPolygon;

    public:

        Wasted() : polygons({}), plants({}), wastePerPolygon({}) {}

        Wasted(vector<Polygon> _polygons, vector<Plant> _plants): polygons(_polygons), plants(_plants){
            wastePerPolygon = calculateWastePerPolygon();
        }

        vector<Polygon> getPolygons() const { return polygons; }
        vector<Plant> getPlants() const { return plants; }
        
        vector<vector<double>> calculateWastePerPolygon() {
            // Clear existing data so calling this twice doesn't duplicate rows
            vector<vector<double>> localWasteMatrix;
            
            for (size_t i = 0; i < polygons.size(); i++) {
                vector<double> perPolygon;
                double area = polygons[i].getAreaHectare();
                vector<int> quantity = polygons[i].getQuantityPlanted();

                for (size_t j = 0; j < plants.size(); j++) {
                    double idealQuantity = plants[j].getPerHectare() * area;
                    double deficit = (idealQuantity - quantity[j])/idealQuantity;

                    
                    perPolygon.push_back(deficit*100); // Or apply percentage math here if preferred
                }
                localWasteMatrix.push_back(perPolygon);
            }
            
            return localWasteMatrix;
        }

        friend ostream& operator<<(ostream& os, const Wasted& wasted) {
            os << "=== Waste Analysis Per Polygon ===\n";
            
            for (size_t i = 0; i < wasted.wastePerPolygon.size(); i++) {
                // Print the Polygon ID if available, fallback to index otherwise
                if (i < wasted.polygons.size()) {
                    os << "Polygon " << wasted.polygons[i].getPolygonId() << " -> [";
                } else {
                    os << "Polygon " << i << " -> [";
                }

                // Print the waste values for each plant in this polygon
                for (size_t j = 0; j < wasted.wastePerPolygon[i].size(); j++) {
                    os << wasted.wastePerPolygon[i][j];
                    if (j + 1 < wasted.wastePerPolygon[i].size()) {
                        os << ", ";
                    }
                }
                os << "]\n";
            }
            
            return os;
        }
};

#endif