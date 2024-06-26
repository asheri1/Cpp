#ifndef VACUUMCLEANER_H
#define VACUUMCLEANER_H

#include "FileParser.h"
#include "Coordinates.h"
#include "House.h"

class VacuumCleaner
{
private:
    House house;
    Coordinates currentLocation;
    int battery;
    int remainedSteps;
    int totalTakenSteps;
    int batteryCapacity;

public:
    // construstor
    VacuumCleaner(const House& house);

    void charge(); 
    void move();
    void stay();
    void clean();

    // getters
    int getBatteryLevel() const;
    int getBatteryCapacity() const;
    int getMaxStepsAllowed() const;
    bool isAtDocking() const;

    bool sensorWallN() const;
    bool sensorWallE() const;
    bool sensorWallS() const;
    bool sensorWallW() const;

    int dirtSensor() const;
};

#endif
