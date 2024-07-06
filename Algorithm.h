#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Coordinates.h"
#include "VacuumCleaner.h"
#include <vector>
#include <stack>
#include <string>


class Algorithm {
private:
    std::vector<char> directions = {'N', 'E', 'S', 'W'};
    std::vector<std::string> actions = {"MOVE", "CLEAN", "CHARGE", "FINISH"};
    bool isCargging = false;
    int moveCounter = 0;
    bool isReturningToDocking    = false;
    std::stack<char> pathToDocking; // LIFO queue.

public:
    Algorithm();
    std::string chooseAction(const VacuumCleaner& cleaner, int remainedDirt);
    char chooseDirection(const VacuumCleaner& cleaner);
    int calcDistanceFromDockingStation();
    void printQueue();
    int getQueueSize();
    void emptyQueue();
};

#endif 