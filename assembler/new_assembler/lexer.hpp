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
private:
    const std::string _sourceCode;
    const std::vector<Instruction> _instructionSet;
     
    std::string _buf;
    long unsigned int _tokenNumber = 0;

    bool _isInInstructionSet();

public:
    Lexer(const std::string& sourceCode, const std::vector<Instruction>& instructionSet);  

    std::vector<Token> TokenList;   

    void tokenize();
    void print();
    void reset();
    
    void eatToken(int i);
    bool hasToken();
    Token nextToken();

};

#endif