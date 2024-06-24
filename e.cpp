#include <iostream>
#include <vector>

int main() {
    std::vector<int> myVector = {1, 2, 3, 4, 5};

    // Add elements
    myVector.push_back(6);
    myVector.push_back(7);

    // Access elements
    std::cout << "First element: " << myVector[0] << std::endl;

    // Iterate using range-based for loop
    std::cout << "Elements: ";
    for (int value : myVector) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    // Remove an element
    myVector.pop_back();

    // Display size and capacity
    std::cout << "Size: " << myVector.size() << std::endl;
    std::cout << "Capacity: " << myVector.capacity() << std::endl;

    return 0;
}
