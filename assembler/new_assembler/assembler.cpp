#include "assembler.hpp"
#include "lexer.hpp"
#include "parser.hpp"

const std::vector<Instruction> Assembler::_instructionSet = createInstructionSet();

Assembler::Assembler(const std::string &sourcePath, const std::string &outputPath)
    : _sourceFilePath(sourcePath), _outputFilePath(outputPath) {
}

void Assembler::assemble() {
    Lexer lexer(_sourceFilePath, _instructionSet);

    lexer.tokenize();
    lexer.print();
}