#include "lexer.hpp"
#include "main.hpp"

Lexer::Lexer(const std::string& sourcePath, const std::vector<Instruction>& instructionSet)
    : _sourceFilePath(sourcePath), _instructionSet(instructionSet) {
}

void Lexer::print() {
    for (size_t i = 0; i < TokenList.size(); i++) {
        std::cout << 
        " TOKEN TYPE: " << TokenList[i].type << 
        " TOKEN STRING: " << TokenList[i].substring << 
        " | " << TokenList[i].line << 
        std::endl;
    }
}

std::string Lexer::_getContents() {
    /*
    Returns the string output of a text file
    */

    std::ifstream inputFile(_sourceFilePath);

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file '" << _sourceFilePath << "'" << std::endl;
        exit(ERROR);
    }

    std::string fileContents;
    std::string line;

    while (getline(inputFile, line))
        fileContents += line + '\n';

    inputFile.close();

    return fileContents;
}

void Lexer::tokenize() {
    std::string sourceCode = _getContents();
    std::string buf;

    for (size_t i = 0; i < sourceCode.length(); i++) {

        if (i+1 < sourceCode.length() && sourceCode[i] == '/' && sourceCode[i+1] == '*') {                      // Comment Block
            i += 2;
            while (i < sourceCode.length() && !(sourceCode[i] == '*' && sourceCode[i+1] == '/')) {
                if (sourceCode[i] == '\n') _lineNumber++;
                i++;
            }
            i++;   
            TokenList.push_back({"Comment Block", TokenType::COMMENT, _lineNumber});
        }
        else if (sourceCode[i] == ';') {                                                                        // Comment
            while (sourceCode[i] != '\n') i++;
            i--;
            TokenList.push_back({"Inline Comment", TokenType::COMMENT, _lineNumber});
        }
        else if (sourceCode[i] == '.' && std::isalpha(sourceCode[i+1])) {                                       // Preprocessor
            buf.clear();

            i++;
            while (i < sourceCode.length() && std::isalnum(sourceCode[i])) {
                buf.push_back(sourceCode[i]);
                i++;
            }
            i--;

            if(buf == "org" || buf == "db" || buf == "tx" || buf == "include") {
                TokenList.push_back({buf, TokenType::PREPROCESS, _lineNumber});
            }

        }
        else if (std::isalpha(sourceCode[i])) {                                                                 // Alpha Character
            buf.clear();

            while (i < sourceCode.length() && std::isalnum(sourceCode[i])) {
                buf.push_back(sourceCode[i]);
                i++;
            }
            i--;
        }
        else if (std::isspace(sourceCode[i]) && sourceCode[i] != '\n') {                                        // Whitespace
            while (i < sourceCode.length() && std::isspace(sourceCode[i]) && sourceCode[i] != '\n') i++;
            i--;
            TokenList.push_back({"Whitespace", TokenType::WHITESPACE, _lineNumber});
        }
        else if (sourceCode[i] == '\n') {                                                                       // Newline
            _lineNumber++;
            TokenList.push_back({"Newline", TokenType::NEWLINE});
        }
    
    }
};
