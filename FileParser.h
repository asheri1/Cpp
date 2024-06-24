#ifndef FILEPARSER_H
#define FILEPARSER_H

#include "Coordinates.h"
#include <vector>
#include <string>


class FileParser
{
private:
    std::vector<std::vector<char>> house_layout;
    Coordinates dockingStation;
    int batteryCapacity;
    int maxStepsAllowed;
    void parseFile(const std::string& file_path);

public:
    FileParser(const std::string& file_path);
    std::vector<std::vector<char>>& getHouseLayout() const; 
    Coordinates getDockingCoordinates() const;
    int getBatteryCapacity() const;
    int getMaxStepsAllowed() const;
};


#endif 