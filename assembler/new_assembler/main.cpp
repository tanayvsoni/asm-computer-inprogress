#include <iostream>
#include <string>
#include <vector>

#include "main.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./tal <filename>" << std::endl;
        return 1;
    }

    std::string sourcePath = argv[1];
    std::string outputPath = sourcePath;

    size_t lastDot = outputPath.find_last_of(".");
    if (lastDot != std::string::npos) outputPath = outputPath.substr(0, lastDot) + ".bin";
    else outputPath += ".bin";

    Assembler assembler(sourcePath, outputPath);

    return 0;
}