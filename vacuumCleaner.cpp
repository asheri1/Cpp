#include "VacuumCleaner.h"

VacuumCleaner::VacuumCleaner(const FileParser& parser, House& house)
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

bool VacuumCleaner::isCharged() const{
    return battery == batteryCapacity;
}

bool VacuumCleaner::sensorWallN() const {
    Coordinates coordinates = currentLocation.getCoordinatesN();
    return house.isWall(coordinates);
}

bool VacuumCleaner::sensorWallE() const {
    Coordinates coordinates = currentLocation.getCoordinatesE();
    return house.isWall(coordinates);
}

bool VacuumCleaner::sensorWallS() const {
    Coordinates coordinates = currentLocation.getCoordinatesS();
    return house.isWall(coordinates);
}

bool VacuumCleaner::sensorWallW() const {
    Coordinates coordinates = currentLocation.getCoordinatesW();
    return house.isWall(coordinates);
}

int VacuumCleaner::dirtSensor() const {
    return house.getDirtLevel(currentLocation);
}
