#ifndef PARSE_HPP
#define PARSE_HPP

#include "main.hpp"
#include "lexer.hpp"

struct ASTNode {
    Token* data;
    std::string value = "";
    std::vector<ASTNode*> children;

    ASTNode(Token* token) : data(token) {}
};

class Parser {
public:
    Parser(Lexer lexer, const std::vector<Instruction>& instructionSet);

    void parseProgram();
    void printAST() { _printAST(_rootNode, 0); }

    ASTNode* rootNode = _rootNode;
    
private:
    Lexer _lexer;
    const std::vector<Instruction> _instructionSet;
    void _printAST(ASTNode* node, int depth);

    ASTNode* _parseStatement();

    ASTNode* _parseOrg();
    ASTNode* _parseDirective();

    ASTNode* _parseVariableAssignment();
    ASTNode* _parseMathExpression();
    ASTNode* _parseAdditionSubtraction();
    ASTNode* _parseMultiplicationDivision();
    ASTNode* _parsePrimary();

    ASTNode* _parseInstruction();
    ASTNode* _parseOperand();
    ASTNode* _parseLabel();

    Token* _currToken; 
    Token _peekNextToken() { return _lexer.peekNextToken(); }
    void _advanceToken() { _currToken = _hasToken() ? _lexer.getToken() : _currToken;  }
    bool _hasToken() { return _lexer.hasToken(); }

    ASTNode* _rootNode;
};

#endif
