#ifndef LEXER_HPP
#define LEXER_HPP

#include "main.hpp"

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

class Lexer {
private:
    const std::vector<Instruction> _instructionSet;
    std::string _sourceFilePath;

public:
    Lexer(const std::string& sourcePath, const std::vector<Instruction>& instructionSet);

    std::vector<Token> TokenList;    

    void tokenize();
    void print();
};

#endif