#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include <fstream>

#include "functions.hpp"

std::string toLowerCase(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return result;
}

std::string toUpperCase(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::toupper(c); });
    return result;
}

std::string get_contents(const std::string& filename) {
    std::ifstream inputFile(filename);

    if(!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file '" << filename << "'" << std::endl;
        exit(1);
    }

    std::string fileContents;
    std::string line;

    while(getline(inputFile, line)) fileContents += line + '\n';

    inputFile.close();

    return fileContents;
}