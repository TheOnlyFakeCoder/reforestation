#include "../include/reforestation.h"
#include "writer.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    const vector<Plant>& plants= {
        Plant("Agave lechuguilla", 26),
        Plant("Agave salmiana", 26),
        Plant("Agave scabra", 26),
        Plant("Agave striata", 26),
        Plant("Opuntia cantabrigiensis", 18),
        Plant("Opuntia engelmani", 21),
        Plant("Opuntia robusta", 18),
        Plant("Opuntia streptacanta", 18),
        Plant("Prosopis laevigata", 26.5),
        Plant("Yucca filifera", 26)
    };
    writeToFile(plants, "../bins/plants.bin");
    return 0;
}