
# Makefile

# Variables
CXX = g++
CXXFLAGS = -Wall -O2
TARGET = assembler
SRCS = assembler.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)
HEADERS = assembler.hpp

# Targets
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

$(OBJS): $(HEADERS)  # Objects depend on the header

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

