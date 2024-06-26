#ifndef RUNNER_H
#define RUNNER_H

#include "FileParser.h"
#include "House.h"
#include "Algorithm.h"
#include "VacuumCleaner.h"
#include "OutputGenerator.h"


class Runner {

private:
    FileParser& parser;
    House& house;
    VacuumCleaner& vacuum;
    Algorithm& algorithm;
    OutputGenerator& outputer;
    
    int totalTakenSteps;
    int remainedSteps;

public:
    Runner(const House& house, VacuumCleaner& vacuum, Algorithm& algorithm);
    void run();

};

#endif