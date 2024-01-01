#ifndef CODEGEN_HPP
#define CODEGEN_HPP

#include "main.hpp"
#include "lexer.hpp"
#include "parser.hpp"

class CodeGen {
public:
    CodeGen(const Parser& parser, const std::vector<Instruction>& instructionSet)
    : _ast(parser.rootNode), _instructionsSet(instructionSet) {}

    void generateCode();

private:
    const std::shared_ptr<ASTNode> _ast;
    const std::vector<Instruction> _instructionsSet;

    int _address = 0;
    std::vector<uint8_t> _machineCode = std::vector<uint8_t>(MAX_MEMORY + 1, 0);

    int _convertToInt(const std::shared_ptr<ASTNode>& node);

    void _generateCodeFromNode(const std::shared_ptr<ASTNode>& node);
    void _generateCodeForOrg(const std::shared_ptr<ASTNode>& node);
    void _generateCodeForVar(const std::shared_ptr<ASTNode>& node);
};

#endif