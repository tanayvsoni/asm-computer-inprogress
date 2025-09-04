#include "main.hpp"
#include "assembler.hpp"

int main(int argc, char* argv[]) {
    // Check if file is provided
    if (argc != 2) {
        std::cerr << "Usage: ./tasml <filename>" << std::endl;
        exit(ERROR::FILE_ERROR);
    }

    // Check if the file extension is .tasml
    std::string sourcePath = argv[1];
    size_t lastDot = sourcePath.find_last_of(".");
    if (lastDot == std::string::npos || sourcePath.substr(lastDot) != ".tasml") {
        std::cerr << "Error: File must have a .tasml extension" << std::endl;
        exit(ERROR::EXT_ERROR);
    }

    std::string outputPath = sourcePath.substr(0, lastDot) + ".bin";

    Assembler assembler(sourcePath, outputPath);
    assembler.assemble();

    return 0;
}