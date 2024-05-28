#ifndef PLANT_H
#define PLANT_H
#include <iostream>

#include "Organism.h"
class Map;

class Plant: public Organism{
    private:
    int current_growth;
    public:
    Plant(char id, int x_coordinate, int y_coordinate, int regrowth_coeff, int energy_points) 
        : Organism{id, x_coordinate, y_coordinate}, 
          regrowth_coeff(regrowth_coeff), 
          energy_points(energy_points), 
          isFullyGrown(true) {}

    int regrowth_coeff;
    int energy_points; 
    bool isFullyGrown;

    void resetGrowth();
    void grow(Map* map);
};

#endif