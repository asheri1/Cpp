#include "OutputHandler.h"
#include <fstream>
#include <iostream>


///####### constructors #######//

// default constructor
OutputHandler::OutputHandler() 
    : outputFilePath("output.txt"),
      totalSteps(0),
      remainedDirt(0),
      isVacuumDead(false),
      missionSucceeded(false) {}


// constructor with file path
OutputHandler::OutputHandler(const std::string& filePath) 
    : outputFilePath(filePath),
      totalSteps(0),
      remainedDirt(0), 
      isVacuumDead(false), 
      missionSucceeded(false) {}

///##########################///



// logging a step.
void OutputHandler::logStep(const std::string& action) {
    stepsLog.push_back(action);
}

void OutputHandler::logStep(const std::string& action, char direction){
    stepsLog.push_back(action + " " + direction);
}


// setters.
void OutputHandler::setRemainedDirt(int dirt) {
    remainedDirt = dirt;
}

void OutputHandler::setVacuumStatus(bool isDead, bool isMissionSucceeded) {
    isVacuumDead = isDead;
    missionSucceeded = isMissionSucceeded;
}

// write the output to file
void OutputHandler::writeOutput() const {
    std::ofstream outFile(outputFilePath);
    if (!outFile) {
        std::cerr << "Error opening output file." << std::endl;
        return;
    }

    for (const auto& step : stepsLog) {
        outFile << step << std::endl;
    }

    outFile << "Total Steps: " << totalSteps << std::endl;
    outFile << "Remaining Dirt: " << remainedDirt << std::endl;
    outFile << "Vacuum is Dead: " << (isVacuumDead ? "Yes" : "No") << std::endl;
    outFile << "Mission Succeeded: " << (missionSucceeded ? "Yes" : "No") << std::endl;

    outFile.close();
}
