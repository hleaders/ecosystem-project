#include <iostream>
#include <fstream>
#include <map>
#include <tuple>
#include "Map.h"
#include <sstream>
int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <map_file> <species_file>\n";
        return 1;
    }
    std::string mapFilePath = argv[1];
    std::string speciesFilePath = argv[2];

    // Define the size of the map
    std::ifstream mapSizeFile(mapFilePath);
    std::string line;
    int height = 0;
    int width = 0;
    while (std::getline(mapSizeFile, line)) {
        ++height;
        if (line.length() > width) {
            width = line.length();
        }
    }
    mapSizeFile.close();

    // Create a map object
    Map map(width, height);

    // Create a 2D vector for the area map
    std::vector<std::vector<char>> areaMap(height, std::vector<char>(width, ' '));

    // Read the map file again to populate the area map
    std::ifstream mapFile(mapFilePath);
    int i = 0;
    while (std::getline(mapFile, line)) {
        for (int j = 0; j < width; ++j) {
            if (j < line.size()) {
                areaMap[i][j] = line[j];
            } else {
                areaMap[i][j] = ' ';
            }
        }
        ++i;
    }
    mapFile.close();
    // Read the species data from species.txt
    std::ifstream speciesFile(speciesFilePath);
    std::map<char, std::tuple<std::string, int, int>> speciesData;
    std::string type;
    char id;
    int initValue1, initValue2;
    

    
    while (std::getline(speciesFile, line)) {
        std::istringstream iss(line);
        iss >> type >> id;
        if (type == "plant") {
            iss >> initValue1 >> initValue2;
            speciesData[id] = std::make_tuple(type, initValue1, initValue2);
        } else { // herbivore or omnivore
            iss >> initValue1;
            speciesData[id] = std::make_tuple(type, initValue1, 0);
        }
    }
    speciesFile.close();
    // Populate the map with organisms based on the area map
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            char organismId = areaMap[i][j];
            if (organismId != ' ') {
                // Check if the organism is a plant or animal
                if (std::get<0>(speciesData[organismId]) == "plant") {
                    // Create and add plant
                    int regrowthCoeff = std::get<1>(speciesData[organismId]);
                    int energyPoints = std::get<2>(speciesData[organismId]);
                    Plant* plant = new Plant(organismId, j, i, regrowthCoeff, energyPoints);
                    map.plantBoard[j][i] = plant;
                } else {
                    // Create and add animal
                    bool isOmnivore = std::get<0>(speciesData[organismId]) == "omnivore";
                    int energyLevel = std::get<1>(speciesData[organismId]);
                    Animal* animal = new Animal(organismId, j, i, energyLevel, isOmnivore);
                    map.animalBoard[j][i] = animal;
                }
            }
        }
    }

    // Print the initial state of the map
    int numIterations;
    std::cout << "\nEnter the number of iterations: ";
    std::cin >> numIterations;

    for (int i = 0; i < numIterations; ++i) {
        std::cout << "\nIteration " << i + 1 << ":\n\n";
        map.printMap();
        map.performLivingFunctions();
    }

    while (true) {
        char continueSimulation;
        std::cout << "Press 'c' to continue the simulation or any other key to exit: ";
        std::cin >> continueSimulation;

        if (continueSimulation == 'c' || continueSimulation == 'C') {
            std::cout << "Enter the number of additional iterations: ";
            std::cin >> numIterations;

            for (int i = 0; i < numIterations; ++i) {
                std::cout << "\nIteration " << i + 1 << ":\n\n";
                map.printMap();
                map.performLivingFunctions();
            }
        } else {
            break;
        }
    }
    return 0;
}