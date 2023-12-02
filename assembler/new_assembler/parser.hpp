#ifndef PARSE_HPP
#define PARSE_HPP

#include "main.hpp"
#include "lexer.hpp"

class Parser {
private:
    Lexer _lexer;
    const std::vector<Instruction> _instructionSet;

    struct _Symbol {
        std::string name;
        int value;
    };

    std::vector<_Symbol> _symbolTable;

    void _processInclude();

public:
    Parser(Lexer& lexer, const std::vector<Instruction>& instructionSet);

    void parse();
};

#endif
