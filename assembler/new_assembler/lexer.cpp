#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

#include "lexer.hpp"

Lexer::Lexer(const std::string& sourcePath, const std::vector<Instruction>& instructionSet) 
    : _sourceFilePath(sourcePath), _instructionSet(instructionSet) {
}

void Lexer::tokenize() {

}