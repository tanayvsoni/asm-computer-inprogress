#include "assembler.hpp"
#include "instructions.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

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

    //cout << "File Contents:" << endl;
    //cout << fileContents;
         
    //lexer(fileContents);

    get_instr();

    return 0;
}
