#include "parser.hpp"
#include "lexer.hpp"

Parser::Parser(Lexer& lexer, const std::vector<Instruction>& instructionSet)
    : _lexer(lexer), _instructionSet(instructionSet) {
}

void Parser::preprocess_statment() {
    if (_currToken.substring == "org") {
        _currToken = _nextToken;
        if (_currToken.type != TokenType::HEX || _currToken.type != TokenType::BINARY || _currToken.type != TokenType::NUMBER) {
            std::cerr << "No directive for .org" << std::endl;
            exit(ERROR);
        }
    }
}

void Parser::parse() {
    _currToken = _nextToken;

    while (_lexer.hasToken()) {
        _currToken = _nextToken;
        switch (_currToken.type) {
            case TokenType::PREPROCESS:
                preprocess_statment();
                break;
        }
    }
}
