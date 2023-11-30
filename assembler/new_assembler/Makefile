
# Makefile

# Variables
CXX = g++
CXXFLAGS = -std=c++20 -fno-exceptions -Wall -O3 -g -Wno-unused-function -Os
TARGET = tal
SRCS = parser.cpp lexer.cpp assembler.cpp main.cpp 
OBJS = $(SRCS:.cpp=.o)
HEADERS = parser.hpp lexer.hpp assembler.hpp main.hpp
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

