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
};

class Polygon {
    private:
        char polygon[16];
        double areaHectare;
        vector<int>quantityPlanted;

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
        
        
};

#endif