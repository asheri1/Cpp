#ifndef VACUUMCLEANER_H
#define VACUUMCLEANER_H

#include "FileParser.h"
#include "Coordinates.h"
#include "House.h"

class VacuumCleaner
{
private:
    FileParser parser;
    House house;
    Coordinates currentLocation;
    int battery;
    int batteryCapacity;

public:
    // construstor
    VacuumCleaner(const House& house, const FileParser& parser);

    void charge(); 
    void move(char direction);
    void clean();

    // getters
    Coordinates getCurrentLocation() const;
    int getBatteryLevel() const;
    int getBatteryCapacity() const;
    int getMaxStepsAllowed() const;
    bool isAtDocking() const;
    bool isCharged() const;

    bool sensorWallN() const;
    bool sensorWallE() const;
    bool sensorWallS() const;
    bool sensorWallW() const;

    int dirtSensor() const;
};

#endif
