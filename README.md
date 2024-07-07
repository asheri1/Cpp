# Vacuum Cleaner Robot Project

## Contributers

- Or Asheri
- Tomer Yihya

## Overview
The Vacuum Cleaner Robot Project simulates an automatic vacuum cleaner.
The vacuum cleaner navigates through a house, cleaning dirt and returning to the docking station for charging. 
The simulation is designed to test various algorithms and strategies for efficient cleaning - while managing battery usage and avoiding walls.

The solution is designed to be modular, with separate classes handling different responsibilities.

This approach allows for easier testing, maintenance, and extension.
The main components are the input file parser, house representation, vacuum cleaner logic, algorithm for decision making, and an output handler. 
The simulator class ties everything together and runs the simulation.



## Files

### `Coordinates.h` and `Coordinates.cpp`
Representing positions in the house.
Includes methods for movement (north, east, south, west) and equality check.

### `FileParser.h` and `FileParser.cpp`
Handles the reading and parsing of the input file.
It extracts battery capacity, maximum steps allowed, and the house layout. 
It also ensures the layout is properly formatted and filled with walls if necessary.

### `House.h` and `House.cpp`
Represents the house layout, including walls, dirt levels, and the docking station. It provides methods to query dirt levels, identify walls, and locate the docking station. It also tracks the total amount of dirt in the house.

### `VacuumCleaner.h` and `VacuumCleaner.cpp`
Manages the vacuum cleaner's state, including its current position, battery level, and actions like moving, cleaning, and charging.
It interacts with the House to get the data which its sensors needs and to perform its operations.
Its also interacts with the Algorithm class in order to obtain its next action in the house.

### `Algorithm.h` and `Algorithm.cpp`
Implements the decision-making logic for the vacuum cleaner.
The Algorithm class determines the next action (move, clean, charge) based on the current state of the vacuum cleaner and the environment.

### `OutputHandler.h` and `OutputHandler.cpp`
Manages the output of the simulation, logging each step taken by the vacuum cleaner and writing the final results to an output file. 
It ensures that the output is formatted correctly and includes all required information.


### `Simulator.h` and `Simulator.cpp`
The Simulator class orchestrates the entire simulation, coordinating between the FileParser, House, VacuumCleaner, Algorithm, and OutputHandler classes.
It runs the simulation loop and manages the overall process.

### `main.cpp`
The entry point of the program, initializing components and running the simulation. 
It parses input arguments, sets up the environment, and manages the execution flow.


## Error Handling
The program includes error handling to manage invalid input files, runtime errors, and unexpected conditions.
It ensures that the simulation can gracefully handle errors without abruptly crashing.


## Building the projects
1. Ensure you have `make` and `g++` installed on your system.
2. Compile the project using the make command:
   ```sh
   make
   ```
3. Run the executable, give an input file as an argument:
   ```sh
   ./myrobot input_file.txt
   ```




## Input File Format

The input file should contain the following information:

1. The battery capacity. 
2. Maximum number of steps allowed.
3. House layout.
   each char represents a dirt level (`0-9`), a wall (`#`), or the docking station (`@`). 

## Output
The program generates an output file which has the following data:

1. All of the steps which were performed.
   for example:
   ```
   MOVE	  from Latout[3][8] to direction: N
   CLEAN	  new dirt Level = 0
   CHARGE  battery Level =  7
   ```
2. Total Steps.
3. Remaining Dirt.
4. Vacuum is Dead.
5. Is Mission Succeeded.

## Example

### Input File - exmaple (`inputfile.txt`)
```
batteryCapacity= 150
maxSteps= 5000
1011022030456708@8934
    02203045670880004
10110220304567####9# #
###5#220304564##88934
f025#2203 4267##88934
013####3 4567##88934
#####################
```

### Output File - example (`output.txt`)
```
MOVE	from Latout[17][1] to direction: E
CLEAN	new dirt Level = 7
...
...
...
MOVE	from Latout[12][5] to direction: S
MOVE	from Latout[12][6] to direction: W
MOVE	from Latout[11][6] to direction: E
MOVE	from Latout[12][6] to direction: E
Total Steps: 5000
Remaining Dirt: 26
Vacuum is Dead: No	 (battery Level = 71)
Mission Succeeded: No	 (Remaining Dirt = 26)
```

