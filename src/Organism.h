#ifndef ORGANISM_H
#define ORGANISM_H

class Organism {
public:
    char id {};
    int x_coordinate {};
    int y_coordinate {};

    // Constructor
    Organism(char id, int x_coordinate, int y_coordinate) : id(id), x_coordinate(x_coordinate), y_coordinate(y_coordinate) {}

    // Methods to get x and y coordinates
    int getXCoordinate() const;
    int getYCoordinate() const;
};

#endif
