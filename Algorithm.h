#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Coordinates.h"
#include "VacuumCleaner.h"
#include <vector>
#include <stack>

// hey
class Algorithm {
private:
    std::vector<char> directions = {'N', 'E', 'S', 'W'};
    std::vector<std::string> actions = {"MOVE", "CLEAN", "CHARGE"};
    int moveCounter = 0;
    bool isReturningToDocking    = false;
    std::stack<char> pathToDocking; // LIFO queue.

public:
    Algorithm();
    int chooseAction(const VacuumCleaner& cleaner);
    char chooseDirection(const VacuumCleaner& cleaner);
};

#endif 