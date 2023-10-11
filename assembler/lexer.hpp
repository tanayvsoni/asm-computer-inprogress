#ifndef ASSEMBLER_HPP
#define ASSEMBLER_HPP

#include <iostream>
#include <string>
#include <vector>

#include "instructions.hpp"

enum TokenType {
    // Whitespace
    WHITESPACE, NEWLINE,

    // Preproccess
    PREPROCESS, INCLUDE, ARGUEMENT,

    // Single-Character Tokens
    PAREN, COMMA,

    // Literals
    IDENTIFIER_DECLARE, IDENTIFIER, LABEL_DECLARE, LABEL_USED, STRING, CHAR, NUMBER, REG, IMMEDIATE, BINARY, HEX, EQUAL, NEGATIVE,

    // Keywords
    INSTRUCTION,
};    

struct Token {
    TokenType        type;
    std::string      substring;
};

std::vector<Token> lexer(std::string text, const std::vector<Instruction>& instruction_list);

//void printTokens(const std::vector<Token>& token_list);

#endif

