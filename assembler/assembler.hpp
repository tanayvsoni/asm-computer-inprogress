#include <iostream>
#include <string>
#include <vector>

enum TokenType {


    /*
    // Extra
    COMMA,
    WHITESPACE,
    DQUOTATION,
    SQUOTATION,

    // Instructions
    INSTR,
    REG,
    NUM,
    VAR,
    
    // Types
    HEX,
    BINARY,

    // Addressing
    HASHTAG,
    BRACKET,

    // Math
    PLUS,
    SUB,
    MUL,
    
    // Organization
    DECLARATIVE,
    LABELS,
    */
};    

struct Token {
    TokenType        type;
    std::string      substring;
};


