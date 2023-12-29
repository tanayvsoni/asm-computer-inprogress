#include "assembler.hpp"

const std::vector<Instruction> Assembler::_instructionSet = createInstructionSet();

Assembler::Assembler(const std::string &sourcePath, const std::string &outputPath)
    : _sourceFilePath(sourcePath), _outputFilePath(outputPath) {
}

void Assembler::assemble() {

    Preprocessor process;
    std::string sourceCode;

    process.processFile(_sourceFilePath, sourceCode);

    Lexer lexer(sourceCode, _instructionSet);

    lexer.tokenize();
    lexer.print();
}
