#include "House.h"


House::House(const FileParser& parser) 
    : parser(parser),
      houseLayout(parser.getLayout()),
      dockingStation(parser.getDockingCoordinates()),
      totalDirt(0)
      {calculateTotalDirt();}

void House::calculateTotalDirt(){
    for (const auto& row : houseLayout) {
        for (const auto& cellDirt : row) {
            if (cellDirt >= '1' && cellDirt <= '9') {
                totalDirt += cellDirt - '0';
            }
        }
    }
}

bool House::isWall(const Coordinates& co) const {
    return houseLayout[co.getY()][co.getX()] == '#';
}

bool House::isDockingStation(const Coordinates& co) const {
    return co == dockingStation;
}

Coordinates House::getDockingCoordinates() const {
    return dockingStation;
}

int House::getDirtLevel(const Coordinates& co) const {
    if (isWall(co) || isDockingStation(co)) {
       return 0; // edge case
    }
    return houseLayout[co.getY()][co.getX()] -'0';
}

void House::decreseDirtLevel(const Coordinates& co, int cleanFactor){
    int dirtLevel = getDirtLevel(co);
    if (dirtLevel >= 1 && dirtLevel <= 9) {
        int newDirtLevel = std::max(0, dirtLevel - cleanFactor);
        houseLayout[co.getY()][co.getX()] = '0' + newDirtLevel; // assigining char(newDirtLevel)

    int cleanedDirt = dirtLevel - newDirtLevel;
    totalDirt -= cleanedDirt;
    }
}

int House::getTotalDirt() const{
    return totalDirt;
}

void House::printLayout() {
    for (const auto& line : houseLayout) {
        for (char ch : line) {
            std::cout << ch << " ";
        }
        std::cout << std::endl;
    }
}

char House::getLayoutChar(int x, int y) {
    return houseLayout[y][x];
}