#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Coordinates.h"
#include "VacuumCleaner.h"
#include <vector>
#include <stack>


class Algorithm {
private:
    std::vector<char> directions = {'N', 'E', 'S', 'W'};
    bool isReturningToDocking    = false;
    std::stack<char> pathToDocking; // LIFO queue. 

public:
    Algorithm();
    char nextMove(const Coordinates& dockingStation, const Coordinates& currentLocation,
                         int dirtLevel, bool isWallN, bool isWallE, bool isWallS, bool isWallW, 
                         int batteryLevel, bool isCharging);

};

#endif 