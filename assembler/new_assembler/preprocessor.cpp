#include "preprocessor.hpp"

std::string Preprocessor::_extractIncludedFilePath(const std::string &line) {
    // Extract the file path from the include directive
    // Assuming the format is: .include <filepath>
    size_t start = line.find('<') + 1;
    size_t end = line.find('>');
    if (start == std::string::npos || end == std::string::npos || start >= end) {
        std::cerr << "Error: invalid include directive format" << std::endl;
        exit(ERROR::INCLUDE_ERROR);
    }
    return line.substr(start, end - start);
}

void Preprocessor::processFile(const std::string& filePath, std::string& output) {
    std::ifstream inputFile(filePath);

    if (!inputFile.is_open()) {
        std::cerr << "Error: unable to open file '" << filePath << "'" << std::endl;
        exit(ERROR::FILE_ERROR);
    }

    std::string line;

    while (std::getline(inputFile, line)) {
        if (line.find(".include") == 0) {
            std::string includedFilePath = _extractIncludedFilePath(line);
            processFile(includedFilePath, output);
        }

        output += line + '\n';

    }

    inputFile.close();
}