#include "VacuumCleaner.h"

VacuumCleaner::VacuumCleaner(const House& house, const FileParser& parser)
  : parser(parser),
    house(house),
    currentLocation(house.getDockingCoordinates()),
    battery(parser.getBatteryCapacity()),
    batteryCapacity(parser.getBatteryCapacity()){}


void VacuumCleaner::charge(){
    if (!isCharged) battery++;
    return;
}

void VacuumCleaner::charge() {
    if (isAtDocking() && battery < batteryCapacity) {
        battery += batteryCapacity / 20;

        // edge case
        if (battery > batteryCapacity) {
            battery = batteryCapacity;
        }
    }
}

void VacuumCleaner::move(char direction) {
    if (battery <= 0) { return;}

    switch (direction) {
        case 'N':
            if (!sensorWallN()) {currentLocation = currentLocation.getCoordinatesN();}
            break;

        case 'E':
            if (!sensorWallE()) {currentLocation = currentLocation.getCoordinatesE();}
            break;

        case 'S':
            if (!sensorWallS()) {currentLocation = currentLocation.getCoordinatesS();}
            break;

        case 'W':
            if (!sensorWallW()) {currentLocation = currentLocation.getCoordinatesW();}
            break;
    }

    battery--;
}


void VacuumCleaner::stay() {
    // Do nothing, just consume battery
    if (battery > 0) {
        battery--;
    }
}

void VacuumCleaner::clean() {
    int dirtLevel = house.getDirtLevel(currentLocation);
    if (dirtLevel > 0) {
        house.decreseDirtLevel(currentLocation);
        battery--;
    }
}

int VacuumCleaner::getBatteryLevel() const {
    return battery;
}

int VacuumCleaner::getBatteryCapacity() const {
    return batteryCapacity;
}

int VacuumCleaner::getMaxStepsAllowed() const {
    return parser.getMaxStepsAllowed();
}

bool VacuumCleaner::isAtDocking() const {
    return currentLocation == house.getDockingCoordinates();
}

bool VacuumCleaner::sensorWallN() const {
    return house.isWall(currentLocation.getCoordinatesN());
}

bool VacuumCleaner::sensorWallE() const {
    return house.isWall(currentLocation.getCoordinatesE());
}

bool VacuumCleaner::sensorWallS() const {
    return house.isWall(currentLocation.getCoordinatesS());
}

bool VacuumCleaner::sensorWallW() const {
    return house.isWall(currentLocation.getCoordinatesW());
}

int VacuumCleaner::dirtSensor() const {
    return house.getDirtLevel(currentLocation);
}