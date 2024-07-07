#include "Simulator.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;


void Simulator::printLocation(Coordinates currentLocation) {
    int x = currentLocation.getX();
    int y = currentLocation.getY();
    std::cout << "currentLocation: layout[" << x << "][" << y << "] = " << house.getLayoutChar(x,y) << "\t";//std::endl;
}

Simulator::Simulator(const FileParser& parser, House& house, VacuumCleaner& cleaner, Algorithm& algorithm, OutputHandler& outputer)
    : parser(parser),
      house(house),
      cleaner(cleaner),
      algorithm(algorithm),
      outputer(outputer),
      totalTakenSteps(0),
      remainedSteps(parser.getMaxStepsAllowed()),
      remainedDirt(house.getTotalDirt()) {}
    
int Simulator::getTotalTakenSteps(){
    return totalTakenSteps;
}

int Simulator::getRemainedSteps(){
    return remainedSteps;
}

int Simulator::getRemainedDirt(){
    return remainedDirt;
}

void Simulator::run() {
    
    while (remainedSteps > 0 && cleaner.getBatteryLevel() > 0) {   
        
        std::string action = algorithm.chooseAction(cleaner, remainedDirt);
        
        if (action == "MOVE"){
            char direction = algorithm.chooseDirection(cleaner);
            outputer.logStep(action, direction, cleaner);
            cleaner.move(direction);
        }
        else if (action == "CLEAN") {
            cleaner.clean();
            outputer.logStep(action, 'N', cleaner);
            remainedDirt--;
        }
        else if (action == "CHARGE") {
            cleaner.charge();
            outputer.logStep(action, 'N', cleaner);
        }
        else if (action == "FINISH") {
            break;
        }

        totalTakenSteps++;
        remainedSteps--;      
    }
    outputer.lastUpdate(totalTakenSteps, getRemainedDirt());

    std::cout << "The house Layout after the cleaning of the robot is finished: " << std::endl;
    printLayout(house);
    std::cout << "\n" << std::endl;
}

void Simulator::printLayout(House house){
    return house.printLayout();
}

// for Debugging
House Simulator::getHouse(){
    return house; 
}
