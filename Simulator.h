#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "FileParser.h"
#include "House.h"
#include "Algorithm.h"
#include "VacuumCleaner.h"
#include "OutputHandler.h"


class Simulator {

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
    void printLocation(Coordinates currentLocation);
    Simulator(const FileParser& parser, House& house, VacuumCleaner& vacuum, Algorithm& algorithm, OutputHandler& outputer);
    void run();
    int getTotalTakenSteps();
    int getRemainedSteps();
    int getRemainedDirt();
    House getHouse();
    void printLayout(House house);
};

#endif