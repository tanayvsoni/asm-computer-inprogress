#include "codegen.hpp"

// Helper Functions

int CodeGen::_convertToInt(const std::unique_ptr<Token>& token) {
    switch (token->type) {
        case TokenType::NUMBER:
            return std::stoi(token->substring, nullptr, 10);

        case TokenType::HEX:
            return std::stoi(token->substring, nullptr, 16);
    
        case TokenType::BINARY:
            return std::stoi(token->substring, nullptr, 2);

        case TokenType::CHAR:
            return static_cast<int>(token->substring[0]);

        case TokenType::IDENTIFIER:
            for (const auto& element : _varTable) {
                if (element.name == token->substring) return element.value;
            }
            std::cerr << "Error: Variable used but not declared" << std::endl;
            exit(ERROR::VAR_ERROR);

        case TokenType::LABEL:
            _labelReplacementLocation.push_back({_address+1, token->substring});
            return 0xffff;

        default:
            break;
    }

    std::cerr << "Error: Conversion error." << std::endl;
    exit(ERROR::CONVER_ERROR);
}

int CodeGen::_evaluateExpression(const std::shared_ptr<ASTNode>& node) {

    
    if (node->data->type == TokenType::NUMBER || node->data->type == TokenType::HEX || node->data->type == TokenType::BINARY || 
        node->data->type == TokenType::CHAR || node->data->type == TokenType::IDENTIFIER) {
            return _convertToInt(node->data);
    }

    if (node->data->type == TokenType::PLUS) {
        return _evaluateExpression(node->children[0]) + _evaluateExpression(node->children[1]);
    }
    else if (node->data->type == TokenType::MINUS) {
        return _evaluateExpression(node->children[0]) - _evaluateExpression(node->children[1]);
    }
    else if (node->data->type == TokenType::MUL) {
        return _evaluateExpression(node->children[0]) * _evaluateExpression(node->children[1]);
    } 
    else if (node->data->type == TokenType::DIV) {
        int right = _evaluateExpression(node->children[1]);
        if (right == 0) {
            std::cerr << "Error: zero in denominator" << std::endl;
            exit(ERROR::ZERO_ERROR);
        }
        return floor(_evaluateExpression(node->children[0]) / right);
    }

    std::cerr << "Error: Unknown operator" << std::endl;
    exit(ERROR::OP_ERROR);
}

void CodeGen::_updateSymbolTable(std::vector<_SymbolTable>& table, const std::string& name, const int& value) {
    for (auto& element : table) {
        if (element.name == name) {
            element.value = value;
            return;
        }
    }

    table.push_back({name, value});
}

int CodeGen::_getOpcode(const std::string& name, const std::string& addressing_mode) {
    for (const Instruction& instr : _instructionsSet) {
        if (instr.name == name && instr.addr_mode == addressing_mode) return instr.opcode;
    }

    std::cerr << "Error: not a valid instructon or addressing mode" << std::endl;
    exit(ERROR::INSTR_ERROR);
}

std::string CodeGen::_getReg(const std::shared_ptr<ASTNode>& node) {
    if (node->children.empty()) {
        std::cerr << "Error: No register provided" << std::endl;
        exit(ERROR::REG_ERROR);
    }
    else if (node->children.size() != 1) {
        std::cerr << "Error: Too many arguements after comma" << std::endl;
        exit(ERROR::SYNTAX_ERROR);
    } 
    else if (node->children[0]->data->substring != "X" && node->children[0]->data->substring != "Y") {
        std::cerr << "Error: Invalid register" << std::endl;
        exit(ERROR::REG_ERROR);
    }

    return node->children[0]->data->substring;
}

int CodeGen::_findLabelVal(const std::string& name) {
    for (const auto& label : _labelTable) {
        if (label.name == name) return label.value;
    }

    std::cerr << "Error: label used but not found" << std::endl;
    exit(ERROR::LABEL_ERROR);
}

// Assigment Functions

void CodeGen::_orgAssigment(const std::shared_ptr<ASTNode>& node) {

    _address = _convertToInt(node->value);
    if (_address < OFFSET || _address > MAX_MEMORY) {
        std::cerr << "Error: org value is out of bounds" << std::endl;
        exit(ERROR::ORG_ERROR);
    }

    //std::cout << _address << std::endl;
}

void CodeGen::_directiveAssignment(const std::shared_ptr<ASTNode>& node) {
    if (node->data->substring == "tx") {
        for (const char& c: node->value->substring) {
            _machineCode[_address++] = static_cast<uint8_t>(c); 
        }

        _machineCode[_address++] = 0;
    }
    else if (node->data->substring == "db") {
        for (const auto& child : node->children) {
            _machineCode[_address++] = static_cast<uint8_t>(_convertToInt(child->data)); 
        }
    }
}

void CodeGen::_labelAssignment(const std::shared_ptr<ASTNode>& node) {
    _updateSymbolTable(_labelTable, node->data->substring, _address);
}

void CodeGen::_varAssignment(const std::shared_ptr<ASTNode>& node) {
    std::string varName = node->data->substring;
    int varValue = _evaluateExpression(node->children[0]);

    // Add to or update the variable in the symbol table
    _updateSymbolTable(_varTable, varName, varValue);
    
}

void CodeGen::_instructionCode(const std::shared_ptr<ASTNode>& node) {
    const std::string name = node->data->substring;
    std::string addressing_mode;
    int opcode = 0;
    int operand_num = 0;
    auto operand = node->children; 

    if (operand.empty()) {                                                                                                      // Implied
        
        addressing_mode = "implied";
        opcode =_getOpcode(name, addressing_mode);
        _machineCode[_address++] = static_cast<uint8_t>(opcode);
    } 
    else if (operand[0]->data->type == TokenType::IMMEDIATE) {                                                                  // Immediate
               
        // Error Checking 
        if (operand.size() > 2) {
            std::cerr << "Error: Invalid immediate operand arguement" << std::endl;
            exit(ERROR::OPERAND_ERROR);
        }

        if (operand[1]->data->type == TokenType::LABEL) {
            std::cerr << "Error: Label can not be used as arguement for immediate" << std::endl;
            exit(ERROR::SYNTAX_ERROR);
        }

        // Decode instruction
        operand_num = _convertToInt(operand[1]->data);

        if (operand_num > 0xff) {
            std::cerr << "Error: Number must be 8 bit long for immediate" << std::endl;
            exit(ERROR::SYNTAX_ERROR);
        }

        addressing_mode = "immediate";
        opcode =_getOpcode(name, addressing_mode);
        _machineCode[_address++] = static_cast<uint8_t>(opcode);
        _machineCode[_address++] = static_cast<uint8_t>(operand_num);

    }
    else if (operand[0]->data->type != TokenType::BRACKET && operand.size() == 1) {                                             // Zeropage/Absolute
        operand_num = _convertToInt(operand[0]->data);
    
        // Figure out if it is zeropage or not
        if (operand_num > 0xff && operand_num <= 0xffff) {                                                      // Absolute
            addressing_mode = "absolute";
            opcode =_getOpcode(name, addressing_mode);
            _machineCode[_address++] = static_cast<uint8_t>(opcode);
            _machineCode[_address++] = static_cast<uint8_t>(operand_num);
            _machineCode[_address++] = static_cast<uint8_t>(operand_num >> 8);
        }
        else if (operand_num <= 0xff) {                                                                         // Zeropage
            addressing_mode = "zeropage";
            opcode =_getOpcode(name, addressing_mode);

            _machineCode[_address++] = static_cast<uint8_t>(opcode);
            _machineCode[_address++] = static_cast<uint8_t>(operand_num);
        } 
        else {
            std::cerr << "Error: Number can only be 16 bits long" << std::endl;
            exit(ERROR::SYNTAX_ERROR);
        }

    }
    else if (operand[0]->data->type != TokenType::BRACKET && operand[1]->data->type == TokenType::COMMA) {                      // Zeropage/Absolute , X/Y
        operand_num = _convertToInt(operand[0]->data);

        // Figure out if it is zeropage or not
        if (operand_num > 0xff && operand_num <= 0xffff) {                                                      // Absolute
            addressing_mode = "absolute," + _getReg(operand[1]);
            opcode =_getOpcode(name, addressing_mode);

            _machineCode[_address++] = static_cast<uint8_t>(opcode);
            _machineCode[_address++] = static_cast<uint8_t>(operand_num);
            _machineCode[_address++] = static_cast<uint8_t>(operand_num >> 8);
        }
        else if (operand_num <= 0xff) {                                                                         // Zeropage
            addressing_mode = "zeropage," + _getReg(operand[1]);
            opcode =_getOpcode(name, addressing_mode);

            _machineCode[_address++] = static_cast<uint8_t>(opcode);
            _machineCode[_address++] = static_cast<uint8_t>(operand_num);
        } 
        else {
            std::cerr << "Error: Number can only be 16 bits long" << std::endl;
            exit(ERROR::SYNTAX_ERROR);
        }

    }
    else if (operand[0]->data->type == TokenType::BRACKET && operand.size() == 1 && operand[0]->children.size() == 1) {         // (indirect)
        
        operand_num = _convertToInt(operand[0]->children[0]->data);

        addressing_mode = "(indirect)";
        opcode =_getOpcode(name, addressing_mode);
        _machineCode[_address++] = static_cast<uint8_t>(opcode);
        _machineCode[_address++] = static_cast<uint8_t>(operand_num);
        _machineCode[_address++] = static_cast<uint8_t>(operand_num >> 8);

    }
    else if (operand[0]->data->type == TokenType::BRACKET && operand.size() == 1) {                                             // (indirect , X/Y)
        auto bracketNodeChildren = operand[0]->children;
        auto commaNode = bracketNodeChildren[1];

        operand_num = _convertToInt(bracketNodeChildren[0]->data);
        addressing_mode = "(indirect," + _getReg(commaNode) + ")";
        opcode =_getOpcode(name, addressing_mode);

        _machineCode[_address++] = static_cast<uint8_t>(opcode);
        _machineCode[_address++] = static_cast<uint8_t>(operand_num);
        _machineCode[_address++] = static_cast<uint8_t>(operand_num >> 8);
    }
    else if (operand[0]->data->type == TokenType::BRACKET && operand[1]->data->type == TokenType::COMMA) {                      // (indirect) , X/Y
        auto bracketNodeChildren = operand[0]->children;
        auto commaNode = operand[1];

        operand_num = _convertToInt(bracketNodeChildren[0]->data);
        
        addressing_mode = "(indirect)," + _getReg(commaNode);
        opcode =_getOpcode(name, addressing_mode);

        _machineCode[_address++] = static_cast<uint8_t>(opcode);
        _machineCode[_address++] = static_cast<uint8_t>(operand_num);
        _machineCode[_address++] = static_cast<uint8_t>(operand_num >> 8);
    }
}

// Main Functions

void CodeGen::printFile(const std::string& outputPath) {
    std::ofstream outFile(outputPath, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error opening file for writing." << std::endl;
        return;
    }
    outFile.write(reinterpret_cast<const char*>(&_machineCode[OFFSET]), MAX_MEMORY - OFFSET + 1);
}

void CodeGen::_updateLabels() {

    for (auto element : _labelReplacementLocation) {
        _address = element.first;
        int value = _findLabelVal(element.second);

        _machineCode[_address++] = static_cast<uint8_t>(value);
        _machineCode[_address++] = static_cast<uint8_t>(value >> 8);
    }
}

void CodeGen::_generateNodeCode(const std::shared_ptr<ASTNode>& node) {
    if (!node) return;

    switch (node->data->type) {
        case TokenType::ORG:
            _orgAssigment(node);
            break;
        case TokenType::DIRECTIVE:
            _directiveAssignment(node);
            break;
        case TokenType::LABEL_DECLARE:
            _labelAssignment(node);
            break; 
        case TokenType::IDENTIFIER:
            if (!node->children.empty()) _varAssignment(node);
            break;
        case TokenType::INSTRUCTION:
            _instructionCode(node);
            return;
        default:
            break;
    }

    // If the node has children, traverse them
    for (const auto& child : node->children) {
        _generateNodeCode(child);
    }
}

void CodeGen::generateCode() {
    
    if (!_ast || _ast->children.empty()) return;

    // Ensure AST's first node is a org with a valid
    std::shared_ptr<ASTNode> firstChild = _ast->children.front();

    if (firstChild->data->type != TokenType::ORG) {
        std::cerr << "Error: First child of the root is not an 'org'. Code generation aborted." << std::endl;
        exit(ERROR::ORG_ERROR);
    }

    // Now generate code
    _generateNodeCode(_ast);
    _updateLabels();

    /*
    for (auto& element : _varTable) {
        std::cout << element.name << ": " << element.value << std::endl;
    }

    for (auto& element : _labelTable) {
        std::cout << element.name << ": " << element.value << std::endl;
    }

    for (size_t i = 0; i < MAX_MEMORY + 1; i++) {
        if (_machineCode[i] != 0) 
            std::cout << static_cast<int>(_machineCode[i]) << ": " << i << std::endl;
    }
    */
}