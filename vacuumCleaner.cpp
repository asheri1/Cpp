#include "VacuumCleaner.h"

VacuumCleaner::VacuumCleaner(const House& house, const FileParser& parser)
  : parser(parser),
    house(house),
    currentLocation(house.getDockingCoordinates()),
    battery(parser.getBatteryCapacity()),
    batteryCapacity(parser.getBatteryCapacity()){}


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
            currentLocation = currentLocation.getCoordinatesN();
            break;

        case 'E':
            currentLocation = currentLocation.getCoordinatesE();
            break;

        case 'S':
            currentLocation = currentLocation.getCoordinatesS();
            break;

        case 'W':
            currentLocation = currentLocation.getCoordinatesW();
            break;
    }

    battery--;
}



void VacuumCleaner::clean() {
    int dirtLevel = house.getDirtLevel(currentLocation);
    if (dirtLevel > 0) {
        house.decreseDirtLevel(currentLocation);
        battery--;
    }
}


Coordinates VacuumCleaner::getCurrentLocation() const {
    return currentLocation;
}

int VacuumCleaner::getBatteryLevel() const {
    return battery;
}

int VacuumCleaner::getBatteryCapacity() const {
    return batteryCapacity;
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