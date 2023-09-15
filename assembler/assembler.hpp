#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

enum TokenType {
    // Extra
    WHITESPACE,
    INLINE_COMMENTS,
    BLOCK_COMMENTS,
    COMMA,
    QUOTATION,

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
    ORG,
    LABELS,
    TEXT,
    DB,
};    


struct Token {
    TokenType   type;
    string      substring;
};


