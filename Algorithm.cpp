#include "Algorithm.h"
#include <time.h>
#include <random>


// Default constructor
Algorithm::Algorithm() {}

int Algorithm::calcDistanceFromDockingStation(){
    
    // Move elements from stack to temporary vector
    std::vector<char> temp;
    while (!pathToDocking.empty()) {
        temp.push_back(pathToDocking.top());
        pathToDocking.pop();
    }

    // Process the temporary vector to remove specified pairs
    std::vector<char> result;
    for (size_t i = 0; i < temp.size(); ++i) {
        if (i + 1 < temp.size() &&
            ((temp[i] == 'N' && temp[i + 1] == 'S') ||
             (temp[i] == 'S' && temp[i + 1] == 'N') ||
             (temp[i] == 'E' && temp[i + 1] == 'W') ||
             (temp[i] == 'W' && temp[i + 1] == 'E'))) {
            ++i; // Skip the next element
        } 
        else {
            result.push_back(temp[i]);
        }
    }

    // Move elements back to the stack
    for (auto it = result.rbegin(); it != result.rend(); ++it) {
        pathToDocking.push(*it);
    }
    
    return pathToDocking.size();
}

//std::vector<std::string> actions = {"MOVE", "CLEAN", "CHARGE", "FINISH"};
std::string Algorithm::chooseAction(const VacuumCleaner& cleaner, int remainedDirt) {
    
    // the house is clean
    if(remainedDirt == 0) {
        isReturningToDocking = true;
        if(cleaner.isAtDocking()){
            return actions[3]; // FINISH
        }
        return actions[0]; // MOVE
    }

    int distance_from_docking_station = calcDistanceFromDockingStation();
    
    if(cleaner.isAtDocking()){
        // if get to the docking station (even accidentally), reset the route back
        emptyQueue();

        // if the robot finish charging
        if(cleaner.isCharged()) {
            isCargging = false;
            isReturningToDocking = false;
            return actions[0]; // MOVE
        }
        // if the robot is charging or has returned to docking station to charge
        if(isCargging || cleaner.getBatteryLevel() == 1) {
            isCargging = true;
            return actions[2]; // CHARGE
        }
        // There is still some battery left, so you don't have to charge it
        if(cleaner.getBatteryLevel() > distance_from_docking_station + 2){
            return actions[0]; // MOVE
        }
        // There is very little battery left so charge now
        else {
            isCargging = true;
            return actions[2]; // CHARGE
        }
    }

    // if the distance from the charging station is equal to the remaining battery + 1 or 2 steps - go charge
    else if((cleaner.getBatteryLevel() == distance_from_docking_station + 2) || 
            (cleaner.getBatteryLevel() == distance_from_docking_station + 1)) {
        isReturningToDocking = true;
        return actions[0]; // MOVE    
    }
    // no need to charge right now
    else { 
        // still dirty - keep cleaning
        if(cleaner.dirtSensor() > 0) {
            return actions[1]; // CLEAN
        }
        // this spot is clean - move
        else { 
            return actions[0]; // MOVE      
        }
    }
}


//std::vector<char> directions = {'N', 'E', 'S', 'W'};
char Algorithm::chooseDirection(const VacuumCleaner& cleaner) {

    if(isReturningToDocking){ 
        if(!pathToDocking.empty()){
            char dirction = pathToDocking.top();
            pathToDocking.pop(); 
            return dirction;
        } 
    }
    
    std::vector<char> possibleDirections;
    if (!cleaner.sensorWallN()) {  possibleDirections.push_back('N'); }
    if (!cleaner.sensorWallS()) {  possibleDirections.push_back('S'); }
    if (!cleaner.sensorWallE()) {  possibleDirections.push_back('E'); }
    if (!cleaner.sensorWallW()) {  possibleDirections.push_back('W'); }

    // No possible directions
    if (possibleDirections.empty()) {
        throw std::runtime_error("The robot is stuck and cannot move in any direction\n"); 
    }

    // Choose a random direction from the possible directions
    std::random_device rd; // get a random number from the hardware
    std::mt19937 gen(rd()); // seed a generator
    std::uniform_int_distribution<> distr(0, possibleDirections.size() - 1); //define the range

    int randomIndex = distr(gen);
    char direction = possibleDirections[randomIndex];

    // Enter the opposite direction to the direction of progress to know how to return
    switch (direction) {
        case 'N':
            pathToDocking.push('S');
            break;
        case 'S':
            pathToDocking.push('N');
            break;
        case 'W':
            pathToDocking.push('E');
            break;
        case 'E':
            pathToDocking.push('W');
            break;
    }    
    return direction;
}

void Algorithm::emptyQueue(){
    while (!pathToDocking.empty()) {
        pathToDocking.pop();
    }
}

void Algorithm::printQueue() {
    std::stack<char> temp = pathToDocking;  // Make a copy of the stack to preserve the original
    std::vector<char> elements;

    // Transfer elements from the stack to a vector to print in the correct order
    while (!temp.empty()) {
        elements.push_back(temp.top());
        temp.pop();
    }

    // Print elements in reverse order to maintain stack order
    std::cout << "Queue: ";
    for (auto it = elements.rbegin(); it != elements.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int Algorithm::getQueueSize(){
    return pathToDocking.size();
}

