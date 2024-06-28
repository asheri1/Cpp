#ifndef FILEPARSER_H
#define FILEPARSER_H

#include "Coordinates.h"
#include <vector>
#include <string>


class FileParser
{
private:
    std::vector<std::vector<char>> layout;
    Coordinates dockingStation;
    int batteryCapacity;
    int maxStepsAllowed;
    void parseFile(const std::string& file_path);
    void fillLayoutMissingWalls();

public:
    
    // constructor
    FileParser(const std::string& file_path);
    
    // getters 
    std::vector<std::vector<char>> getLayout() const; 
    Coordinates getDockingCoordinates() const;
    int getBatteryCapacity() const;
    int getMaxStepsAllowed() const;
};


#endif 