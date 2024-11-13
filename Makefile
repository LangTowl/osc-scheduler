# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Source files and object files
SRCS = main.cpp instruction.cpp
OBJS = $(SRCS:.cpp=.o)

# Output executable
TARGET = run

# Rule to create the target executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# Rule to compile the .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove the object files and the executable
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets (not actual files)
.PHONY: clean
