#ifndef RUNNER_H
#define RUNNER_H

#include "FileParser.h"
#include "House.h"
#include "Algorithm.h"
#include "VacuumCleaner.h"
#include "OutputHandler.h"


class Runner {

private:
    FileParser& parser;
    House& house;
    VacuumCleaner& vacuum;
    Algorithm& algorithm;
    OutputHandler& outputer;
    
    int totalTakenSteps;
    int remainedSteps;

public:
    Runner(const House& house, VacuumCleaner& vacuum, Algorithm& algorithm);
    void run();

};

#endif