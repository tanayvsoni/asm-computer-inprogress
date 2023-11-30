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

bool Lexer::_isInInstructionSet() {
    for (size_t i = 0; i < _instructionSet.size(); i++) 
        if (_buf == _instructionSet[i].name) return true;
    return false;
}

void Lexer::tokenize() {
    std::string sourceCode = _getContents();

    for (size_t i = 0; i < sourceCode.length(); i++) {

        if (i+1 < sourceCode.length() && sourceCode[i] == '/' && sourceCode[i+1] == '*') {                      // Comment Block
            i += 2;
            while (i < sourceCode.length() && !(sourceCode[i] == '*' && sourceCode[i+1] == '/')) {
                if (sourceCode[i] == '\n') _lineNumber++;
                i++;
            }
            i++;   
            //TokenList.push_back({"Comment Block", TokenType::COMMENT, _lineNumber});
        }
        else if (sourceCode[i] == ';') {                                                                        // Comment
            while (sourceCode[i] != '\n') i++;
            i--;
            //TokenList.push_back({"Inline Comment", TokenType::COMMENT, _lineNumber});
        }
        else if (sourceCode[i] == '.' && std::isalpha(sourceCode[i+1])) {                                       // Preprocessor
            _buf.clear();

            i++;
            while (i < sourceCode.length() && std::isalnum(sourceCode[i])) {
                _buf.push_back(sourceCode[i]);
                i++;
            }
            i--;

            if(_buf == "org" || _buf == "db" || _buf == "tx" || _buf == "include") {
                TokenList.push_back({_buf, TokenType::PREPROCESS, _lineNumber});
            }

        }
        else if (std::isalpha(sourceCode[i])) {                                                                 // Alpha Character
            _buf.clear();

            while (i < sourceCode.length() && (std::isalnum(sourceCode[i]) || sourceCode[i] == '_')) {
                _buf.push_back(sourceCode[i]);
                i++;
            }
            i--;

            if (_isInInstructionSet()) {                                                                        // Instruction
                TokenList.push_back({_buf, TokenType::INSTRUCTION, _lineNumber});
            } else if (sourceCode[i+1] == ':') {                                                                // Label Declaration
                TokenList.push_back({_buf, TokenType::LABEL_DECLARE, _lineNumber});
            } else if (_buf == "rX" || _buf == "rY") {                                                          // Registers
                TokenList.push_back({_buf.erase(0,1), TokenType::REG, _lineNumber});
            } else {
                TokenList.push_back({_buf, TokenType::IDENTIFIER, _lineNumber});
            }
        }
        else if (sourceCode[i] == '=') {                                                                        // Equals
            TokenList.push_back({"Equal", TokenType::EQUAL, _lineNumber});
        }
        else if (sourceCode[i] == '#') {                                                                        // Immediate
            TokenList.push_back({"Immediate", TokenType::IMMEDIATE, _lineNumber});                              
        }
        else if (sourceCode[i] == '(') {                                                                        // Left Paren
            TokenList.push_back({"Left Paren", TokenType::L_PAREN, _lineNumber});                              
        }
        else if (sourceCode[i] == ')') {                                                                        // Right Paren
            TokenList.push_back({"Right Paren", TokenType::R_PAREN, _lineNumber});                              
        }
        else if (sourceCode[i] == '-') {                                                                        // Negative
            TokenList.push_back({"Negative", TokenType::NEGATIVE, _lineNumber});                                
        }
        else if (sourceCode[i] == ',') {                                                                        // Comma
            TokenList.push_back({"Comma", TokenType::COMMA, _lineNumber});                                      
        }
        else if (sourceCode[i] == '<') {                                                                        // Include Arguements
            _buf.clear();
            i++;

            while (i < sourceCode.length() && sourceCode[i] != '>') {
                _buf.push_back(sourceCode[i]);
                i++;
            }

            TokenList.push_back({_buf, TokenType::ARGUEMENT, _lineNumber});
        }
        else if (sourceCode[i] == '\'') {                                                                       // Char
            _buf.clear();
            i++;

            while (i < sourceCode.length() && (sourceCode[i] != '\'' || sourceCode[i-1] == '\\')) {
                // Handle the escape sequence for single quote
                if (sourceCode[i] == '\\' && i + 1 < sourceCode.length() && sourceCode[i+1] == '\'') {
                    _buf.push_back('\'');
                    i++;
                } else _buf.push_back(sourceCode[i]);
                i++;
            }

            TokenList.push_back({_buf, TokenType::CHAR, _lineNumber});
        }
        else if (sourceCode[i] == '"') {                                                                        // String  
            _buf.clear();
            i++;

            while (i < sourceCode.length() && (sourceCode[i] != '"' || sourceCode[i-1] == '\\')) {
                // Handle the escape sequence for double quote
                if (sourceCode[i] == '\\' && i + 1 < sourceCode.length() && sourceCode[i+1] == '"') {
                    _buf.push_back('"');
                    i++;
                } else _buf.push_back(sourceCode[i]);
                i++;
            }

            TokenList.push_back({_buf, TokenType::STRING, _lineNumber});
        }
        else if (sourceCode[i] == '$') {                                                                        // Hex
            _buf.clear();
            i++;

            while (i < sourceCode.length() && std::isalnum(sourceCode[i])) {
                _buf.push_back(sourceCode[i]);
                i++;
            }
            i--;
            TokenList.push_back({_buf, TokenType::HEX, _lineNumber});
        }
        else if (sourceCode[i] == '%') {                                                                        // Binary
            _buf.clear();
            i++;

            while (i < sourceCode.length() && std::isalnum(sourceCode[i])) {
                _buf.push_back(sourceCode[i]);
                i++;
            }
            i--;
            TokenList.push_back({_buf, TokenType::BINARY, _lineNumber});
        }
        else if (std::isdigit(sourceCode[i])) {                                                                 // Number
            _buf.clear();
            while (i < sourceCode.length() && std::isdigit(sourceCode[i])) {
                _buf.push_back(sourceCode[i]);
                i++;
            }
            i--;

            TokenList.push_back({_buf, TokenType::NUMBER, _lineNumber});
        }
        else if (std::isspace(sourceCode[i]) && sourceCode[i] != '\n') {                                        // Whitespace
            while (i < sourceCode.length() && std::isspace(sourceCode[i]) && sourceCode[i] != '\n') i++;
            i--;
            //TokenList.push_back({"Whitespace", TokenType::WHITESPACE, _lineNumber});
        }
        else if (sourceCode[i] == '\n') {                                                                       // Newline
            _lineNumber++;
            //TokenList.push_back({"Newline", TokenType::NEWLINE});
        }
    
    }
};
