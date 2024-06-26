#include "House.h"

House::House(const std::string& file_path){
    FileParser parser(file_path); 
    houseLayout     = parser.getHouseLayout();
    dockingStation  = parser.getDockingCoordinates();
    batteryCapacity = parser.getBatteryCapacity();
    maxStepsAllowed = parser.getMaxStepsAllowed();
    fillLayoutMissingWalls();
}

void House::fillLayoutMissingWalls(){
   /////////////////////////////// to implement ///////////////////////////////////
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

int House::setDirtLevel(const Coordinates& co){}
