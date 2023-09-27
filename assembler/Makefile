
# Makefile

# Variables
CXX = g++
CXXFLAGS = -Wall -O2 -Wno-unused-function
TARGET = assembler
SRCS = assembler.cpp instructions.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)
HEADERS = assembler.hpp instructions.hpp

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

