#include <iostream>
#include "Map.h"


void Plant::resetGrowth(){//reset growth to 0
    isFullyGrown = false;
    current_growth = 0;
}
void Plant::grow(Map* mapPtr){//grow the plant
    Map& map = *mapPtr;
    if(!isFullyGrown){//
        if(current_growth != regrowth_coeff){
            current_growth += 1;
        }
        
        if(!map.spaceIsOccupiedByAnimal(x_coordinate,y_coordinate)){//if the space is not occupied by an animal, grow the plant fully
            isFullyGrown = true;
        }
        
    }
}