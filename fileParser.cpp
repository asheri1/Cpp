#include "FileParser.h"
#include <fstream>

// construnctor
FileParser::FileParser(const std::string& file_path) { 
    parseFile(file_path);
    fillLayoutMissingWalls();
}

void FileParser::parseFile(const std::string& file_path) {
    std::ifstream file(file_path);
    if (!file) {
        throw std::runtime_error("Failed to open the input file.");
    }

    std::string line;

    std::getline(file, line); 
    batteryCapacity = std::stoi(line); // read the first line - for battery capacity.

    std::getline(file, line);
    maxStepsAllowed = std::stoi(line); // read the second line - for max steps allowed.

    while (std::getline(file ,line)){
        std::vector<char> row = std::vector<char>(line.begin(), line.end());
        layout.push_back(row);
    }
    

    // find the docking station coordinates by '@' character in the houseLayout.
    bool found_docking = false;

    for (int y = 0; y <  static_cast<int>(layout.size()); ++y) {
        for (int x = 0; x <  static_cast<int>(layout[y].size()); ++x) {
            if (layout[y][x] == '@') {
                dockingStation = Coordinates(x, y);
                found_docking = true;
                break;
            }
        }
    }

    if (!found_docking)
    {
        throw std::runtime_error("Docking station not found in house layout.");
    }

}

void FileParser::fillLayoutMissingWalls(){
   /////////////////////////////// to implement ///////////////////////////////////
}


// getters implementations.
std::vector<std::vector<char>> FileParser::getLayout() const{
    return layout;
}

Coordinates FileParser::getDockingCoordinates() const{
    return dockingStation;
}

int FileParser::getBatteryCapacity() const{
    return batteryCapacity;
}

int FileParser::getMaxStepsAllowed() const{
    return maxStepsAllowed;
}
