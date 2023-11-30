#ifndef LEXER_HPP
#define LEXER_HPP

#include "main.hpp"

enum TokenType {
    // Whitespace
    WHITESPACE, NEWLINE,

    // Preproccess
    PREPROCESS, INCLUDE, ARGUEMENT,

    // Keywords
    INSTRUCTION,

    // Comment
    COMMENT,

    // Single-Character Tokens
    L_PAREN, R_PAREN, COMMA, IMMEDIATE, NEGATIVE, EQUAL,

    // Literals
    IDENTIFIER, LABEL_DECLARE, STRING, CHAR, NUMBER, BINARY, HEX, REG,
};    

struct Token {
    std::string      substring;
    TokenType        type;
    int              line;
};

class Lexer {
private:
    const std::string _sourceFilePath;
    const std::vector<Instruction> _instructionSet;
    
    int _lineNumber = 1;
    std::string _buf;

    std::string _getContents();
    bool _isInInstructionSet();

public:
    Lexer(const std::string& sourcePath, const std::vector<Instruction>& instructionSet);

    std::vector<Token> TokenList;    

    void tokenize();
    void print();
};

#endif