#ifndef REFORESTATION_H
#define REFORESTATION_H
#include <iostream>
#include <cstring> 

using namespace std;

class Plant {
    private:
        char specie[32];
        double unitaryCost;
    public:
        const char* getSpecie () const { return specie; }
        double getUnitaryCost () const { return unitaryCost; }
        void setSpecie (const char* _specie) {
            strncpy(specie,_specie, sizeof(specie));
            specie[sizeof(specie) - 1] = '\0';
        }
        void setUnitaryCost (double _unitaryCost) { unitaryCost = _unitaryCost; }
        Plant() : specie(""), unitaryCost(0) {}
        Plant(const char* _specie, double _unitaryCost) : unitaryCost(_unitaryCost) {
            strncpy(specie,_specie, sizeof(specie));
            specie[sizeof(specie) - 1] = '\0';
        } 
        friend ostream& operator<<(ostream& os, const Plant plant) {
            os << "Plants Name: " << plant.specie 
            << " | Cost: " << plant.unitaryCost;
            return os;
        }
};

#endif