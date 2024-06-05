
# Makefile

# Variables
CXX = g++
CXXFLAGS = -std=c++20 -fno-exceptions -Wall -Wno-unused-function -Os
TARGET = emulator
SRCS = emulator.cpp main.cpp 
OBJS = $(SRCS:.cpp=.o)
HEADERS = emulator.hpp main.hpp 

# Targets
all: $(TARGET)
	rm -f $(OBJS)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

$(OBJS): $(HEADERS)  # Objects depend on the header

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

