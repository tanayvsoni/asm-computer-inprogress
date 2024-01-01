#include "codegen.hpp"

void CodeGen::_generateCodeForOrg(const std::shared_ptr<ASTNode>& node) {

    _address = _convertToInt(node);
    if (_address < OFFSET || _address > MAX_MEMORY) {
        std::cerr << "Error: org value is out of bounds" << std::endl;
        exit(ORG_ERROR);
    }
}

void CodeGen::_generateCodeForVar(const std::shared_ptr<ASTNode>& node) {
    
}

void CodeGen::_generateCodeFromNode(const std::shared_ptr<ASTNode>& node) {
    if (!node) return;

    switch (node->data->type) {
        case TokenType::ORG:
            _generateCodeForOrg(node);
            break;
        case TokenType::IDENTIFIER:
            _generateCodeForVar(node);
            break;
        default:
            break;
    }

    // If the node has children, traverse them
    for (const auto& child : node->children) {
        _generateCodeFromNode(child);
    }
}

int CodeGen::_convertToInt(const std::shared_ptr<ASTNode>& node) {
    switch (node->value->type) {
        case TokenType::NUMBER:
            return std::stoi(node->value->substring, nullptr, 10);

        case TokenType::HEX:
            return std::stoi(node->value->substring, nullptr, 16);
    
        case TokenType::BINARY:
            return std::stoi(node->value->substring, nullptr, 2);

        case TokenType::CHAR:
            return static_cast<int>(node->value->substring[0]);

        case TokenType::IDENTIFIER:
            break;
    
        default:
            break;
    }
}

void CodeGen::generateCode() {
    
    if (!_ast || _ast->children.empty()) return;

    // Ensure AST's first node is a org with a valid
    std::shared_ptr<ASTNode> firstChild = _ast->children.front();

    if (firstChild->data->type != TokenType::ORG) {
        std::cerr << "Error: First child of the root is not an 'org'. Code generation aborted." << std::endl;
        exit(ORG_ERROR);
    }

    // Now generate code
    _generateCodeFromNode(_ast);
}