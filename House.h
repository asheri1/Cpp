#ifndef HOUSE_H
#define HOUSE_H

#include "Coordinates.h"
#include "FileParser.h"
#include <vector>
#include <string>

class House
{
private:

    FileParser parser;
    std::vector<std::vector<char>> houseLayout;
    void calculateTotalDirt();

    Coordinates dockingStation;
    int batteryCapacity;
    int maxStepsAllowed;
    int totalDirt;

public:
    // constructor
    House(const FileParser& parser);

    bool isWall(const Coordinates& co) const;
    bool isDockingStation(const Coordinates& co) const;
    
    // getters
    Coordinates getDockingCoordinates() const;
    int getDirtLevel(const Coordinates& co) const;
    int getTotalDirt() const;

    // setters
    void decreseDirtLevel(const Coordinates& co, int cleanFactor=1);
};

#endif 