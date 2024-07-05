#include "myrobot.h"

#include <iostream>
#include <stdexcept>
#include <string>

void myrobot::printLocation(Coordinates currentLocation) {
    int x = currentLocation.getX();
    int y = currentLocation.getY();
    std::cout << "currentLocation: layout[" << x << "][" << y << "] = " << house.getLayoutChar(x,y) << "\t";//std::endl;
}


myrobot::myrobot(const FileParser& parser, House& house, VacuumCleaner& cleaner, Algorithm& algorithm, OutputHandler& outputer)
    : parser(parser),
      house(house),
      cleaner(cleaner),
      algorithm(algorithm),
      outputer(outputer),
      totalTakenSteps(0),
      remainedSteps(parser.getMaxStepsAllowed()),
      remainedDirt(house.getTotalDirt()) {}
    

int myrobot::getTotalTakenSteps(){
    return totalTakenSteps;
}

int myrobot::getRemainedSteps(){
    return remainedSteps;
}

int myrobot::getRemainedDirt(){
    return remainedDirt;
}


void myrobot::run() {
    
    while (remainedSteps > 0 && cleaner.getBatteryLevel() > 0) {   
        
        std::string action = algorithm.chooseAction(cleaner, remainedDirt);
        printLocation(cleaner.getCurrentLocation());
        std::cout << "action: " << action;
        
        if (action == "MOVE"){
            char direction = algorithm.chooseDirection(cleaner);
            std::cout << ", direction: " << direction << std::endl;
            outputer.logStep(action, direction, cleaner);
            cleaner.move(direction);
            //outputer.logStep(action, direction);
        }
        else if (action == "CLEAN") {
            cleaner.clean();
            //outputer.logStep(action);
            outputer.logStep(action, 'N', cleaner);
            remainedDirt--;
        }
        else if (action == "CHARGE") {
            std::cout << ", battery Level = " << cleaner.getBatteryLevel();
            cleaner.charge();
            //outputer.logStep(action);
            outputer.logStep(action, 'N', cleaner);
        }
        else if (action == "FINISH") {
            break;
        }

        totalTakenSteps++;
        remainedSteps--;
        
        // Debugging
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
    }
    outputer.lastUpdate(totalTakenSteps, getRemainedDirt());
}




int main(int argc, char* argv[]) {
    // Check if the user has provided the input file path
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " <house_input_file>" << std::endl;
        return 1;
    }

    try {
        FileParser parser(argv[1]);             // parse the input file
        House house(parser);                    // create the house object
        VacuumCleaner cleaner(parser, house);   // create the vacuum cleaner object
        Algorithm algorithm;                    // create the algorithm object
        OutputHandler outputer;                 // create the output handler object

        // create myrobot object
        myrobot robot(parser, house, cleaner, algorithm, outputer);  
        
        // Run the vacuum cleaner simulation
        robot.run();

        // create output File
        outputer.setVacuumStatus((cleaner.getBatteryLevel() <= 0), (house.getTotalDirt() == 0));
        outputer.writeOutput();
    } 

    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }



    return 0;
}

// for Debugging
House myrobot::getHouse(){
    return house; 
}

void myrobot::printLayout(House house){
    return house.printLayout();
}