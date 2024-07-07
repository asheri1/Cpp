#ifndef OUTPUTHANDLER_H
#define OUTPUTHANDLER_H

#include "VacuumCleaner.h"
#include <string>
#include <vector>

class OutputHandler
{
private:
    const std::string outputFilePath;
    std::vector<std::string> stepsLog;

    int totalSteps;
    int remainedDirt;
    bool isVacuumDead;
    bool missionSucceeded;

public:
    // constructors
    OutputHandler();
    OutputHandler(const std::string& filePath);

    // setters.
    void logStep(const std::string& action, char direction, VacuumCleaner& cleaner);
    void logMoveStep(const std::string& action, char direction, const std::string& location);
    void logCleanStep(const std::string& action, int totalDirt);
    void logChargeStep(const std::string& action, int batteryLevel);
    void lastUpdate(int totalTakenStpes, int totalRemainedDirt);

    void setRemainedDirt(int dirtLevel);
    void setVacuumStatus(bool isDead, bool missionSucceeded);
     
    // write to file method.
    void writeOutput(int batteryLevel, std::string outputFilePath) const;
};

#endif
