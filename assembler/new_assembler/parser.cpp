#include "parser.hpp"
#include "lexer.hpp"

Parser::Parser(Lexer lexer, const std::vector<Instruction>& instructionSet) : _lexer(lexer), _instructionSet(instructionSet) {
    // Setup Root Node
    _rootNode = new ASTNode(nullptr);
    _rootNode->data = new Token;
    _rootNode->data->type = TokenType::START;
    _rootNode->data->substring = "PROGRAM ENTRY";
}

void Parser::_printAST(ASTNode* node, int depth) {
    if (node == nullptr) {
        return;
    }

    std::string indent(depth * 2, ' ');  // 2 spaces per depth level
    std::string contentIndent = indent + "  ";

    // Start of node
    std::cout << indent << "{\n";

    // Node content
    std::cout << contentIndent << "\"data\": ";
    if (node->data != nullptr) {
        std::cout << "\"" << node->data->substring << "\"";
    } else std::cout << "null";

    // Children
    if (!node->children.empty()) {
        std::cout << ",\n" << contentIndent << "\"child\": [";
        for (size_t i = 0; i < node->children.size(); ++i) {
            if (i != 0) {
                std::cout << ", ";
            }
            std::cout << "\n";
            _printAST(node->children[i], depth + 2);  // Increase depth for children
        }
        std::cout << "\n" << contentIndent << "]";
    }

    // End of node
    std::cout << "\n" << indent << "}";
}

ASTNode* Parser::_parseDirective() {
    ASTNode* directiveNode = new ASTNode(_currToken);

    if (_currToken->substring == "org") {                                // Handle .org directive
        _advanceToken();

        // Check for Errors
        if (_currToken->type != TokenType::NUMBER && _currToken->type != TokenType::HEX && _currToken->type != TokenType::BINARY) {
            std::cerr << "Error: invalid org directive format" << std::endl;
            exit(ERROR::ORG_ERROR);
        }

        ASTNode* addressNode = new ASTNode(_currToken);
        directiveNode->children.push_back(addressNode);
    } 
    else if (_currToken->substring == "db") {                            // Handle .db directive
        while (_hasToken()) {
            const Token& nextToken = _peekNextToken();

            if (nextToken.type != TokenType::NUMBER && nextToken.type != TokenType::HEX && nextToken.type != TokenType::BINARY && nextToken.type != TokenType::CHAR) {
                break; // Stop when a non-numeric token is encountered
            }
            
            _advanceToken();
            ASTNode* byteNode = new ASTNode(_currToken);
            directiveNode->children.push_back(byteNode);
            
        }
    } 
    else if (_currToken->substring == "tx") {                            // Handle .tx directive
        _advanceToken(); // Advance to the string token

        // Check for Errors
        if (_currToken->type != TokenType::STRING) {
            std::cerr << "Error: tx directive is invalid" << std::endl;
            exit(ERROR::STRING_ERROR);
        }

        ASTNode* stringNode = new ASTNode(_currToken);
        directiveNode->children.push_back(stringNode);
    }

    return directiveNode;
}

ASTNode* Parser::_parseVariableAssignment() {
    ASTNode* varNode = new ASTNode(_currToken);  // Variable name
    _advanceToken();

    if (_currToken->type != TokenType::EQUAL) {
        std::cerr << "Error: invalid variable assignment format" << std::endl;
        exit(ERROR::ASSIGNMENT_ERROR);
    }
    ASTNode* assignmentNode = new ASTNode(_currToken);

    _advanceToken();

    ASTNode* exprNode = _parseMathExpression();  // Parse the math expression
    assignmentNode->children.push_back(exprNode);
    varNode->children.push_back(assignmentNode);

    return varNode;
}

ASTNode* Parser::_parseMathExpression() {
    return _parseAdditionSubtraction();
}

ASTNode* Parser::_parseAdditionSubtraction() {
    ASTNode* left = _parseMultiplicationDivision();

    while (_currToken->type == TokenType::PLUS || _currToken->type == TokenType::MINUS) {
        ASTNode* newParent = new ASTNode(_currToken);

        _advanceToken();
        ASTNode* right = _parseMultiplicationDivision();
        newParent->children.push_back(left);  // The left-hand side becomes the left child
        newParent->children.push_back(right); // The right-hand side becomes the right child

        left = newParent;
    }

    return left; // Return the root of the built subtree
}

ASTNode* Parser::_parseMultiplicationDivision() {
    ASTNode* left = _parsePrimary();

    while (_currToken->type == TokenType::MUL || _currToken->type == TokenType::DIV) {
        ASTNode* newParent = new ASTNode(_currToken);

        _advanceToken();
        ASTNode* right = _parseMultiplicationDivision();
        newParent->children.push_back(left);  // The left-hand side becomes the left child
        newParent->children.push_back(right); // The right-hand side becomes the right child

        left = newParent;
    }
    return left; // Return the root of the built subtree
}

ASTNode* Parser::_parsePrimary() {
    // Handle primary expressions (numbers, parentheses, etc.)
    if (_currToken->type == TokenType::NUMBER || _currToken->type == TokenType::HEX || _currToken->type == TokenType::BINARY || _currToken->type == TokenType::CHAR) {
        ASTNode* node = new ASTNode(_currToken);

        // Only advance token if there if a math expression following number
        const Token& temp = _peekNextToken();
        if (temp.type == TokenType::MUL || temp.type == TokenType::DIV || temp.type == TokenType::PLUS || temp.type == TokenType::MINUS) 
            _advanceToken();

        return node;

    } else if (_currToken->type == TokenType::L_PAREN) {
        _advanceToken();
        ASTNode* node = _parseMathExpression();
        if (_currToken->type != TokenType::R_PAREN) {
            std::cerr << "Error: parentheses error" << std::endl;
            exit(ERROR::PAREN_ERROR);
        }
        _advanceToken();  // Skip closing parenthesis
        return node;
    } else {
            std::cerr << "Error: unexpected token in variable assigment" << std::endl;
            exit(ERROR::UNEXP_TOKEN_ERROR);
    }
}

ASTNode* Parser::_parseInstruction() {
    ASTNode* instructionNode = new ASTNode(_currToken);

    do {
        switch (_peekNextToken().type) {
            case TokenType::NUMBER:
                _advanceToken();
                instructionNode->children.push_back(new ASTNode(_currToken));
                break;
            case TokenType::COMMA:
                _advanceToken();
                instructionNode->children.push_back(new ASTNode(_currToken));
                break;
            case TokenType::REG:
                _advanceToken();
                instructionNode->children.push_back(new ASTNode(_currToken));
                break;
            case TokenType::IMMEDIATE:
                _advanceToken();
                instructionNode->children.push_back(new ASTNode(_currToken));
                break;
            default: 
                return instructionNode;
        }
    }
    while (_hasToken() && _peekNextToken().type != TokenType::INSTRUCTION);   

    return instructionNode;
}

ASTNode* Parser::_parseLabel() {

    // Create a new label node
    ASTNode* labelNode = new ASTNode(_currToken);
    _advanceToken();

    // Parse subsequent instructions and add them as children to the label node
    while (_hasToken()) {
        //ASTNode* instructionNode = _parseInstruction();
        //labelNode->children.push_back(instructionNode);
    }

    return labelNode;
}

ASTNode* Parser::_parseStatement() {
    switch (_currToken->type) {
        case TokenType::DIRECTIVE:
            return _parseDirective();
        case TokenType::IDENTIFIER:
            return _parseVariableAssignment();
        case TokenType::INSTRUCTION:
            return _parseInstruction();
        default:
            return nullptr;
    }
}

void Parser::parseProgram() {

    while (_hasToken()) {
        _advanceToken();
        _rootNode->children.push_back(_parseStatement());
    }
}
