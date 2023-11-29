#ifndef LEXER_HPP
#define LEXER_HPP

#include "main.hpp"

enum TokenType {
    // Whitespace
    WHITESPACE, NEWLINE,

    // Preproccess
    PREPROCESS, INCLUDE, ARGUEMENT,

    // Comment
    COMMENT,

    // Single-Character Tokens
    PAREN, COMMA,

    // Literals
    IDENTIFIER_DECLARE, IDENTIFIER, LABEL_DECLARE, LABEL_USED, STRING, CHAR, NUMBER, REG, IMMEDIATE, BINARY, HEX, EQUAL, NEGATIVE,

    // Keywords
    INSTRUCTION,
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

    std::string _getContents();

public:
    Lexer(const std::string& sourcePath, const std::vector<Instruction>& instructionSet);

    std::vector<Token> TokenList;    

    void tokenize();
    void print();
};

#endif