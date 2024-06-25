#include "Coordinates.h"
#include <iostream>
#include <cassert>

// Helper function to run and print tests
void runTest(bool condition, const std::string& testName) {
    if (condition) {
        std::cout << "Passed: " << testName << std::endl;
    } else {
        std::cout << "Failed: " << testName << std::endl;
    }
}


int main() {
    
    // Test the parameterized constructor
    Coordinates coord1(10, 20);
    runTest(coord1.getX() == 10 && coord1.getY() == 20, "Parameterized Constructor");

    // Test the getX method
    Coordinates coord2(30, 40);
    runTest(coord2.getX() == 30, "getX Method");

    // Test the getY method
    runTest(coord2.getY() == 40, "getY Method");


    // Test the setX method
    coord1.setX(15);
    runTest(coord1.getX() == 15, "setX Method");

    // Test the setY method
    coord1.setY(25);
    runTest(coord1.getY() == 25, "setY Method");

    // Test the equality operator
    Coordinates coord3(10, 20);
    Coordinates coord4(10, 20);
    Coordinates coord5(15, 25);
    runTest(coord3 == coord4, "Equality Operator - Equal");
    runTest(!(coord3 == coord5), "Equality Operator - Not Equal");

    return 0;

}
