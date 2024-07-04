#include "Algorithm.h"
#include <time.h>


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

//std::vector<std::string> actions = {"MOVE", "CLEAN", "CHARGE"};
std::string Algorithm::chooseAction(const VacuumCleaner& cleaner) {
    
    int distance_from_docking_station = calcDistanceFromDockingStation();

    if(cleaner.isAtDocking()){
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
        if(cleaner.getBatteryLevel() > distance_from_docking_station + 5){
            return actions[0]; // MOVE
        }
        // There is very little battery left so charge now
        else {
            isCargging = true;
            return actions[2]; // CHARGE
        }
    }

    // if the distance from the charging station is equal to the remaining battery + 2 steps - charge
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
        // cleaner.dirtSensor() == 0
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
        //return 'D'; 
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
    srand(static_cast<unsigned int>(time(0)));
    int randomIndex = rand() % possibleDirections.size();
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

