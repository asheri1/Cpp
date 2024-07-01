#ifndef OUTPUTHANDLER_H
#define OUTPUTHANDLER_H

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
    void logStep(const std::string& step);
    void setRemainedDirt(int dirtLevel);
    void setVacuumStatus(bool isDead, bool missionSucceeded);
     
    // write to file method.
    void writeOutput() const;
};

#endif
