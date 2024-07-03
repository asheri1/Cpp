#include "../House.h"
#include <iostream>
#include <cassert>

void test_house_initialization() {
    FileParser parser("input_files/house_input.txt");
    House house(parser);

    // Check the docking station coordinates
    Coordinates dock = house.getDockingCoordinates();
    assert(dock.getX() == 17 && dock.getY() == 1 && "Docking station should be at (17, 1)");

    // Check for walls and open spaces
    assert(house.isWall(Coordinates(0, 0)) == true && "Coordinate (0, 0) should be a wall");
    assert(house.isWall(Coordinates(1, 1)) == false && "Coordinate (1, 1) should not be a wall");

    // Check the dirt level
    assert(house.getDirtLevel(Coordinates(0, 0)) == 0 && "Coordinate (0, 0) is a wall and should have a dirt level of 0");
    assert(house.getDirtLevel(Coordinates(6, 2)) == 2 && "Coordinate (6, 2) should have a dirt level of 2");
    assert(house.getDirtLevel(Coordinates(17, 4)) == 8 && "Coordinate (17, 4) should have a dirt level of 8");


    std::cout << "test_house_initialization passed!" << std::endl;
}


int main() {
    test_house_initialization();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
