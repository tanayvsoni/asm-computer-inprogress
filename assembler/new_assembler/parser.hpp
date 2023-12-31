#ifndef PARSE_HPP
#define PARSE_HPP

#include "main.hpp"
#include "lexer.hpp"

struct ASTNode {
    std::unique_ptr<Token> data;
    std::string value = "";
    std::vector<std::shared_ptr<ASTNode>> children;

    ASTNode(std::unique_ptr<Token> token) : data(std::move(token)) {}
};

class Parser {
public:
    Parser(const Lexer& lexer, const std::vector<Instruction>& instructionSet);

    void parseProgram();
    void printAST() { _printAST(rootNode, 0); }

    std::shared_ptr<ASTNode> rootNode;
    
private:
    Lexer _lexer;
    const std::vector<Instruction>& _instructionSet;
    void _printAST(std::shared_ptr<ASTNode> node, int depth);

    std::unique_ptr<ASTNode> _parseStatement();

    std::unique_ptr<ASTNode> _parseOrg();
    std::unique_ptr<ASTNode> _parseDirective();

    std::unique_ptr<ASTNode> _parseVariableAssignment();
    std::unique_ptr<ASTNode> _parseMathExpression();
    std::unique_ptr<ASTNode> _parseAdditionSubtraction();
    std::unique_ptr<ASTNode> _parseMultiplicationDivision();
    std::unique_ptr<ASTNode> _parsePrimary();

    std::unique_ptr<ASTNode> _parseInstruction();
    std::unique_ptr<ASTNode> _parseOperand();
    std::unique_ptr<ASTNode> _parseLabel();

    std::shared_ptr<Token> _currToken; 
    Token _peekNextToken() { return _lexer.peekNextToken(); }
    void _advanceToken() { _currToken = _hasToken() ? _lexer.getToken() : _currToken;  }
    bool _hasToken() { return _lexer.hasToken(); }
};

#endif
