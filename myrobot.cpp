#include "myrobot.h"

#include <iostream>
#include <stdexcept>
#include <string>



myrobot::myrobot(const FileParser& parser, House& house, VacuumCleaner& cleaner, Algorithm& algorithm, OutputHandler& outputer)
    : parser(parser),
      house(house),
      cleaner(cleaner),
      algorithm(algorithm),
      outputer(outputer),
      totalTakenSteps(0),
      remainedSteps(parser.getMaxStepsAllowed()),
      remainedDirt(house.getTotalDirt()) {}



void myrobot::run() {

    while (remainedSteps > 0 && cleaner.getBatteryLevel() > 0) {    

        std::string nextAction = algorithm.chooseAction(cleaner);

        if (nextAction == "MOVE"){
            char direction = algorithm.chooseDirection(cleaner);
            cleaner.move(direction);
            outputer.logStep(nextAction);
        }
        else if (nextAction == "CLEAN") {
            cleaner.clean();
            remainedDirt--;
        }
        else if (nextAction == "CHARGE") {
            cleaner.charge();
        }

        totalTakenSteps++;
        remainedSteps--;
    }
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
    } 

    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
