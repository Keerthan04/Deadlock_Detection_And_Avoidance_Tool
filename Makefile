# Makefile for Deadlock Detection & Avoidance Tool

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = deadlock_tool
SOURCES = main.cpp bankers_algorithm.cpp rag_single_instance.cpp
HEADERS = bankers_algorithm.h rag_single_instance.h

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Clean build files
clean:
	rm -f $(TARGET) $(TARGET).exe

# Run the program
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
