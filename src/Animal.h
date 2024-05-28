#ifndef ANIMAL_H
#define ANIMAL_H
#include <iostream>

#include "Organism.h"
class Map;
class Plant;
class Animal: public Organism{
    public:
    Animal(char id, int x_coordinate, int y_coordinate, int energy_level, bool isOmnivore) 
        : Organism{id, x_coordinate, y_coordinate}, 
          current_energy_level(energy_level), 
          max_energy_level(energy_level),
          isOmnivore(isOmnivore) {}

    bool isDead = false;
    int current_energy_level;
    int max_energy_level;
    bool isOmnivore;
    bool canEat(Animal& otherAnimal);
    bool canEat(Plant& plant);
    void Eat(Plant& plant, Map* map);
    void Eat(Animal& animal, Map* map);
    void Move(Map* map);
};

#endif