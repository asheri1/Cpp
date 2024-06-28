#include "myrobot.h"

myrobot::myrobot(FileParser& parser, House& house, VacuumCleaner& cleaner, Algorithm& algorithm, OutputHandler& outputer)
    : parser(parser),
      house(house),
      cleaner(cleaner),
      algorithm(algorithm),
      outputer(outputer),
      totalTakenSteps(0),
      remainedSteps(parser.getMaxStepsAllowed()) {}



void myrobot::run() {
    while (remainedSteps > 0 && cleaner.getBatteryLevel() > 0) {
        int dirtLevel = house.getDirtLevel(cleaner.getCurrentLocation());


        char nextAction = algorithm.chooseAction(cleaner);


        totalTakenSteps++;
        remainedSteps--;
        // have to implement the rest.

    }
}