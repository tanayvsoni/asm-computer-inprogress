#ifndef PARSE_HPP
#define PARSE_HPP

#include "main.hpp"
#include "lexer.hpp"

struct ASTNode {
    TokenType type;
    std::string substring;
    ASTNode* leftNode;
    ASTNode* rightNode;
};

class Parser {
public:
    Parser(Lexer& lexer, const std::vector<Instruction>& instructionSet);

    void parse();
    
private:
    Lexer _lexer;
    const std::vector<Instruction> _instructionSet;

    ASTNode _AST; 
    
    Token _nextToken = _lexer.getNextToken();
    Token _currToken; 

    void preprocess_statment();
};

#endif
