#ifndef LEXER_HPP
#define LEXER_HPP

#include "main.hpp"

enum TokenType {
    // Whitespace
    WHITESPACE, NEWLINE,

    // Preproccess
    PREPROCESS, INCLUDE, ARGUEMENT,

    // Keywords
    INSTRUCTION, REG,

    // Comment
    COMMENT,

    // Single-Character Tokens
    L_PAREN, R_PAREN, COMMA, IMMEDIATE, MINUS, EQUAL, PLUS, DIV, MUL,

    // Literals
    IDENTIFIER, LABEL_DECLARE, STRING, CHAR, NUMBER, BINARY, HEX,

    // End
    END
};    

struct Token {
    std::string      substring;
    TokenType        type;
};

class Lexer {
public:
    Lexer(const std::string& sourceCode, const std::vector<Instruction>& instructionSet);  

    void tokenize();
    void print();
    
    Token getNextToken();
    bool hasToken();
    void resetTokenList();


private:
    const std::string _sourceCode;
    const std::vector<Instruction> _instructionSet;
    std::vector<Token> _tokenList; 
     
    std::string _buf;
    long unsigned int _tokenIndex = 0;

    bool _isInInstructionSet();
};

#endif