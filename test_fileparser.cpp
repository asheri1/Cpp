
#include "../FileParser.h"
#include <iostream>
#include <vector>

void printHouseLayout(const std::vector<std::vector<char>>& layout) {
    for (const auto& row : layout) {
        for (const auto& cell : row) {
            std::cout << cell;
        }
        std::cout << '\n';
    }
}


void test(std::string filename) {
    
    try {
        FileParser parser(filename);
    
        // Test getHouseLayout
        std::cout << "House Layout:\n";
        printHouseLayout(parser.getLayout());

        // Test getDockingCoordinates
        Coordinates dock = parser.getDockingCoordinates();
        std::cout << "\nDocking Station Coordinates: (" << dock.getX() << ", " << dock.getY() << ")\n";

        // Test getBatteryCapacity
        int batteryCapacity = parser.getBatteryCapacity();
        std::cout << "Battery Capacity: " << batteryCapacity << "\n";

        // Test getMaxStepsAllowed
        int maxSteps = parser.getMaxStepsAllowed();
        std::cout << "Max Steps Allowed: " << maxSteps << "\n\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}






int main() {
    
    std::string files[] = {"house_input.txt", 
                           "house_input2.txt", 
                           "house_input3.txt", 
                           "house_input4.txt",
                           "house_input5.txt",
                           "house_input6.txt",
                           "house_input7.txt",
                           "house_input8.txt",
                           "house_input9.txt",
                           "house_input10.txt",
                           "house_input11.txt",
                           "house_input12.txt",
                           "house_input13.txt",
                           "house_input14.txt", 
                           "house_input15.txt"};

    int number_of_files = 0;
    for(std::string file : files){
        number_of_files++;
    }
    
    for(int i = 0; i < number_of_files; i++){
        std::cout << "Testing: " << files[i] <<"\n";
        test(files[i]);
    }
    

    return 0;
}
