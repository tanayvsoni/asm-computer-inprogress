#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <fstream>
#include <memory>
#include <cmath>


#define OFFSET          0x4000
#define MAX_MEMORY      0xffff

enum ERROR {
    STARTADDR_ERROR, INCLUDE_ERROR, FILE_ERROR, ORG_ERROR, STRING_ERROR, ASSIGNMENT_ERROR,
    FLOAT_ERROR, PAREN_ERROR, UNEXP_TOKEN_ERROR, EXT_ERROR, CONVER_ERROR, ZERO_ERROR, OP_ERROR,
    LARGE_VALUE_ERROR, INSTR_ERROR, SYNTAX_ERROR, OPERAND_ERROR, VAR_ERROR, REG_ERROR, LABEL_ERROR,
};

struct Instruction {
    std::string name;
    uint8_t opcode;
    std::string addr_mode;
};

#endif