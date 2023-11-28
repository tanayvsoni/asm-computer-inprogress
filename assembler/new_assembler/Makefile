
# Makefile

# Variables
CXX = g++
CXXFLAGS = -std=c++20 -Wall -O2 -g -Wno-unused-function
TARGET = tal
SRCS = assembler.cpp main.cpp 
OBJS = $(SRCS:.cpp=.o)
HEADERS = main.hpp
PYTHON_SCRIPT = instruction_setup.py

# Targets
all: run_python_script $(TARGET)
	rm -f $(OBJS)

run_python_script:
	python3 $(PYTHON_SCRIPT)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

$(OBJS): $(HEADERS)  # Objects depend on the header

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

