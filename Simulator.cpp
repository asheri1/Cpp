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
        //printLocation(cleaner.getCurrentLocation());
        //std::cout << "action: " << action;
        
        if (action == "MOVE"){
            char direction = algorithm.chooseDirection(cleaner);
            //std::cout << ", direction: " << direction << std::endl;
            outputer.logStep(action, direction, cleaner);
            cleaner.move(direction);
        }
        else if (action == "CLEAN") {
            cleaner.clean();
            outputer.logStep(action, 'N', cleaner);
            remainedDirt--;
        }
        else if (action == "CHARGE") {
            //std::cout << ", battery Level = " << cleaner.getBatteryLevel();
            cleaner.charge();
            outputer.logStep(action, 'N', cleaner);
        }
        else if (action == "FINISH") {
            break;
        }

        totalTakenSteps++;
        remainedSteps--;
        
        /*/ Debugging
        if(action != "MOVE"){ std::cout << std::endl;}
        if(action == "MOVE"){
            house.printLayout();
            printLocation(cleaner.getCurrentLocation());
            std::cout << std::endl;
            algorithm.printQueue();
            std::cout << "total Taken Steps = " << totalTakenSteps << std::endl;
            std::cout << "remained Steps = " << remainedSteps  << std::endl;
            std::cout << "battery Level = " << cleaner.getBatteryLevel() << std::endl;
            std::cout << "remained Dirt; = " << getRemainedDirt() << std::endl;
            std::cout << "distance from docking station = " << algorithm.calcDistanceFromDockingStation() << "\n" << std::endl;
        }
        */      
    }
    outputer.lastUpdate(totalTakenSteps, getRemainedDirt());
}



// for Debugging
House Simulator::getHouse(){
    return house; 
}

void Simulator::printLayout(House house){
    return house.printLayout();
}