# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -pedantic

# Project name
TARGET = myrobot

# Source files
SRCS = myrobot.cpp Coordinates.cpp FileParser.cpp House.cpp VacuumCleaner.cpp Algorithm.cpp OutputHandler.cpp

# Default rule
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Clean up generated files
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: all clean
