#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <fstream>

#define OFFSET  0x4000
#define ERROR   1

struct Instruction {
    std::string name;
    uint8_t opcode;
    std::string addr_mode;
};

struct ParsedInstruction {
    Instruction instr;
    int argumentValue;
    std::string label_val = "";
    int address = 0;
};

struct Labels {
    std::string name;
    int address;
};

struct Vars {
    std::string name;
    int val;
};

std::string toLowerCase(const std::string& input);
std::string toUpperCase(const std::string& input);

#endif