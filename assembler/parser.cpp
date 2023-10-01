#include <iostream>
#include <string>
#include <vector>
#include <regex>

#include "parser.hpp"
#include "functions.hpp"
#include "instructions.hpp"
#include "lexer.hpp"

static void print_parsed_tokens(const std::vector<ParsedInstruction>& parsed_list) {
    for (size_t i = 0; i < parsed_list.size(); i++) {
        std::cout << "Address Value: " << parsed_list[i].address << " Name: " << parsed_list[i].instr.name
         << " Arg Value: " << parsed_list[i].argumentValue << " Addressing Mode: " << parsed_list[i].instr.addr_mode << " Label Value: " << parsed_list[i].label_val << std::endl;
    }
}

static int handle_value(Token value) {

    switch (value.type) {
        case TokenType::HEX: 
            return std::stoi(value.substring, nullptr, 16);
        
        case TokenType::BINARY: 
            return std::stoi(value.substring, nullptr, 2);

        case TokenType::NEGATIVE:
            return stoi(value.substring, nullptr, 10);

        case TokenType::NUMBER: 
            return std::stoi(value.substring, nullptr, 10);
        
        default:
            std::cerr << "Error: Number not valid" << std::endl;
            exit(1);
    }
}

static void handle_preprocess(size_t& i, const std::vector<Token>& tokens, ParsedInstruction& pToken, std::vector<ParsedInstruction>& parsed_list) {
    std::string preprocess_name = tokens[i].substring;

    if (preprocess_name == "org") {
        i++;
        pToken.address = handle_value(tokens[i]);
        pToken.instr.addr_mode = "";
        pToken.label_val = "";

        if (pToken.address < 0x4000 || pToken.address > 0xFFFD) {
            std::cerr << "Error: Org Address not in range ($4000 - $FFFC)" << std::endl; 
            exit(1);
        }

    } else if (preprocess_name == "db") {
        pToken.size = 1;
        pToken.instr.addr_mode = "";
        pToken.label_val = "";

        while (tokens[i+1].type == TokenType::CHAR || tokens[i+1].type == TokenType::HEX || tokens[i+1].type == TokenType::NUMBER || tokens[i+1].type == TokenType::BINARY) {
            i++;
            if (tokens[i].type == TokenType::CHAR) {
                pToken.argumentValue = static_cast<int>(tokens[i].substring[0]);
                pToken.instr.name = "W";

            } else {
                pToken.argumentValue = handle_value(tokens[i]);
                pToken.instr.name = "W";
            }

            if (pToken.argumentValue > 0xFF) {
                std::cerr << "Error: db value not in range (8 bit)" << std::endl; 
                exit(1);
            }

            parsed_list.push_back(pToken);
            pToken.address += 1;
        }

    } else if (preprocess_name == "tx") {
        i++;
        pToken.instr.addr_mode = "";
        pToken.label_val = "";

        pToken.size = 1;
        for (size_t j = 0; j < tokens[i].substring.size(); j++) {
            pToken.argumentValue = static_cast<int>(tokens[i].substring[j]);
            pToken.instr.name = "W";
            parsed_list.push_back(pToken);
            pToken.address += 1;
        }

        pToken.argumentValue = 0;
        pToken.instr.name = "W";
        parsed_list.push_back(pToken);
        pToken.address += 1;


    } else {
       std::cerr << "Error: Preprocessor Statement" << std::endl; 
       exit(1); 
    }
}

static void handle_abs(size_t& i, const std::vector<Token>& tokens, ParsedInstruction& pToken) {
    pToken.size = 3;

    if (tokens[i+1].type == TokenType::COMMA) pToken.instr.addr_mode = "absolute," + tokens[i+1].substring;
    else pToken.instr.addr_mode = "absolute";
}

static void handle_zp(size_t& i, const std::vector<Token>& tokens, ParsedInstruction& pToken) {
    pToken.size = 2;

    if (tokens[i+1].type == TokenType::COMMA) pToken.instr.addr_mode = "zeropage," + tokens[i+1].substring;
    else pToken.instr.addr_mode = "zeropage";
}

static void replaceLabel(const size_t& i, std::vector<Token>& tokens, const std::vector<Labels>& label_list) {
    for (const Labels& label : label_list) {
        if (label.name == tokens[i].substring) {
            tokens[i].substring = std::to_string(label.address);
            tokens[i].type = TokenType::NUMBER;
        } 
            
    }
    
}

static void handle_instr(size_t& i, std::vector<Token>& tokens, ParsedInstruction& pToken, std::vector<ParsedInstruction>& parsed_list) {
    pToken.instr.name = tokens[i].substring;
    i++;

    if (tokens[i].type == TokenType::NEWLINE) {
        pToken.size = 1;
        pToken.instr.addr_mode = "Implied";
        pToken.label_val = "";
        parsed_list.push_back(pToken);
        pToken.address += 1;

    } else if (tokens[i].type == TokenType::IMMEDIATE) {
        i++;
        pToken.size = 2;
        pToken.argumentValue = handle_value(tokens[i]);

        if (pToken.argumentValue > 0xFF) {
            std::cerr << "Error: db value not in range (8 bit)" << std::endl; 
            exit(1);
        }

        pToken.instr.addr_mode = "Immediate";
        pToken.label_val = "";
        parsed_list.push_back(pToken);
        pToken.address += 2;

    } else if (tokens[i].type == TokenType::NUMBER || tokens[i].type == TokenType::BINARY || tokens[i].type == TokenType::HEX || tokens[i].type == TokenType::NEGATIVE) {

        //if (tokens[i].type == TokenType::LABEL_USED) replaceLabel(i, tokens, label_list);
        pToken.argumentValue = handle_value(tokens[i]);
        pToken.label_val = "";

        if (pToken.argumentValue > 0xFF && pToken.argumentValue <= 0xFFFF) {
            handle_abs(i, tokens, pToken);
            parsed_list.push_back(pToken);
            pToken.address += 3;
        } else if (pToken.argumentValue < 0xFF) {
            handle_zp(i, tokens, pToken);
            parsed_list.push_back(pToken);
            pToken.address += 2;
        } else {
            std::cerr << "Error: Number too Large" << std::endl;
            exit(1);
        }

    } else if (tokens[i].type == TokenType::LABEL_USED) {
        pToken.label_val = tokens[i].substring;
        handle_abs(i, tokens, pToken);
        parsed_list.push_back(pToken);
        pToken.address += 3;
    } else if (tokens[i].type == TokenType::PAREN) {
        i++;
        if ((tokens[i].type == TokenType::NUMBER || tokens[i].type == TokenType::BINARY || 
            tokens[i].type == TokenType::HEX || tokens[i].type == TokenType::NEGATIVE || 
            tokens[i].type == TokenType::LABEL_USED) && tokens[i + 1].type == TokenType::PAREN && tokens[i + 2].type == TokenType::NEWLINE) {
                if (tokens[i].type == TokenType::LABEL_USED) {
                    pToken.label_val = tokens[i].substring;
                    pToken.instr.addr_mode = "(indirect)";
                    pToken.size = 3;
                    parsed_list.push_back(pToken);
                    pToken.address += 3;
                    i += 2;
                }
        } else if ((tokens[i].type == TokenType::NUMBER || tokens[i].type == TokenType::BINARY || 
            tokens[i].type == TokenType::HEX || tokens[i].type == TokenType::NEGATIVE || 
            tokens[i].type == TokenType::LABEL_USED) && tokens[i + 1].type == TokenType::PAREN && tokens[i + 2].type == TokenType::COMMA) {

        }
    }

}

std::vector<ParsedInstruction> parse(std::vector<Token>& tokens) {
    for (const Token& token : tokens) {
        if (token.type != WHITESPACE && token.type != NEWLINE && token.substring != "org") {
            std::cerr << "Error: No starting address" << std::endl; 
            exit(1);
        } else if (token.substring == "org") break;
    }

    std::vector<ParsedInstruction> parsed_list;
    ParsedInstruction parsed_token;
    std::vector<Labels> label_list;
    std::vector<Vars> var_list;

    Labels label;
    Vars var;

    // First Pass for Labels
    for (size_t i = 0; i < tokens.size(); i++) {
        // Get the names of all labels
        if(tokens[i].type == TokenType::LABEL_DECLARE)
            label.name = tokens[i].substring;
            label_list.push_back(label);
    }

    // Second Pass for Variables
    for (size_t i = 0; i < tokens.size(); i++) {

        // Gets the values of each variable
        if (tokens[i].type == TokenType::IDENTIFIER_DECLARE) {
            bool isInVarList = false;

            // Check if it's already been declared if so replace it's value
            for (size_t j = 0; j < var_list.size(); j++) {
                if (var_list[j].name == tokens[i].substring) {
                    var_list[j].val = handle_value(tokens[i+2]);
                    isInVarList = true;
                }
            }

            // If not declared, add it in
            if (!isInVarList) {
                var.name = tokens[i].substring;
                var.val = handle_value(tokens[i+2]);
                var_list.push_back(var);
            }
            i += 2;

        // Replace all instances of the variable
        } else if (tokens[i].type == TokenType::IDENTIFIER) {
            bool isInVarList = false;

            for (size_t j = 0; j < var_list.size(); j++) {
                if (tokens[i].substring == var_list[j].name) {
                    tokens[i].substring = std::to_string(var_list[j].val);
                    tokens[i].type = TokenType::NUMBER;
                    isInVarList = true;
                }
            }

            if (!isInVarList) {
                std::cerr << "Error: Variable used without declaration" << std::endl; 
                exit(1);
            }
        }
    }

    // Third Pass
    for (size_t i = 0; i < tokens.size(); i++) {
        switch (tokens[i].type) {
            case TokenType::PREPROCESS:
                handle_preprocess(i, tokens, parsed_token, parsed_list);
                break;

            // Assgin each label with a address
            case TokenType::LABEL_DECLARE:  
                for (size_t j = 0; j < label_list.size(); j++) {
                    if (label_list[j].name == tokens[i].substring) {
                        label_list[j].address = parsed_token.address;
                    }
                }
                break;

            case TokenType::INSTRUCTION:
                handle_instr(i, tokens, parsed_token, parsed_list);
                break;
        }
    }

    print_parsed_tokens(parsed_list);

    return parsed_list;
}


