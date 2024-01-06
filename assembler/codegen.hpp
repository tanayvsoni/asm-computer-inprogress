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
    void printFile(const std::string& outputPath);

private:
    const std::shared_ptr<ASTNode> _ast;
    const std::vector<Instruction> _instructionsSet;

    int _address = 0;
    std::vector<uint8_t> _machineCode = std::vector<uint8_t>(MAX_MEMORY + 1, 0);

    struct _SymbolTable {
        std::string name;
        int value;
    };

    std::vector<_SymbolTable> _varTable;
    std::vector<_SymbolTable> _labelTable;

    std::vector<std::pair<int, std::string>> _labelReplacementLocation;

    int _convertToInt(const std::unique_ptr<Token>& node);
    int _evaluateExpression(const std::shared_ptr<ASTNode>& node);
    void _updateSymbolTable(std::vector<_SymbolTable>& table, const std::string& name, const int& value);
    int _getOpcode(const std::string& name, const std::string& addressing_mode);
    
    void _generateNodeCode(const std::shared_ptr<ASTNode>& node);
    void _updateLabels();

    void _orgAssigment(const std::shared_ptr<ASTNode>& node);
    void _directiveAssignment(const std::shared_ptr<ASTNode>& node);
    void _labelAssignment(const std::shared_ptr<ASTNode>& node);
    void _varAssignment(const std::shared_ptr<ASTNode>& node);
    void _instructionCode(const std::shared_ptr<ASTNode>& node);
    std::string _getReg(const std::shared_ptr<ASTNode>& node);
    int _findLabelVal(const std::string& name);
};

#endif