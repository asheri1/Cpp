#include "FileParser.h"
#include <fstream>


// construnctor
FileParser::FileParser(const std::string& file_path) { 
    parseFile(file_path);
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

    std::cout << "layout before fillLayoutMissingWalls: " << std::endl;
    printLayout();
    std::cout << "layout after fillLayoutMissingWalls: " << std::endl;
    fillLayoutMissingWalls();
    printLayout();
    std::cout << "\n" << std::endl;
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

// Helper functions for fillLayoutMissingWalls
void FileParser::checkLeftAndRightWalls() {
    for (auto& line : layout) {
        if (!line.empty() && line[0] != '#') {
            line.insert(line.begin(), '#');
        }
        if (!line.empty() && line.back() != '#') {
            line.push_back('#');
        }
    }
}

bool FileParser::rowIsAWall(const std::vector<char>& row) {
    for (char c : row) {
        if (c != '#' && (int)c != 13) {
            return false;
        }
    }
    return true;
}

void FileParser::checkUperWall() {
    if (!layout.empty()) {
        bool isAWall = rowIsAWall(layout[0]);
        int size = 0;
        if(isAWall) {  size = layout[1].size(); }
        else { size = layout[0].size();}
        
        if (size != 0) {
            std::vector<char> newLine(size, '#');
            if(isAWall) {
                layout.erase(layout.begin());
            }
            layout.insert(layout.begin(), newLine);
        }
    }
}

void FileParser::checkLowerWall() { 
    if (!layout.empty()) {
        bool isAWall = rowIsAWall(layout.back());
        if(isAWall) {  
            layout.erase(layout.end()); 
        }
        int size = layout.back().size();
        if (size != 0) {
            std::vector<char> newLine(size, '#');
            layout.push_back(newLine);
        }
    }
}

void FileParser::checkBetweenRowsWall() {
    for (size_t i = 0; i < layout.size() - 1; ++i) {
        if (layout[i + 1].size() > layout[i].size()) {
            int difference = layout[i + 1].size() - layout[i].size();
            layout[i].insert(layout[i].end(), difference, '#');
        } 
        else { //(layout[i + 1].size() < layout[i].size()) {
            int difference = layout[i].size() - layout[i + 1].size();
            layout[i + 1].insert(layout[i + 1].end(), difference, '#');
        }
    }
    for (auto& row : layout) { 
        for (auto& ch : row) { 
            if (ch == ' ') {
                ch = '#'; 
            }
        }
    }
}

void FileParser::cleanLayout() {
    for (auto& row : layout) { 
        for (auto it = row.begin(); it != row.end(); ) { 
            if (*it == ' ') // space char -> turn into clean floor.
            {
                *it = '0';
            }
            
            if (!(std::isdigit(*it) || *it == '#' || *it == '@')) {
                it = row.erase(it); 
            } else {
                ++it; 
            }
        }
    }
}

void FileParser::cleanUnnecessaryWalls() {
    for (size_t i = 0; i < layout.size(); ++i) {
        for (size_t j = 0; j < layout[i].size(); ++j) {
            bool me = (layout[i][j] == '#');
            bool above = (i > 0) && (layout[i - 1][j] == '#');
            bool left = (j > 0) && (layout[i][j - 1] == '#');
            bool diagAbove = (i > 0 && j > 0) && (layout[i - 1][j - 1] == '#');
            bool below = (i < layout.size() - 1) && (layout[i + 1][j] == '#');
            bool diagBelow = (i < layout.size() - 1 && j > 0) && (layout[i + 1][j - 1] == '#');

            if (i == layout.size() - 1) { 
                int m =j + 1;
                bool diagAboveRight = (i > 0 && j > 0) && (m < (int)layout[i].size()) && (layout[i - 1][j + 1] == '#');
                bool restOfTheUpperRowIsWall = true;
                for(int k = j; k < (int)layout[i-1].size(); k++){
                    if(layout[i-1][k] != '#') {
                        restOfTheUpperRowIsWall = false;
                        break;
                    }
                }
                if (me && above && left && diagAbove && diagAboveRight && restOfTheUpperRowIsWall) {
                    layout[i].erase(layout[i].begin() + j, layout[i].end());
                    break;  
                }
            } 
            else {  
                bool restOfTheRowIsWall = true;
                for(int k = j; k < (int)layout[i].size(); k++){
                    if(layout[i][k] != '#') {
                        restOfTheRowIsWall = false;
                        break;
                    }
                }
                if (restOfTheRowIsWall && me && above && left && diagAbove && below && diagBelow) {
                    layout[i].erase(layout[i].begin() + j, layout[i].end());
                    break;
                }
            }
        }
    }
}

void FileParser::fillLayoutMissingWalls() {
    cleanLayout();
    checkUperWall();
    checkLowerWall();
    checkLeftAndRightWalls();
    checkBetweenRowsWall();
    cleanUnnecessaryWalls();
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

void FileParser::printLayout() {
    
    std::vector<std::vector<char>> layout = getLayout();
    for (const auto& line : layout) {
        for (char ch : line) {
            std::cout << ch << " ";
        }
        std::cout << std::endl;
    }
}