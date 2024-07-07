#ifndef FILEPARSER_H
#define FILEPARSER_H

#include "Coordinates.h"
#include <vector>
#include <string>
#include <iostream>


class FileParser
{
private:
    std::vector<std::vector<char>> layout;
    Coordinates dockingStation;
    int batteryCapacity;
    int maxStepsAllowed;
    void parseFile(const std::string& file_path);
    void checkLeftAndRightWalls();
    bool rowIsAWall(const std::vector<char>& row);
    void checkUperWall();
    void checkLowerWall();
    void checkBetweenRowsWall();
    void cleanLayout();
    void cleanUnnecessaryWalls();
    void fillLayoutMissingWalls();
    void lineFixer(std::vector<char>& line);

public:
    
    // constructor
    FileParser(const std::string& file_path);
    
    // getters 
    std::vector<std::vector<char>> getLayout() const; 
    Coordinates getDockingCoordinates() const;
    int getBatteryCapacity() const;
    int getMaxStepsAllowed() const;

    void printLayout();

};


#endif 