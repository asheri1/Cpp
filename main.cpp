#include "Simulator.h"

#include <iostream>
#include <stdexcept>
#include <string>

#include <fstream>
#include <vector>



int main(int argc, char* argv[]) {
    // Check if the user has provided the input file path
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " <house_input_file>" << std::endl;
        return 1;
    }

    try {
        FileParser parser(argv[1]);             // parse the input file
        House house(parser);                    // create the house object
        VacuumCleaner cleaner(parser, house);   // create the vacuum cleaner object
        Algorithm algorithm;                    // create the algorithm object
        OutputHandler outputer;                 // create the output handler object

        // create myrobot object
        Simulator robot(parser, house, cleaner, algorithm, outputer);  
        
        // Run the vacuum cleaner simulation
        robot.run();

        // create output File
        outputer.setVacuumStatus((cleaner.getBatteryLevel() <= 0), (house.getTotalDirt() == 0 && cleaner.isAtDocking()));
        outputer.writeOutput(cleaner.getBatteryLevel(), "output.txt");
    } 

    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
