#ifndef INSTRUCTIONS_HPP
#define INSTRUCTIONS_HPP

#include <iostream>
#include <string>
#include <vector>

struct Instruction {
    std::string name;
    int opcode;
    std::string addr_mode;
};

std::vector<Instruction> get_instr();

#endif // INSTRUCTIONS_HPP


