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

    // get roes and cols size
    int rows = layout.size();
    int cols = layout[0].size();
    if (rows == 0 || cols == 0) {
        throw std::runtime_error("Failed - File is empty, there is no House to clean.");
    }

    // check if the top and bottom rows have walls 
    if (static_cast<int>(layout[0].size()) < cols) layout[0].resize(cols, ' ');
    if (static_cast<int>(layout[rows - 1].size()) < cols) layout[rows - 1].resize(cols, ' ');

    for (int i = 0; i < cols; ++i) {
        if (layout[0][i] != '#') layout[0][i] = '#';
        if (layout[rows - 1][i] != '#') layout[rows - 1][i] = '#';
    }

    // check if left and right columns have walls
    for (int i = 0; i < rows; ++i) {
        if (static_cast<int>(layout[i].size()) < cols) layout[i].resize(cols, ' ');
        if (layout[i][0] != '#') layout[i][0] = '#';
        if (layout[i][cols - 1] != '#') layout[i][cols - 1] = '#';
    }

    // check the corners
    if (layout[0][0] != '#') layout[0][0] = '#';
    if (layout[0][cols - 1] != '#') layout[0][cols - 1] = '#';
    if (layout[rows - 1][0] != '#') layout[rows - 1][0] = '#';
    if (layout[rows - 1][cols - 1] != '#') layout[rows - 1][cols-1] ='#';
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
