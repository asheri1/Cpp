#ifndef MYROBOT_H
#define MYROBOT_H

#include "FileParser.h"
#include "House.h"
#include "Algorithm.h"
#include "VacuumCleaner.h"
#include "OutputHandler.h"


class myrobot {

private:
    FileParser parser;
    House house;
    VacuumCleaner cleaner;
    Algorithm algorithm;
    OutputHandler outputer;
    
    int totalTakenSteps;
    int remainedSteps;

public:
    myrobot(FileParser& parser, House& house, VacuumCleaner& vacuum, Algorithm& algorithm, OutputHandler& outputer);
    void run();

};

#endif