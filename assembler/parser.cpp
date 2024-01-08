#include "parser.hpp"

Parser::Parser(const Lexer& lexer): _lexer(lexer) {
    // Setup Root Node
    rootNode = std::make_unique<ASTNode>(nullptr);
    rootNode->data = std::make_unique<Token>();
    rootNode->data->substring = "PROGRAM ENTRY";
}

void Parser::_printAST(std::shared_ptr<ASTNode> node, int depth) {
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

    // Value
    if (node->value != nullptr) {
        std::cout << ",\n" << contentIndent << "\"value\": ";
        std::cout << "\"" << node->value->substring << "\"";
    }

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

std::unique_ptr<ASTNode> Parser::_parseOrg() {
    std::unique_ptr<ASTNode> orgNode = std::make_unique<ASTNode>(std::make_unique<Token>(*_currToken));

    _advanceToken();
    // Check for Errors
    if (_currToken->type != TokenType::NUMBER && _currToken->type != TokenType::HEX && _currToken->type != TokenType::BINARY) {
        std::cerr << "Error: invalid org directive format" << std::endl;
        exit(ERROR::ORG_ERROR);
    }

    //Set value of org
    orgNode->value = std::make_unique<Token>(std::move(*_currToken));

    while (_hasToken()) {
        if (_peekNextToken().type == TokenType::ORG) break;
        _advanceToken();
        if (_currToken->type == TokenType::NEWLINE) continue;
        orgNode->children.push_back(std::move(_parseStatement()));
    }

    return orgNode;
}

std::unique_ptr<ASTNode> Parser::_parseDirective() {
    std::unique_ptr<ASTNode> directiveNode = std::make_unique<ASTNode>(std::make_unique<Token>(*_currToken));

    if (_currToken->substring == "db") {                                // Handle .db directive
        while (_hasToken()) {
            const Token& nextToken = _peekNextToken();

            if (nextToken.type != TokenType::NUMBER && nextToken.type != TokenType::HEX && nextToken.type != TokenType::BINARY && nextToken.type != TokenType::CHAR) {
                break; // Stop when a non-numeric token is encountered
            }
            
            _advanceToken();
            std::unique_ptr<ASTNode> byteNode = std::make_unique<ASTNode>(std::make_unique<Token>(*_currToken));
            directiveNode->children.push_back(std::move(byteNode));
            
        }
    } 
    else if (_currToken->substring == "tx") {                            // Handle .tx directive
        _advanceToken(); // Advance to the string token

        // Check for Errors
        if (_currToken->type != TokenType::STRING) {
            std::cerr << "Error: tx directive is invalid" << std::endl;
            exit(ERROR::STRING_ERROR);
        }

        directiveNode->value = std::make_unique<Token>(*_currToken);
    }

    return directiveNode;
}

std::unique_ptr<ASTNode> Parser::_parseVariableAssignment() {
    std::unique_ptr<ASTNode> varNode = std::make_unique<ASTNode>(std::make_unique<Token>(*_currToken));  // Variable name
    _advanceToken();

    if (_currToken->type != TokenType::EQUAL) {
        std::cerr << "Error: invalid variable assignment format" << std::endl;
        exit(ERROR::ASSIGNMENT_ERROR);
    }
    //std::unique_ptr<ASTNode> assignmentNode = std::make_unique<ASTNode>(std::make_unique<Token>(*_currToken));

    _advanceToken();

    std::unique_ptr<ASTNode> exprNode = _parseMathExpression();  // Parse the math expression
    //assignmentNode->children.push_back(std::move(exprNode));
    //varNode->children.push_back(std::move(assignmentNode));
    varNode->children.push_back(std::move(exprNode));

    return varNode;
}

std::unique_ptr<ASTNode> Parser::_parseMathExpression() {
    return _parseAdditionSubtraction();
}

std::unique_ptr<ASTNode> Parser::_parseAdditionSubtraction() {
    std::unique_ptr<ASTNode> left = _parseMultiplicationDivision();

    while (_currToken->type == TokenType::PLUS || _currToken->type == TokenType::MINUS) {
        std::unique_ptr<ASTNode> newParent = std::make_unique<ASTNode>(std::make_unique<Token>(*_currToken));

        _advanceToken();
        std::unique_ptr<ASTNode> right = _parseMultiplicationDivision();
        newParent->children.push_back(std::move(left));  // The left-hand side becomes the left child
        newParent->children.push_back(std::move(right)); // The right-hand side becomes the right child

        left = std::move(newParent); 
    }

    return left; // Return the root of the built subtree
}

std::unique_ptr<ASTNode> Parser::_parseMultiplicationDivision() {
    std::unique_ptr<ASTNode> left = _parsePrimary();

    while (_currToken->type == TokenType::MUL || _currToken->type == TokenType::DIV) {
        std::unique_ptr<ASTNode> newParent = std::make_unique<ASTNode>(std::make_unique<Token>(*_currToken));

        _advanceToken();
        std::unique_ptr<ASTNode> right = _parseMultiplicationDivision();
        newParent->children.push_back(std::move(left));  // The left-hand side becomes the left child
        newParent->children.push_back(std::move(right)); // The right-hand side becomes the right child

        left = std::move(newParent); 
    }
    return left; // Return the root of the built subtree
}

std::unique_ptr<ASTNode> Parser::_parsePrimary() {
    // Handle primary expressions (numbers, parentheses, etc.)
    if (_currToken->type == TokenType::NUMBER || _currToken->type == TokenType::HEX || _currToken->type == TokenType::BINARY || _currToken->type == TokenType::CHAR || _currToken->type == TokenType::IDENTIFIER) {
        std::unique_ptr<ASTNode> node = std::make_unique<ASTNode>(std::make_unique<Token>(*_currToken));

        // Only advance token if there if a math expression following number
        const Token& temp = _peekNextToken();
        if (temp.type == TokenType::MUL || temp.type == TokenType::DIV || temp.type == TokenType::PLUS || 
            temp.type == TokenType::MINUS || temp.type == TokenType::L_PAREN || temp.type == TokenType::R_PAREN || temp.type == TokenType::IDENTIFIER) 
            _advanceToken();

        return node;

    } else if (_currToken->type == TokenType::L_PAREN) {
        _advanceToken();
        std::unique_ptr<ASTNode> node = _parseMathExpression();
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

std::unique_ptr<ASTNode> Parser::_parseInstructionPrimary() { 

    if (_currToken->type == TokenType::L_PAREN) {
        _advanceToken();
        Token bracketToken = {"BRACKET", TokenType::BRACKET};
        std::unique_ptr<ASTNode> bracketNode = std::make_unique<ASTNode>(std::make_unique<Token>(bracketToken));

        while (_currToken->type != TokenType::R_PAREN) {
            if (!_hasToken()) {
                std::cerr << "Error: Missing closing parenthesis" << std::endl;
                exit(ERROR::PAREN_ERROR);
            }
            bracketNode->children.push_back(std::move(_parseInstructionPrimary()));
            _advanceToken();
        }

        _advanceToken();
        return bracketNode;
    } 
    else if (_currToken->type == TokenType::COMMA) {
        _advanceToken();
        Token commaToken = {"COMMA", TokenType::COMMA};
        std::unique_ptr<ASTNode> commaNode = std::make_unique<ASTNode>(std::make_unique<Token>(commaToken));
        commaNode->children.push_back(std::move(_parseInstructionPrimary()));
        
        return commaNode;
    } 
    else if (_currToken->type == TokenType::MINUS) {
        _advanceToken();
        _currToken->substring = "-" + _currToken->substring;
        return std::make_unique<ASTNode>(std::make_unique<Token>(*_currToken));
    }  
    else {
        return std::make_unique<ASTNode>(std::make_unique<Token>(*_currToken));
    }

}

std::unique_ptr<ASTNode> Parser::_parseInstruction() {
    std::unique_ptr<ASTNode> instructionNode = std::make_unique<ASTNode>(std::make_unique<Token>(*_currToken));
    
    while (_hasToken() && _currToken->type != TokenType::NEWLINE && _peekNextToken().type != TokenType::NEWLINE) {
        if (_currToken->type != TokenType::COMMA) _advanceToken();
        instructionNode->children.push_back(std::move(_parseInstructionPrimary()));
    }

    
    return instructionNode;
}

std::unique_ptr<ASTNode> Parser::_parseLabel() {

    // Create a new label node
    std::unique_ptr<ASTNode> labelNode = std::make_unique<ASTNode>(std::make_unique<Token>(*_currToken));

    // Parse subsequent instructions and add them as children to the label node
    while (_hasToken()) {
        if (_peekNextToken().type == TokenType::ORG) break;
        if (_peekNextToken().type == TokenType::LABEL_DECLARE) break;
        if (_peekNextToken().type == TokenType::IDENTIFIER) break;
        _advanceToken();
        if (_currToken->type == TokenType::NEWLINE) continue;

        labelNode->children.push_back(std::move(_parseStatement()));
    }

    return labelNode;
}

std::unique_ptr<ASTNode> Parser::_parseStatement() {
    switch (_currToken->type) {
        case TokenType::ORG:
            return _parseOrg();
        case TokenType::DIRECTIVE:
            return _parseDirective();
        case TokenType::IDENTIFIER:
            return _parseVariableAssignment();
        case TokenType::INSTRUCTION:
            return _parseInstruction();
        case TokenType::LABEL_DECLARE:
            return _parseLabel();
        default:
            return nullptr;
    }
}

std::shared_ptr<ASTNode> Parser::_findAndRemoveMainLabelNode(std::shared_ptr<ASTNode>& node) {
    if (!node) return nullptr;

    for (size_t i = 0; i < node->children.size(); ++i) {
        if (node->children[i]->data->substring == "main") {
            std::shared_ptr<ASTNode> mainNode = node->children[i];
            node->children.erase(node->children.begin() + i);
            return mainNode;
        }
        auto childResult = _findAndRemoveMainLabelNode(node->children[i]);
        if (childResult) return childResult;
    }

    return nullptr;
}

void Parser::parseProgram() {

    while (_hasToken()) {
        _advanceToken();
        if (_currToken->type == TokenType::NEWLINE) continue;
        rootNode->children.push_back(std::move(_parseStatement()));
    }

    std::shared_ptr<ASTNode> mainNode = _findAndRemoveMainLabelNode(rootNode);

    if (mainNode) {
        for (auto& child : rootNode->children) {
            if (child->data->type == TokenType::ORG && child->value->substring == "4000") {
                child->children.insert(child->children.begin(), mainNode);
                break;
            } 
        }
    } else {
        std::cerr << "Error: no main function" << std::endl;
        exit(ERROR::MAIN_ERROR);
    }
}
