
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

int main() {
    try {
        // Replace "house_input.txt" with the path to your actual test input file
        FileParser parser("house_input.txt");

        // Test getHouseLayout
        std::cout << "House Layout:\n";
        printHouseLayout(parser.getLayout());

        // Test getDockingCoordinates
        Coordinates dock = parser.getDockingCoordinates();
        std::cout << "Docking Station Coordinates: (" << dock.getX() << ", " << dock.getY() << ")\n";

        // Test getBatteryCapacity
        int batteryCapacity = parser.getBatteryCapacity();
        std::cout << "Battery Capacity: " << batteryCapacity << "\n";

        // Test getMaxStepsAllowed
        int maxSteps = parser.getMaxStepsAllowed();
        std::cout << "Max Steps Allowed: " << maxSteps << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
