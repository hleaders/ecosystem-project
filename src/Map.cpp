#include "Map.h"
#include <stdexcept> // Include for std::out_of_range exception

Map::Map(int width, int height) : width(width), height(height) {
    // Resize the board to the specified size and initialize each space with an Organism object
    animalBoard.resize(width, std::vector<Animal*>(height, nullptr));
    plantBoard.resize(width, std::vector<Plant*>(height, nullptr));
}

Map::~Map() {
    // Delete dynamically allocated organisms
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            delete animalBoard[i][j];
            delete plantBoard[i][j];
        }
    }
}

bool Map::spaceHasNearbyOmnivore(int x, int y){
    if (y != 0){//Checking if there is an omnivore to the north
        if(animalBoard[x][y - 1] != nullptr){//Checking if the space is occupied
            if(animalBoard[x][y - 1]->isOmnivore){//Checking if the occupying organism is an omnivore
                return true;
            }
        }
    }
    if (y != height - 1){//Checking if there is an omnivore to the south
        if(animalBoard[x][y + 1] != nullptr){
            if(animalBoard[x][y + 1]->isOmnivore){
                return true;
            }
        }
    }
    if (x != width - 1){//Checking if there is an omnivore to the east
        if(animalBoard[x + 1][y] != nullptr){
            if(animalBoard[x + 1][y]->isOmnivore){
                return true;
            }
        }
    }
    if (x != 0){//Checking if there is an omnivore to the west
        if(animalBoard[x - 1][y] != nullptr){
            if(animalBoard[x - 1][y]->isOmnivore){
                return true;
            }
        }
    }
    return false;

}
bool Map::spaceIsOpen(int x, int y){
    return(spaceExists(x,y) && !spaceIsOccupiedByAnimal(x,y) && !spaceIsOccupiedByPlant(x,y)); //If the space exists and is not occupied by an animal or plant, it is open
}
bool Map::spaceHasNearbyPlant(int x, int y){
    if (y != 0){//Checking if there is a plant to the north
        if(plantBoard[x][y - 1] != nullptr){
            if(plantBoard[x][y - 1]->isFullyGrown){//Only fully grown plants are considered, as only fully grown plants matter for the purposes of this function
                return true;
            }
        }
    }
    if (y != height - 1){//Checking if there is a plant to the south
        if(plantBoard[x][y + 1] != nullptr){
            if(plantBoard[x][y + 1]->isFullyGrown){
                return true;
            }
        }
    }
    if (x != width - 1){//Checking if there is a plant to the east
        if(plantBoard[x + 1][y] != nullptr){
            if(plantBoard[x + 1][y]->isFullyGrown){
                return true;
            }
        }
    }
    if (x != 0){//Checking if there is a plant to the west
        if(plantBoard[x - 1][y] != nullptr){
            if(plantBoard[x - 1][y]->isFullyGrown){
                return true;
            }
        }
    }
    return false; //No fully grown plants were found

}
bool Map::spaceHasNearbyHerbivore(int x, int y){//This function is similar to spaceHasNearbyPlant, but it checks for herbivores instead of plants
    if (y != 0){
        if(animalBoard[x][y - 1] != nullptr){
            if(animalBoard[x][y - 1]->isOmnivore==false){
                return true;
            }
        }
    }
    if (y != height - 1){
        if(animalBoard[x][y + 1] != nullptr){
            if(animalBoard[x][y + 1]->isOmnivore==false){
                return true;
            }
        }
    }
    if (x != width - 1){
        if(animalBoard[x + 1][y] != nullptr){
            if(animalBoard[x + 1][y]->isOmnivore==false){
                return true;
            }
        }
    }
    if (x != 0){
        if(animalBoard[x - 1][y] != nullptr){
            if(animalBoard[x - 1][y]->isOmnivore==false){
                return true;
            }
        }
    }
    return false;

}
bool Map::spaceIsOccupiedByAnimal(int x, int y){//This function checks if a space is occupied by an animal
    if (!spaceExists(x,y)) {
        throw std::out_of_range("Coordinates out of range");
    }
    return animalBoard[x][y] != nullptr;
}
bool Map::spaceIsOccupiedByPlant(int x, int y){//This function checks if a space is occupied by a plant, regardless of growth status
    if (!spaceExists(x,y)) {
        throw std::out_of_range("Coordinates out of range");
    }
    return plantBoard[x][y] != nullptr;
}
bool Map::spaceIsOccupiedByOmnivore(int x, int y){//This function checks if a space is occupied by an omnivore
    if(!spaceExists(x,y)) {
        throw std::out_of_range("Coordinates out of range");
    }
    return animalBoard[x][y] != nullptr;
}
bool Map::spaceExists(int x, int y){//This function checks if a space exists on the map
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return false;
    }
    return true;
}
bool Map::canMoveToSpace(int x, int y, Animal* animalPtr){//This function checks if an animal can move to a space
    Animal& animal = *animalPtr;
    if(!spaceExists(x,y)){return false;} //If the space does not exist, the animal cannot move there
    if(spaceIsOccupiedByAnimal(x,y)){//If the space is occupied by an animal, the animal can only move there if it can eat the occupying animal
        Animal* occupyingAnimalPtr = getAnimal(x,y);
        Animal& occupyingAnimal = *occupyingAnimalPtr;
        if(animal.canEat(occupyingAnimal)){return true;}
        else{return false;}
    }
    if(spaceIsOccupiedByPlant(x,y)){//If the space is occupied by a plant, the animal can only move there if it can eat the occupying plant
        Plant* occupyingPlantPtr = getPlant(x,y);
        Plant& occupyingPlant = *occupyingPlantPtr;
        if(animal.canEat(occupyingPlant)){return true;}
        else{return false;}
    }
    else{//If the space is not occupied, the animal can move there
        return true;
    }
}
int Map::getHeight() const {//These functions return the height and width of the map
    return height;
}
int Map::getWidth() const {
    return width;
}
void Map::removeAnimal(Animal* animal){//This function removes an animal from the map

    animalBoard[animal->getXCoordinate()][animal->getYCoordinate()] = nullptr;
    animal = nullptr;
    delete animal;

}
Animal* Map::getAnimal(int x, int y) {//This function returns a pointer to an animal at a given location
    // Check if the coordinates are within bounds
    if (!spaceExists(x,y)) {
        throw std::out_of_range("Coordinates out of range");
    }

    if (animalBoard[x][y] == nullptr) {//If there is no animal at the given location, the function returns nullptr
        return nullptr;
    }
    
    return animalBoard[x][y];//Returning a pointer to the animal
}
Plant* Map::getPlant(int x, int y){//This function returns a pointer to a plant at a given location
    if (!spaceExists(x,y)) {
        throw std::out_of_range("Coordinates out of range");
    }
    if(plantBoard[x][y] == nullptr){//If there is no plant at the given location, the function returns nullptr
        return nullptr;
    }
    return plantBoard[x][y];//Returning a pointer to the plant
}
Animal* Map::getNearbyPredator(Animal* animalPtr){//This function returns a pointer to a nearby predator, if one exists
    int x = animalPtr->getXCoordinate();
    int y = animalPtr->getYCoordinate();
    Animal& animal = *animalPtr; //The animal that is calling the function
    if (y != 0){
        if(spaceIsOccupiedByOmnivore(x,y - 1)){//Checking if there is an omnivore to the north
            Animal* omnivorePtr = getAnimal(x,y-1);
            Animal& omnivore = *omnivorePtr;//The omnivore that is to the north
            if(omnivore.canEat(animal)){//If the omnivore can eat the animal, the function returns a pointer to the omnivore
                return omnivorePtr;
            }
        }
    }
    if (y != height - 1){//Checking if there is an omnivore to the south
        if(spaceIsOccupiedByOmnivore(x,y + 1)){
            Animal* omnivorePtr = getAnimal(x,y+1);
            Animal& omnivore = *omnivorePtr;
            if(omnivore.canEat(animal)){
                return omnivorePtr;
            }
        }
    }
    if (x != width - 1){//Checking if there is an omnivore to the east
        if(spaceIsOccupiedByOmnivore(x+1,y)){
            Animal* omnivorePtr = getAnimal(x+1,y);
            Animal& omnivore = *omnivorePtr;
            if(omnivore.canEat(animal)){
                return omnivorePtr;
            }
        }
    }
    if (x != 0){
        if(spaceIsOccupiedByOmnivore(x-1,y)){//Checking if there is an omnivore to the west
            Animal* omnivorePtr = getAnimal(x - 1,y);
            Animal& omnivore = *omnivorePtr;
            if(omnivore.canEat(animal)){
                return omnivorePtr;
            }
        }
    }
    return nullptr;//If no nearby predators were found, the function returns nullptr
}
Animal* Map::getNearbyPrey(Animal* animalPtr){//This function returns a pointer to a nearby prey, if one exists
    int x = animalPtr->getXCoordinate();
    int y = animalPtr->getYCoordinate();
    Animal& animal = *animalPtr; //The animal that is calling the function
    if (y != 0){
        if(spaceIsOccupiedByAnimal(x,y - 1)){//Checking if there is an animal to the north
            Animal* preyPtr = getAnimal(x,y-1);
            Animal& prey = *preyPtr;//The animal that is to the north
            if(animal.canEat(prey)){//If the animal can eat the prey, the function returns a pointer to the prey
                return preyPtr;
            }
        }
    }
    if (y != height - 1){//Checking if there is an animal to the south
        if(spaceIsOccupiedByAnimal(x,y + 1)){
            Animal* preyPtr = getAnimal(x,y+1);
            Animal& prey = *preyPtr;
            if(animal.canEat(prey)){
                return preyPtr;
            }
        }
    }
    if (x != width - 1){//Checking if there is an animal to the east
        if(spaceIsOccupiedByAnimal(x+1,y)){
            Animal* preyPtr = getAnimal(x+1,y);
            Animal& prey = *preyPtr;
            if(animal.canEat(prey)){
                return preyPtr;
            }
        }
    }
    if (x != 0){//Checking if there is an animal to the west
        if(spaceIsOccupiedByAnimal(x-1,y)){
            Animal* preyPtr = getAnimal(x - 1,y);
            Animal& prey = *preyPtr;
            if(animal.canEat(prey)){
                return preyPtr;
            }
        }
    }
    return nullptr;//If no nearby prey were found, the function returns nullptr
}
Plant* Map::getNearbyEdiblePlant(Animal* animalPtr){//This function returns a pointer to a nearby edible plant, if one exists
    int x = animalPtr->getXCoordinate();
    int y = animalPtr->getYCoordinate();
    Animal& animal = *animalPtr;//The animal that is calling the function
    if (y != 0){//Checking if there is a plant to the north
        if(spaceIsOccupiedByPlant(x,y - 1)){
            Plant* plantPtr = getPlant(x,y-1);
            Plant& plant = *plantPtr;//The plant that is to the north
            if(animal.canEat(plant)){//If the animal can eat the plant, the function returns a pointer to the plant
                return plantPtr;
            }
        }
    }
    if (y != height - 1){//Checking if there is a plant to the south
        if(spaceIsOccupiedByPlant(x,y + 1)){
            Plant* plantPtr = getPlant(x,y+1);
            Plant& plant = *plantPtr;
            if(animal.canEat(plant)){
                return plantPtr;
            }
        }
    }
    if (x != width - 1){//Checking if there is a plant to the east
        if(spaceIsOccupiedByPlant(x+1,y)){
            Plant* plantPtr = getPlant(x+1,y);
            Plant& plant = *plantPtr;
            if(animal.canEat(plant)){
                return plantPtr;
            }
        }
    }
    if (x != 0){//Checking if there is a plant to the west
        if(spaceIsOccupiedByPlant(x-1,y)){
            Plant* plantPtr = getPlant(x-1,y);
            Plant& plant = *plantPtr;
            if(animal.canEat(plant)){
                return plantPtr;
            }
        }
    }
    return nullptr;//If no nearby edible plants were found, the function returns nullptr
}
void Map::moveAnimal(int x, int y, Animal* animal) {//This function moves an animal to a new location

    if (!spaceExists(x,y)) {//If the space does not exist, the function throws an out_of_range exception
        throw std::out_of_range("Coordinates out of range");
    }
    animalBoard[animal->getXCoordinate()][animal->getYCoordinate()] = nullptr;//The animal's old location is set to nullptr
    //The animal's x and y coordinates are updated
    animal->x_coordinate = x;
    animal->y_coordinate = y;
    animalBoard[x][y] = animal;//The animal is placed at its new location

}
void Map::performLivingFunctions() {//This function performs the living functions of all organisms on the map
    // Create a list of all animals
    std::vector<Animal*> animals;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (animalBoard[j][i] != nullptr) {
                animals.push_back(animalBoard[j][i]);
            }
        }
    }
    // Call the move function for each animal
    for (Animal* animal : animals) {
        
        if(animal != nullptr){
            animal->Move(this);
        }
        
    }

    // Create a list of all plants
    std::vector<Plant*> plants;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (plantBoard[j][i] != nullptr) {
                plants.push_back(plantBoard[j][i]);
            }
        }
    }

    // Call the grow function for each plant
    for (Plant* plant : plants) {
        plant->grow(this);
    }
}
void Map::printMap() const {//This function prints the map
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            
            if (animalBoard[j][i] != nullptr){
                std::cout << animalBoard[j][i]->id;
            } 
            else if(plantBoard[j][i] != nullptr && plantBoard[j][i]->isFullyGrown){
                std::cout << plantBoard[j][i]->id;
            }
            else{
                std::cout << " ";
            }
            
        }
        std::cout << std::endl;
    }
}

