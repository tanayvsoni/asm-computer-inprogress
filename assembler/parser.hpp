#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <string>
#include <vector>

#include "instructions.hpp"
#include "lexer.hpp"

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

std::vector<ParsedInstruction> parse(std::vector<Token>& tokens, const std::vector<Instruction>& instruction_list);

#endif