#include "House.h"


House::House(const FileParser& parser) 
    : parser(parser),
      houseLayout(parser.getLayout()),
      dockingStation(parser.getDockingCoordinates()),
      batteryCapacity(parser.getBatteryCapacity()),
      maxStepsAllowed(parser.getMaxStepsAllowed()),
      totalDirt(0) {
    
    calculateTotalDirt();
    fillLayoutMissingWalls();

}

void House::fillLayoutMissingWalls(){
   /////////////////////////////// to implement ///////////////////////////////////
}

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
    if (isWall(co) || isDockingStation(co))
    {
       return 0; // edge case
    }
    return houseLayout[co.getY()][co.getX()] -'0';
}

int House::decreseDirtLevel(const Coordinates& co, int cleanFactor=1){
       /////////////////////////////// to implement ///////////////////////////////////
}
