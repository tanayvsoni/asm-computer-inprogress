#include <iostream>
#include <string>
#include <vector>

enum TokenType {
    // Whitespace
    WHITESPACE,

    // Single-Character Tokens
    LEFT_PAREN, RIGHT_PAREN, COMMA,

    // Literals
    IDENTIFIER, STRING, CHAR, NUMBER,

    // Keywords
    INSTRUCTION, PREPROCESS,
};    

struct Token {
    TokenType        type;
    std::string      substring;
};

std::vector<Token> lexer(std::string text);

