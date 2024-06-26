#include "../House.h"
#include <iostream>
#include <cassert>

void test_house_initialization() {
    House house("house_input.txt");

    // Check the battery capacity
    assert(house.getBatteryCapacity() == 100 && "Battery capacity should be 100");

    // Check the maximum steps allowed
    assert(house.getMaxStepsAllowed() == 300 && "Max steps allowed should be 300");

    // Check the docking station coordinates
    Coordinates dock = house.getDockingCoordinates();
    assert(dock.getX() == 18 && dock.getY() == 2 && "Docking station should be at (18, 2)");

    // Check for walls and open spaces
    assert(house.isWall(Coordinates(0, 0)) == true && "Coordinate (0, 0) should be a wall");
    assert(house.isWall(Coordinates(1, 1)) == false && "Coordinate (1, 1) should not be a wall");

    // Check the dirt level
    assert(house.getDirtLevel(Coordinates(1, 1)) == 1 && "Coordinate (1, 1) should have a dirt level of 1");
    assert(house.getDirtLevel(Coordinates(4, 2)) == 9 && "Coordinate (4, 2) should have a dirt level of 9");

    std::cout << "test_house_initialization passed!" << std::endl;
}


int main() {
    test_house_initialization();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
