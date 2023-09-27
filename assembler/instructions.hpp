#include <iostream>
#include <string>
#include <vector>

struct Instruction {
    std::string name;
    int opcode;
    std::string addr_mode;
};

std::vector<Instruction> get_instr();
