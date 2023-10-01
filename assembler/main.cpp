#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#include "instructions.hpp"
#include "lexer.hpp"
#include "parser.hpp"

int main(int argc, char* argv[]){
    if (argc != 2) {
        std::cerr << "Usage: ./assembler <filename>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];

    std::ifstream inputFile(filename);

    if(!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file '" << filename << "'" << std::endl;
        return 1;
    }

    std::string fileContents;
    std::string line;

    while(getline(inputFile, line)) {
        fileContents += line + '\n';
    }

    inputFile.close();

    std::vector<Instruction> instruction_list  = get_instr();
    std::vector<Token> tokens = lexer(fileContents, instruction_list);
    parse(tokens);
    

    return 0;
}
