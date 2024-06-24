# Define the compiler
CXX = g++

# Define the compiler flags
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -pedantic

# Define the target executable
TARGET = test

# Define the source files
SRCS = Coordinate.cpp test.cpp

# Define the object files
OBJS = $(SRCS:.cpp=.o)

# Default target to build the executable
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to build the object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean the build files
clean:
	rm -f $(OBJS) $(TARGET)

# Rule to run the tests
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run
