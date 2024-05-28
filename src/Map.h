#ifndef MAP_H
#define MAP_H

#include <vector>
#include "Organism.h"
#include "Animal.h"
#include "Plant.h"
#include <iostream>

class Map {
private:
    int width;
    int height;
    //std::vector<std::vector<Organism*>> board;
    
    

public:
    std::vector<std::vector<Animal*>> animalBoard;
    std::vector<std::vector<Plant*>> plantBoard;
    Map(int width, int height);
    ~Map();
    bool spaceIsOpen(int x, int y);
    bool spaceHasNearbyOmnivore(int x, int y);
    bool spaceHasNearbyPlant(int x, int y);
    bool spaceHasNearbyHerbivore(int x, int y);
    bool spaceIsOccupiedByAnimal(int x, int y);
    bool spaceIsOccupiedByPlant(int x, int y);
    bool spaceIsOccupiedByOmnivore(int x, int y);
    bool spaceExists(int x, int y);
    bool canMoveToSpace(int x, int y, Animal* animal);
    Animal* getAnimal(int x, int y);
    Plant* getPlant(int x, int y);
    Animal* getNearbyPredator(Animal* animal);
    Animal* getNearbyPrey(Animal* animal);
    Plant* getNearbyEdiblePlant(Animal* animal);
    void moveAnimal(int x, int y, Animal* animal);
    void removeAnimal(Animal* animal);
    int getWidth() const;
    int getHeight() const;
    void performLivingFunctions();
    void printMap() const;
};

#endif
    