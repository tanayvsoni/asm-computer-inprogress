#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

#include "main.hpp"

const std::vector<Instruction> Assembler::m_instructionSet = createInstructionSet();

Assembler::Assembler(const std::string& sourcePath, const std::string& outputPath)
    : m_sourceFilePath(sourcePath), m_outputFilePath(outputPath) {
}

void Assembler::assemble() {
    Lexer lexer(m_sourceFilePath, m_instructionSet);

    lexer.tokenize();
}