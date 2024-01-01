#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <fstream>
#include <memory>

#define OFFSET          0x4000
#define MAX_MEMORY      0xffff
#define SIZE            MAX_MEMORY - OFFSET + 1

enum ERROR {
    STARTADDR_ERROR, INCLUDE_ERROR, FILE_ERROR, ORG_ERROR, STRING_ERROR, ASSIGNMENT_ERROR,
    FLOAT_ERROR, PAREN_ERROR, UNEXP_TOKEN_ERROR,
};

struct Instruction {
    std::string name;
    uint8_t opcode;
    std::string addr_mode;
};

#endif