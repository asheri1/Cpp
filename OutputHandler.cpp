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


void OutputHandler::logStep(const std::string& action, char direction, VacuumCleaner& cleaner){
    
    if(action == "MOVE"){
        Coordinates cor = cleaner.getCurrentLocation();
        std::string location = "Latout[" + std::to_string(cor.getX()) + "][" + std::to_string(cor.getY()) + "]";
        logMoveStep(action, direction, location);
    }
    else if(action == "CLEAN"){
        int totalDirt = cleaner.dirtSensor();
        logCleanStep(action, totalDirt);
    }
    else{ // (action == "CHARGE")
        int batteryLevel = cleaner.getBatteryLevel();
        logChargeStep(action, batteryLevel);
    }
}

void OutputHandler::logMoveStep(const std::string& action, char direction, const std::string& location){
    stepsLog.push_back(action + "\tfrom " + location + " to direction: " + direction);
}

void OutputHandler::logCleanStep(const std::string& action, int dirtLevel){
    stepsLog.push_back(action + "\tnew dirt Level = " + std::to_string(dirtLevel));
}

void OutputHandler::logChargeStep(const std::string& action, int batteryLevel){
    stepsLog.push_back(action + "\tbattery Level =  " + std::to_string(batteryLevel));
}

void OutputHandler::lastUpdate(int totalTakenStpes, int totalRemainedDirt) {
    totalSteps = totalTakenStpes;
    remainedDirt = totalRemainedDirt;
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
void OutputHandler::writeOutput(int batteryLevel, std::string outputFilePath) const {
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
    if(isVacuumDead) {
        outFile << "Vacuum is Dead: Yes" << std::endl;
    }
    else {
        outFile << "Vacuum is Dead: No\t (battery Level = "<< batteryLevel << ")" << std::endl;
    }
    if(missionSucceeded) {
        outFile << "Mission Succeeded: Yes" << std::endl;
    }
    else {
        outFile << "Mission Succeeded: No\t (Remaining Dirt = " << remainedDirt << ")" << std::endl;
    }
    
    outFile.close();
}
