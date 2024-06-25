#ifndef HOUSE_H
#define HOUSE_H

#include "Coordinates.h"
#include "FileParser.h"
#include <vector>
#include <string>

class House
{
private:
    std::vector<std::vector<char>> houseLayout;
    Coordinates dockingStation;
    int batteryCapacity;
    int maxStepsAllowed;

public:
    // constructor
    House(const std::string& file_path);

    bool isWall(const Coordinates& co) const;
    bool isDockingStation(const Coordinates& co) const;
    
    // getters
    Coordinates getDockingCoordinates() const;
    int getDirtLevel(const Coordinates& co) const;
    int getBatteryCapacity() const;
    int getMaxStepsAllowed() const;
};

#endif 