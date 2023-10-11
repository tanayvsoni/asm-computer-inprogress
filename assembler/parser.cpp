#include <iostream>
#include <string>
#include <vector>
#include <regex>

#include "parser.hpp"
#include "functions.hpp"
#include "instructions.hpp"
#include "lexer.hpp"

static void print_parsed_tokens(const std::vector<ParsedInstruction>& parsed_list) {
    for (const ParsedInstruction& pToken :  parsed_list) {
        std::cout << "Address Value: " << pToken.address << "|Name: " << pToken.instr.name << "|Mode: " << pToken.instr.addr_mode;
        if (pToken.instr.addr_mode == "Implied") std::cout << std::endl;
        else std::cout << "|Arg Value: " << pToken.argumentValue << std::endl;
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
    if (tokens[i+1].type == TokenType::COMMA) pToken.instr.addr_mode = "absolute," + tokens[i+2].substring;
    else pToken.instr.addr_mode = "absolute";
}

static void handle_zp(size_t& i, const std::vector<Token>& tokens, ParsedInstruction& pToken) {
    if (tokens[i+1].type == TokenType::COMMA) pToken.instr.addr_mode = "zeropage," + tokens[i+1].substring;
    else pToken.instr.addr_mode = "zeropage";
}

static void replaceLabel(ParsedInstruction& pToken, const std::vector<Labels>& label_list) {
    for (const Labels& label : label_list) {
        if (label.name == pToken.label_val) {
            pToken.argumentValue = label.address; 
            break;
        }    
    }
}

static void handle_instr(size_t& i, std::vector<Token>& tokens, ParsedInstruction& pToken, std::vector<ParsedInstruction>& parsed_list) {
    pToken.instr.name = tokens[i].substring;
    i++;

    // Implied
    if (tokens[i].type == TokenType::NEWLINE) {
        pToken.instr.addr_mode = "implied";
        pToken.label_val = "";
        parsed_list.push_back(pToken);
        pToken.address += 1;

    } 
    // Immediate
    else if (tokens[i].type == TokenType::IMMEDIATE) {
        i++;
        pToken.argumentValue = handle_value(tokens[i]);

        if (pToken.argumentValue > 0xFF) {
            std::cerr << "Error: db value not in range (8 bit)" << std::endl; 
            exit(1);
        }

        pToken.instr.addr_mode = "immediate";
        pToken.label_val = "";
        parsed_list.push_back(pToken);
        pToken.address += 2;

    } 
    // Absolutes or Zeropages No labels
    else if (tokens[i].type == TokenType::NUMBER || tokens[i].type == TokenType::BINARY || tokens[i].type == TokenType::HEX || tokens[i].type == TokenType::NEGATIVE) {

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

    } 
    // Hand any labels for absolutes
    else if (tokens[i].type == TokenType::LABEL_USED) {

        pToken.label_val = tokens[i].substring;
        handle_abs(i, tokens, pToken);
        parsed_list.push_back(pToken);
        pToken.address += 3;
    } 
    // Indirects
    else if (tokens[i].type == TokenType::PAREN) {
        i++;

        // (Indirect)
        if ((tokens[i].type == TokenType::NUMBER || tokens[i].type == TokenType::BINARY || 
            tokens[i].type == TokenType::HEX || tokens[i].type == TokenType::NEGATIVE || 
            tokens[i].type == TokenType::LABEL_USED) && tokens[i + 1].type == TokenType::PAREN && tokens[i + 2].type == TokenType::NEWLINE) {
                if (tokens[i].type == TokenType::LABEL_USED) {
                    pToken.label_val = tokens[i].substring;
                    pToken.instr.addr_mode = "(indirect)";
                    parsed_list.push_back(pToken);
                    pToken.address += 3;
                    i += 2;
                } else {
                    pToken.argumentValue = handle_value(tokens[i]);
                    pToken.instr.addr_mode = "(indirect)";
                    parsed_list.push_back(pToken);
                    pToken.address += 3;
                    i += 2;
                }
        } 
        // (Indirect),X or (Indirect),Y
        else if ((tokens[i].type == TokenType::NUMBER || tokens[i].type == TokenType::BINARY || 
            tokens[i].type == TokenType::HEX || tokens[i].type == TokenType::NEGATIVE || 
            tokens[i].type == TokenType::LABEL_USED) && tokens[i + 1].type == TokenType::PAREN && tokens[i + 2].type == TokenType::COMMA && tokens[i + 3].type == TokenType::REG) {
                
                std::string reg;
                if (tokens[i + 3].substring == "X") reg = "X";   
                else reg = "Y";

                if (tokens[i].type == TokenType::LABEL_USED) {
                    pToken.label_val = tokens[i].substring;
                    pToken.instr.addr_mode = "(indirect)," + reg;
                    parsed_list.push_back(pToken);
                    pToken.address += 3;
                    i += 3;
                } else {
                    pToken.argumentValue = handle_value(tokens[i]);
                    pToken.instr.addr_mode = "(indirect)," + reg;
                    parsed_list.push_back(pToken);
                    pToken.address += 3;
                    i += 3;
                }
        } 
        // (Indirect,X) or (Indirect,Y)
        else if ((tokens[i].type == TokenType::NUMBER || tokens[i].type == TokenType::BINARY || 
            tokens[i].type == TokenType::HEX || tokens[i].type == TokenType::NEGATIVE || 
            tokens[i].type == TokenType::LABEL_USED) && tokens[i + 1].type == TokenType::COMMA && tokens[i + 2].type == TokenType::REG, tokens[i + 3].type == TokenType::PAREN) {

                std::string reg;
                if (tokens[i + 2].substring == "X") reg = "X";   
                else reg = "Y";

                 if (tokens[i].type == TokenType::LABEL_USED) {
                    pToken.label_val = tokens[i].substring;
                    pToken.instr.addr_mode = "(indirect," + reg + ")";
                    parsed_list.push_back(pToken);
                    pToken.address += 3;
                    i += 3;
                } else {
                    pToken.argumentValue = handle_value(tokens[i]);
                    pToken.instr.addr_mode = "(indirect," + reg + ")";
                    parsed_list.push_back(pToken);
                    pToken.address += 3;
                    i += 3;
                }
        }
        // Error
        else {
            std::cerr << "Error: Addressing Mode Error" << std::endl; 
            exit(1);
        }
    }
    // Error
    else {
        std::cerr << "Error: Addressing Mode Error" << std::endl; 
        exit(1);
    }

}

std::vector<ParsedInstruction> parse(std::vector<Token>& old_tokens, const std::vector<Instruction>& instruction_list) {
    
    for (const Token& token : old_tokens) {
        if (token.type != WHITESPACE && token.type != NEWLINE && token.substring != "org") {
            std::cerr << "Error: No starting address" << std::endl; 
            exit(1);
        } else if (token.substring == "org") break;
    }

    std::vector<Token> tokens;

    // Process all includes
    for (size_t i = 0; i < old_tokens.size(); i++) {
        if (i < old_tokens.size() - 1 && old_tokens[i].type == TokenType::INCLUDE && old_tokens[i + 1].type == TokenType::ARGUEMENT) {
            std::string temp_name = old_tokens[i + 1].substring;
            std::string temp_contents = get_contents(temp_name);
            std::vector<Token> new_tokens = lexer(temp_contents, instruction_list);

            for (Token token : new_tokens) tokens.push_back(token);

        } else if (old_tokens[i].type == TokenType::INCLUDE) {
            std::cerr << "Error: No Include Arguement" << std::endl; 
            exit(1);

        } else if (old_tokens[i].type != TokenType::ARGUEMENT) tokens.push_back(old_tokens[i]);
    }

    std::vector<ParsedInstruction> parsed_list;
    ParsedInstruction parsed_token;
    std::vector<Labels> label_list;
    std::vector<Vars> var_list;


    // First Pass for Labels
    for (size_t i = 0; i < tokens.size(); i++) {
        // Get the names of all labels
        if(tokens[i].type == TokenType::LABEL_DECLARE) {
            Labels label;
            label.name = tokens[i].substring;
            label_list.push_back(label);
        }
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
                Vars var;
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
                for (Labels& label : label_list) {
                    if (label.name == tokens[i].substring) label.address = parsed_token.address;
                }
                break;

            case TokenType::INSTRUCTION:
                handle_instr(i, tokens, parsed_token, parsed_list);
                break;
            
            default:
                break;
        }
    }

    for (ParsedInstruction& pToken : parsed_list) replaceLabel(pToken, label_list);
    

    //print_parsed_tokens(parsed_list);

    return parsed_list;
}


