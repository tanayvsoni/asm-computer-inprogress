#ifndef INSTRUCTIONS_HPP
#define INSTRUCTIONS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

struct Instruction {
    std::string name;
    uint8_t opcode;
    std::string addr_mode;
};

std::vector<Instruction> get_instr();

#endif // INSTRUCTIONS_HPP


