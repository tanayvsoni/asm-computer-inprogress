#include "lexer.hpp"

Lexer::Lexer(const std::string& sourceCode, const std::vector<Instruction>& instructionSet)
    : _sourceCode(sourceCode), _instructionSet(instructionSet) {
}

void Lexer::print() {
    for (size_t i = 0; i < _tokenList.size(); i++) {
        std::cout << 
        " TOKEN TYPE: " << _tokenList[i].type << 
        " TOKEN STRING: " << _tokenList[i].substring << 
        std::endl;
    }
}

void Lexer::resetTokenList() {
    _tokenIndex = 0;
}

bool Lexer::hasToken() {
    if (_tokenIndex >= _tokenList.size()) return false;
    return true;
}

Token Lexer::getNextToken() {
    return _tokenList[_tokenIndex++];
}

bool Lexer::_isInInstructionSet() {
    for (size_t i = 0; i < _instructionSet.size(); i++) 
        if (_buf == _instructionSet[i].name) return true;
    return false;
}

void Lexer::tokenize() {

    for (size_t i = 0; i < _sourceCode.length(); i++) {

        if (i+1 < _sourceCode.length() && _sourceCode[i] == '/' && _sourceCode[i+1] == '*') {                    // Comment Block
            i += 2;
            while (i < _sourceCode.length() && !(_sourceCode[i] == '*' && _sourceCode[i+1] == '/')) {
                //if (_sourceCode[i] == '\n') _lineNumber++;
                i++;
            }
            i++;   
            //_tokenList.push_back({"Comment Block", TokenType::COMMENT, _lineNumber});
        }
        else if (_sourceCode[i] == ';') {                                                                        // Comment
            while (_sourceCode[i] != '\n') i++;
            i--;
            //_tokenList.push_back({"Inline Comment", TokenType::COMMENT, _lineNumber});
        }
        else if (_sourceCode[i] == '.' && std::isalpha(_sourceCode[i+1])) {                                      // Preprocessor
            _buf.clear();

            i++;
            while (i < _sourceCode.length() && std::isalnum(_sourceCode[i])) {
                _buf.push_back(_sourceCode[i]);
                i++;
            }
            i--;

            if(_buf == "org" || _buf == "db" || _buf == "tx") {
                _tokenList.push_back({_buf, TokenType::PREPROCESS});
            }

        }
        else if (std::isalpha(_sourceCode[i])) {                                                                 // Alpha Character
            _buf.clear();

            while (i < _sourceCode.length() && (std::isalnum(_sourceCode[i]) || _sourceCode[i] == '_')) {
                _buf.push_back(_sourceCode[i]);
                i++;
            }
            i--;

            if (_isInInstructionSet()) {                                                                        // Instruction
                _tokenList.push_back({_buf, TokenType::INSTRUCTION});
            } else if (_sourceCode[i+1] == ':') {                                                                // Label Declaration
                _tokenList.push_back({_buf, TokenType::LABEL_DECLARE});
            } else if (_buf == "rX" || _buf == "rY") {                                                          // Registers
                _tokenList.push_back({_buf.erase(0,1), TokenType::REG});
            } else {
                _tokenList.push_back({_buf, TokenType::IDENTIFIER});
            }
        }
        else if (_sourceCode[i] == '=') {                                                                        // Equals
            _tokenList.push_back({"Equal", TokenType::EQUAL});
        }
        else if (_sourceCode[i] == '#') {                                                                        // Immediate
            _tokenList.push_back({"Immediate", TokenType::IMMEDIATE});                              
        }
        else if (_sourceCode[i] == '(') {                                                                        // Left Paren
            _tokenList.push_back({"Left Paren", TokenType::L_PAREN});                              
        }
        else if (_sourceCode[i] == ')') {                                                                        // Right Paren
            _tokenList.push_back({"Right Paren", TokenType::R_PAREN});                              
        }
        else if (_sourceCode[i] == '-') {                                                                        // Minus
            _tokenList.push_back({"Minus", TokenType::MINUS});                                
        }
        else if (_sourceCode[i] == '+') {                                                                        // Plus
            _tokenList.push_back({"Plus", TokenType::PLUS});                                
        }
        else if (_sourceCode[i] == '/') {                                                                        // Divide
            _tokenList.push_back({"Divide", TokenType::DIV});                                
        }
        else if (_sourceCode[i] == '*') {                                                                        // Multiply
            _tokenList.push_back({"Multiply", TokenType::MUL});                                
        }
        else if (_sourceCode[i] == ',') {                                                                        // Comma
            _tokenList.push_back({"Comma", TokenType::COMMA});                                      
        }
        else if (_sourceCode[i] == '<') {                                                                        // Include Arguements
            _buf.clear();
            i++;

            while (i < _sourceCode.length() && _sourceCode[i] != '>') {
                _buf.push_back(_sourceCode[i]);
                i++;
            }

            //_tokenList.push_back({_buf, TokenType::ARGUEMENT});
        }
        else if (_sourceCode[i] == '\'') {                                                                       // Char
            _buf.clear();
            i++;

            while (i < _sourceCode.length() && (_sourceCode[i] != '\'' || _sourceCode[i-1] == '\\')) {
                // Handle the escape sequence for single quote
                if (_sourceCode[i] == '\\' && i + 1 < _sourceCode.length() && _sourceCode[i+1] == '\'') {
                    _buf.push_back('\'');
                    i++;
                } else _buf.push_back(_sourceCode[i]);
                i++;
            }

            _tokenList.push_back({_buf, TokenType::CHAR});
        }
        else if (_sourceCode[i] == '"') {                                                                        // String  
            _buf.clear();
            i++;

            while (i < _sourceCode.length() && (_sourceCode[i] != '"' || _sourceCode[i-1] == '\\')) {
                // Handle the escape sequence for double quote
                if (_sourceCode[i] == '\\' && i + 1 < _sourceCode.length() && _sourceCode[i+1] == '"') {
                    _buf.push_back('"');
                    i++;
                } else _buf.push_back(_sourceCode[i]);
                i++;
            }

            _tokenList.push_back({_buf, TokenType::STRING});
        }
        else if (_sourceCode[i] == '$') {                                                                        // Hex
            _buf.clear();
            i++;

            while (i < _sourceCode.length() && std::isalnum(_sourceCode[i])) {
                _buf.push_back(_sourceCode[i]);
                i++;
            }
            i--;
            _tokenList.push_back({_buf, TokenType::HEX});
        }
        else if (_sourceCode[i] == '%') {                                                                        // Binary
            _buf.clear();
            i++;

            while (i < _sourceCode.length() && std::isalnum(_sourceCode[i])) {
                _buf.push_back(_sourceCode[i]);
                i++;
            }
            i--;
            _tokenList.push_back({_buf, TokenType::BINARY});
        }
        else if (std::isdigit(_sourceCode[i])) {                                                                 // Number
            _buf.clear();
            while (i < _sourceCode.length() && std::isdigit(_sourceCode[i])) {
                _buf.push_back(_sourceCode[i]);
                i++;
            }
            i--;

            _tokenList.push_back({_buf, TokenType::NUMBER});
        }
        else if (std::isspace(_sourceCode[i]) && _sourceCode[i] != '\n') {                                       // Whitespace
            while (i < _sourceCode.length() && std::isspace(_sourceCode[i]) && _sourceCode[i] != '\n') i++;
            i--;
            //_tokenList.push_back({"Whitespace", TokenType::WHITESPACE, _lineNumber});
        }
        else if (_sourceCode[i] == '\n') {                                                                       // Newline
            //_tokenList.push_back({"Newline", TokenType::NEWLINE});
        }
    
    }
};
