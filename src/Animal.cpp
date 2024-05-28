#include "Animal.h"
#include "Map.h" // Assuming Map class is included here
#include <cstdlib>
#include <ctime>


bool Animal::canEat(Animal& otherAnimal){//Check if animal can eat another animal
    if(!isOmnivore){return false;}
    int possible_energy_level = current_energy_level + otherAnimal.current_energy_level;//Check if energy level will exceed max energy level, if so, the animal cannot eat the other animal
    if(possible_energy_level > max_energy_level){return false;}
    return true;

}
bool Animal::canEat(Plant& plant){//Check if animal can eat a plant
    if(plant.isFullyGrown == false){return false;}
    int possible_energy_level = current_energy_level + plant.energy_points;//Check if energy level will exceed max energy level, if so, the animal cannot eat the plant
    if(possible_energy_level > max_energy_level){return false;}
    return true;
}
void Animal::Eat(Animal& consumedAnimal, Map* mapPtr) {//Eat another animal
    Map& map = *mapPtr;
    if (!isOmnivore) {//If an animal is not an omnivore, it cannot eat another animal
        throw std::runtime_error("Non-omnivores cannot eat other animals.");
    }

    
    // Increase the current energy level by the consumed animal's current energy level
    current_energy_level += consumedAnimal.current_energy_level;

    // Ensure current energy level doesn't exceed max energy level
    if (current_energy_level > max_energy_level) {
        current_energy_level = max_energy_level;
    }

    // Remove the consumed animal from the map
    
    map.removeAnimal(&consumedAnimal);
    consumedAnimal.isDead = true;

}
void Animal::Eat(Plant& consumedPlant, Map* mapPtr){// Eat a plant
    Map& map = *mapPtr;
    if (!consumedPlant.isFullyGrown) {
        throw std::runtime_error("Plant is not fully grown and cannot be eaten");
    }
    // Increase the current energy level by the consumed animal's current energy level
    current_energy_level += consumedPlant.energy_points;

    // Ensure current energy level doesn't exceed max energy level
    if (current_energy_level > max_energy_level) {
        current_energy_level = max_energy_level;
    }


    consumedPlant.resetGrowth();//When a plant is eaten, it remains in the same location but is no longer fully grown
    
}

void Animal::Move(Map* mapPtr){//Move the animal
    if (isDead) {//This will catch if the animal has died before its chance to move in performLvivingFunctions
        return;
    }
    Map& map = *mapPtr;
    Animal* nearbyPredator = map.getNearbyPredator(this);
    Plant* nearbyEdiblePlant = map.getNearbyEdiblePlant(this);

    if(!isOmnivore){ //Herbivore move behavior
        if(nearbyPredator != nullptr && current_energy_level >= 1){//If there is a predator nearby and the animal has enough energy to move
            int x_diff = x_coordinate - nearbyPredator->getXCoordinate();
            int y_diff = y_coordinate - nearbyPredator->getYCoordinate();

            if(x_diff != 0){//If the predator is to the left or right of the animal
                if(map.canMoveToSpace(x_coordinate+x_diff,y_coordinate, this)){
                    //If the space the animal wants to move to is open, move there and eat the plant if there is one
                    if(map.spaceIsOccupiedByPlant(x_coordinate+x_diff,y_coordinate)){
                        Plant* plantPtr = map.getPlant(x_coordinate+x_diff, y_coordinate);
                        Plant& plant = *plantPtr;
                        Eat(plant, mapPtr); 
                        
                       
                    }
                    map.moveAnimal(x_coordinate+x_diff,y_coordinate,this);
                    //x_coordinate += x_diff;

                }

            }
            else{//If the predator is above or below the animal
                if(map.canMoveToSpace(x_coordinate,y_coordinate+y_diff, this)){
                    
                    if(map.spaceIsOccupiedByPlant(x_coordinate,y_coordinate+y_diff)){
                        Plant* plantPtr = map.getPlant(x_coordinate, y_coordinate+y_diff);
                        Plant& plant = *plantPtr;
                        Eat(plant, mapPtr);
                        
                    }
                    map.moveAnimal(x_coordinate,y_coordinate+y_diff,this);
                    //y_coordinate += y_diff;

                }

            }

        }
        
        
        else if(nearbyEdiblePlant != nullptr){//If there is an edible plant nearby, eat it
            int x_diff = x_coordinate - nearbyEdiblePlant->getXCoordinate();
            int y_diff = y_coordinate - nearbyEdiblePlant->getYCoordinate();
            Plant& plant = *nearbyEdiblePlant;
            if(canEat(plant)){
                Eat(plant, mapPtr);
            }
            
            if(x_diff != 0){
                map.moveAnimal(x_coordinate-x_diff,y_coordinate,this);
                //x_coordinate -= x_diff;
                }

            else{
                map.moveAnimal(x_coordinate,y_coordinate - y_diff,this);
                //y_coordinate -= y_diff;
                }
            }

        
        else{//If there is no predator or edible plant nearby, move randomly
            int possibleMoves[4] {0,0,0,0};
            bool possibleMoveExists = false;
            if(map.spaceIsOpen(x_coordinate, y_coordinate-1)){//Check if the space north of the animal is open
                possibleMoves[0]= 1;
                possibleMoveExists = true;
                }
            if(map.spaceIsOpen(x_coordinate, y_coordinate+1)){//Check if the space south of the animal is open
                possibleMoves[1]= 1;
                possibleMoveExists = true;
                }
            if(map.spaceIsOpen(x_coordinate+1, y_coordinate)){//Check if the space east of the animal is open
                possibleMoves[2]= 1;
                possibleMoveExists = true;
                }
            if(map.spaceIsOpen(x_coordinate-1, y_coordinate)){//Check if the space west of the animal is open
                possibleMoves[3]= 1;
                possibleMoveExists = true;
                }
            if(possibleMoveExists){//If there is an open space, move to a random open space
                std::srand(std::time(nullptr));
                int rand;
                bool foundMove = false;
                while(!foundMove){
                    rand = std::rand() % 4;
                    if(possibleMoves[rand] == 1){
                        foundMove = true;
                    }
                }
                switch(rand){
                    case 0:
                        map.moveAnimal(x_coordinate,y_coordinate-1,this);
                        break;
                        
                    case 1:
                        map.moveAnimal(x_coordinate,y_coordinate+1,this);
                        break;
                        
                    case 2:
                        map.moveAnimal(x_coordinate+1,y_coordinate,this);
                        break;
                        
                    default:
                        map.moveAnimal(x_coordinate-1,y_coordinate,this);
                        break;
                        
                }
            }

            
        }

    }
    else{//Omnivore move behavior
        
        Animal* nearbyPrey = map.getNearbyPrey(this);
        
        if(nearbyPredator != nullptr && current_energy_level >= 1){//If there is a predator nearby and the animal has enough energy to move
            int x_diff = x_coordinate - nearbyPredator->getXCoordinate();
            int y_diff = y_coordinate - nearbyPredator->getYCoordinate();

            if(x_diff != 0){//If the predator is to the left or right of the animal
                if(map.canMoveToSpace(x_coordinate+x_diff,y_coordinate, this)){
                    if(map.spaceIsOccupiedByAnimal(x_coordinate+x_diff,y_coordinate)){//If the space the animal wants to move to is occupied by another animal, eat it
                        Animal* preyPtr = map.getAnimal(x_coordinate+x_diff, y_coordinate);
                        Animal& prey = *preyPtr;
                        if(canEat(prey)){
                            Eat(prey, mapPtr);
                        }
                    }
                    if(map.spaceIsOccupiedByPlant(x_coordinate+x_diff,y_coordinate)){
                        Plant* plantPtr = map.getPlant(x_coordinate+x_diff, y_coordinate);
                        Plant& plant = *plantPtr;
                        if(canEat(plant)){
                            Eat(plant, mapPtr);
                        }
                    }
                    map.moveAnimal(x_coordinate+x_diff,y_coordinate,this);
                    //x_coordinate += x_diff;

                }

            }
            else{//If the predator is above or below the animal
                if(map.canMoveToSpace(x_coordinate,y_coordinate+y_diff, this)){
                    if(map.spaceIsOccupiedByAnimal(x_coordinate,y_coordinate+y_diff)){
                        Animal* preyPtr = map.getAnimal(x_coordinate, y_coordinate+y_diff);
                        Animal& prey = *preyPtr;
                        if(canEat(prey)){
                            Eat(prey, mapPtr);
                            }

                    }
                    if(map.spaceIsOccupiedByPlant(x_coordinate,y_coordinate+y_diff)){
                        Plant* plantPtr = map.getPlant(x_coordinate, y_coordinate+y_diff);
                        Plant& plant = *plantPtr;
                        if(canEat(plant)){
                            Eat(plant, mapPtr);
                        }
                        
                    }
                    map.moveAnimal(x_coordinate,y_coordinate+y_diff,this);
                    

                }

            }

        }
        
        else if(nearbyPrey != nullptr){//If there is a prey nearby, eat it
            Animal& prey = *nearbyPrey;
            int x_diff = x_coordinate - nearbyPrey->getXCoordinate();
            int y_diff = y_coordinate - nearbyPrey->getYCoordinate();
            Eat(prey, mapPtr);

            if(x_diff != 0){
                map.moveAnimal(x_coordinate-x_diff,y_coordinate,this);
                //x_coordinate -= x_diff;
                }
            else{
                map.moveAnimal(x_coordinate,y_coordinate - y_diff,this);
                //y_coordinate -= y_diff;
                }
            }
        else if(nearbyEdiblePlant != nullptr){//If there is an edible plant nearby, eat it
            int x_diff = x_coordinate - nearbyEdiblePlant->getXCoordinate();
            int y_diff = y_coordinate - nearbyEdiblePlant->getYCoordinate();
            Plant& plant = *nearbyEdiblePlant;
            Eat(plant, mapPtr);
            if(x_diff != 0){
                map.moveAnimal(x_coordinate-x_diff,y_coordinate,this);
                //x_coordinate -= x_diff;
                }

            else{
                map.moveAnimal(x_coordinate,y_coordinate - y_diff,this);
                //y_coordinate -= y_diff;
                }
            }

        
        else{//If there is no predator, prey, or edible plant nearby, move randomly
            int possibleMoves[4] {0,0,0,0};
            bool possibleMoveExists = false;
            if(map.spaceIsOpen(x_coordinate, y_coordinate-1)){
                possibleMoves[0]= 1;
                possibleMoveExists = true;
                }
            if(map.spaceIsOpen(x_coordinate, y_coordinate+1)){
                possibleMoves[1]= 1;
                possibleMoveExists = true;
                }
            if(map.spaceIsOpen(x_coordinate+1, y_coordinate)){
                possibleMoves[2]= 1;
                possibleMoveExists = true;
                }
            if(map.spaceIsOpen(x_coordinate-1, y_coordinate)){
                possibleMoves[3]= 1;
                possibleMoveExists = true;
                }
            if(possibleMoveExists){
                std::srand(std::time(nullptr));
                int rand;
                bool foundMove = false;
                while(!foundMove){
                    rand = std::rand() % 4;
                    if(possibleMoves[rand] == 1){
                        foundMove = true;
                    }
                }
                switch(rand){
                    case 0:
                        map.moveAnimal(x_coordinate,y_coordinate-1,this);
                        break;
                        
                    case 1:
                        map.moveAnimal(x_coordinate,y_coordinate+1,this);
                        break;
                        
                    case 2:
                        map.moveAnimal(x_coordinate+1,y_coordinate,this);
                        break;
                        
                    default:
                        map.moveAnimal(x_coordinate-1,y_coordinate,this);
                        break;
                        
                }
            }

            
        }
    }
    if(current_energy_level <= 0){
        map.removeAnimal(this);
        //Animal has starved to death
    }
    current_energy_level -= 1; //Decrement energy level after moving
    }
    
    


