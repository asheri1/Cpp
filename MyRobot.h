#ifndef MYROBOT_H
#define MYROBOT_H

#include "FileParser.h"
#include "House.h"
#include "Algorithm.h"
#include "VacuumCleaner.h"
#include "OutputHandler.h"


class myrobot {

private:
    const FileParser& parser;
    House& house;
    VacuumCleaner& cleaner;
    Algorithm& algorithm;
    OutputHandler& outputer;
    
    int totalTakenSteps;
    int remainedSteps;
    int remainedDirt;

public:
    myrobot(const FileParser& parser, House& house, VacuumCleaner& vacuum, Algorithm& algorithm, OutputHandler& outputer);
    void run();

};

#endif