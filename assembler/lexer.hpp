#ifndef ASSEMBLER_HPP
#define ASSEMBLER_HPP

#include <iostream>
#include <string>
#include <vector>

#include "instructions.hpp"

enum TokenType {
    // Whitespace
    WHITESPACE,

    // Single-Character Tokens
    PAREN, COMMA,

    // Literals
    IDENTIFIER, LABEL, STRING, CHAR, NUMBER, REG, IMMEDIATE, BINARY, HEX, EQUAL,

    // Keywords
    INSTRUCTION, PREPROCESS,
};    

struct Token {
    TokenType        type;
    std::string      substring;
};

std::vector<Token> lexer(std::string text, const std::vector<Instruction> instruction_list);

#endif

