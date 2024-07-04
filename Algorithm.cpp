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
    

    isReturningToDocking = false;
    int distance_from_docking_station = calcDistanceFromDockingStation();

    // The distance from the charging station is equal to the remaining battery
    if(cleaner.getBatteryLevel() == distance_from_docking_station+2) {
        isReturningToDocking = true;
        return actions[0]; // MOVE    
    }
    else if(cleaner.isAtDocking()){

        if(cleaner.isAtChargingState() || cleaner.getBatteryLevel() == 1){
            return actions[2]; // CHARGE
        }
        // Finish charging
        if(cleaner.isCharged()){
            return actions[0]; // MOVE
        }
        // There is still some battery left, so you don't have to charge it
        else if(cleaner.getBatteryLevel() > distance_from_docking_station+5){
            return actions[0]; // MOVE
        }
        // There is very little battery left so charge now
        else {
            return actions[2]; // CHARGE
        } 
    }
    //(cleaner.getBatteryLevel() > moveCounter)
    else { 
        if(cleaner.getBatteryLevel() == distance_from_docking_station+1) {
            isReturningToDocking = true;
            return actions[0]; // MOVE    
        }
        // still dirty - keep cleaning
        else if(cleaner.dirtSensor() > 0) {
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
        
        else{
            isReturningToDocking = false;
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

/*/
int calcMinDisToDocking(std::stack<char>& pathToDocking, std::vector<std::vector<char>>& layout, int x1, int y1, int x2, int y2) {
    // Directions for moving in the grid
    std::vector<std::tuple<int, int, char>> directions = {
        {0, -1, 'N'},  // North
        {0, 1, 'S'},   // South
        {-1, 0, 'W'},  // West
        {1, 0, 'E'}    // East
    };

    int rows = layout.size();
    int cols = layout[0].size();

    // Check if start or end positions are invalid
    if (x1 < 0 || x1 >= rows || y1 < 0 || y1 >= cols || x2 < 0 || x2 >= rows || y2 < 0 || y2 >= cols || layout[x1][y1] == '#' || layout[x2][y2] == '#') {
        return -1;
    }

    // BFS setup
    std::queue<std::tuple<int, int, int, std::stack<char>>> q;
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

    // Initial position
    q.push({x1, y1, 0, std::stack<char>()});
    visited[x1][y1] = true;

    while (!q.empty()) {
        auto [curX, curY, dist, path] = q.front();
        q.pop();

        // Check if we reached the destination
        if (curX == x2 && curY == y2) {
            pathToDocking = path;
            return dist;
        }

        // Explore neighbors
        for (const auto& [dx, dy, dir] : directions) {
            int newX = curX + dx;
            int newY = curY + dy;

            // Check boundaries and if the cell is already visited or is a wall
            if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && !visited[newX][newY] && layout[newX][newY] != '#') {
                visited[newX][newY] = true;
                std::stack<char> newPath = path;
                newPath.push(dir);
                q.push({newX, newY, dist + 1, newPath});
            }
        }
    }

    // If we reach here, there is no path to the destination
    return -1;
}
*/