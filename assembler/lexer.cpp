#include "lexer.hpp"

void Lexer::print() {
    for (size_t i = 0; i < _tokenList.size(); i++) {
        std::cout << 
        " TOKEN TYPE: " << _tokenList[i].type << 
        " TOKEN STRING: " << _tokenList[i].substring << 
        std::endl;
    }
}

void Lexer::_resetTokenList() {
    _tokenIndex = 0;
}

bool Lexer::hasToken() {
    if (_tokenIndex >= _tokenList.size()) return false;
    return true;
}

Token Lexer::peekNextToken() {
    if (!hasToken()) _resetTokenList();
    return _tokenList[_tokenIndex];
}

std::shared_ptr<Token> Lexer::getToken() {
    if (!hasToken()) _resetTokenList();
    return std::make_shared<Token>(_tokenList[_tokenIndex++]);
}

bool Lexer::_isInInstructionSet() {
    for (size_t i = 0; i < _instructionSet.size(); i++) 
        if (_buf == _instructionSet[i].name) return true;
    return false;
}

bool Lexer::_isInList(const std::vector<Token>& list, const Token& token) {
    for (size_t i = 0; i < list.size(); i++) {
        if (token.substring == list[i].substring) return true;
    }

    return false;
}

void Lexer::_sortLabels() {
    std::vector<Token> labelDeclare; 

    // Get Labels which have been declared
    for (size_t i = 0; i < _tokenList.size(); i++) {
        if (_tokenList[i].type == TokenType::LABEL_DECLARE) labelDeclare.push_back(_tokenList[i]);
    }

    // Change all label used tokens from IDENTIFIER to LABEL
    for (size_t i = 0; i < _tokenList.size(); i++) {
        if (_tokenList[i].type == TokenType::IDENTIFIER && _isInList(labelDeclare, _tokenList[i])) {
            _tokenList[i].type = TokenType::LABEL;
        }
    }
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

            if(_buf == "db" || _buf == "tx") {
                _tokenList.push_back({_buf, TokenType::DIRECTIVE});
            } else if (_buf == "org") {
                _tokenList.push_back({_buf, TokenType::ORG});
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
            _tokenList.push_back({"=", TokenType::EQUAL});
        }
        else if (_sourceCode[i] == '#') {                                                                        // Immediate
            _tokenList.push_back({"#", TokenType::IMMEDIATE});                              
        }
        else if (_sourceCode[i] == '(') {                                                                        // Left Paren
            _tokenList.push_back({"(", TokenType::L_PAREN});                              
        }
        else if (_sourceCode[i] == ')') {                                                                        // Right Paren
            _tokenList.push_back({")", TokenType::R_PAREN});                              
        }
        else if (_sourceCode[i] == '-') {                                                                        // Minus
            _tokenList.push_back({"-", TokenType::MINUS});                                
        }
        else if (_sourceCode[i] == '+') {                                                                        // Plus
            _tokenList.push_back({"+", TokenType::PLUS});                                
        }
        else if (_sourceCode[i] == '/') {                                                                        // Divide
            _tokenList.push_back({"/", TokenType::DIV});                                
        }
        else if (_sourceCode[i] == '*') {                                                                        // Multiply
            _tokenList.push_back({"*", TokenType::MUL});                                
        }
        else if (_sourceCode[i] == ',') {                                                                        // Comma
            _tokenList.push_back({",", TokenType::COMMA});                                      
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
            while (i < _sourceCode.length() && (std::isdigit(_sourceCode[i]) || _sourceCode[i] == '.')) {
                if (_sourceCode[i] == '.') {
                    // Error handling for decimal point
                    std::cerr << "Error: Unexpected decimal point in number." << std::endl;
                    exit(ERROR::FLOAT_ERROR);
                }

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
            _tokenList.push_back({"Newline", TokenType::NEWLINE});
        }
    
    }

    _sortLabels();
};
