#include <iostream>
#include <string>
#include <vector>
#include <regex>

#include "lexer.hpp"
#include "functions.hpp"
#include "instructions.hpp"

static std::string removeComments(std::string text) {
    std::string result;
    bool inCommentBlock = false;
    bool inLineComment = false;

    for (size_t i = 0; i < text.length(); i++) {
        if (!inCommentBlock) {
            if (text[i] == '/' && i + 1 < text.length() && text[i + 1] == '*') {
                inCommentBlock = true;
                i++;
            }
            else if (text[i] == ';' && !inLineComment) {
                inLineComment = true;
            }
            else if (text[i] == '\n' && inLineComment) {
                result += text[i];
                inLineComment = false;
            }
            else if (inLineComment) {
                continue;
            }
            else {
                result += text[i];
            }
        }
        else if (inCommentBlock && text[i] == '*' && i + 1 < text.length() && text[i + 1] == '/') {
            inCommentBlock = false;
            ++i;
        }
    }

    return result;
}

static void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Avoid infinite loop by moving past the replaced substring
    }
}

static void printTokens(const std::vector<Token>& token_list) {
    for (const Token& token : token_list) {
        std::string typeStr;
        switch (token.type) {
            case TokenType::STRING:
                typeStr = "String";
                break;

            case TokenType::CHAR:
                typeStr = "Char";
                break;
            
            case TokenType::INCLUDE:
                typeStr = "Include ";
                break;
            
            case TokenType::ARGUEMENT:
                typeStr = "Arguement ";
                break;

            case TokenType::PREPROCESS:
                typeStr = "Preprocessor";
                break;

            case TokenType::NEWLINE:
                typeStr = "Newline";
                break;
                
            case TokenType::WHITESPACE:
                typeStr = "Whitespace";
                break;
            
            case TokenType::LABEL_DECLARE:
                typeStr = "Label Declare";
                break;

            case TokenType::LABEL_USED:
                typeStr = "Label Used";
                break;
            
            case TokenType::COMMA:
                typeStr = "Comma";
                break;

            case TokenType::REG:
                typeStr = "Register";
                break;
            
            case TokenType::PAREN:
                typeStr = "Parentheses";
                break;
            
            case TokenType::IMMEDIATE:
                typeStr = "Immediate";
                break;
            
            case TokenType::BINARY:
                typeStr = "Binary";
                break;
            
            case TokenType::HEX:
                typeStr = "Hex";
                break;
            
            case TokenType::NEGATIVE:
                typeStr = "Negative";
                break;

            case TokenType::NUMBER:
                typeStr = "Number";
                break;


            case TokenType::INSTRUCTION:
                typeStr = "Instruction";
                break;

            case TokenType::IDENTIFIER:
                typeStr = "Identifier";
                break;
            
            case TokenType::IDENTIFIER_DECLARE:
                typeStr = "Identifier Declare";
                break;
            
            case TokenType::EQUAL:
                typeStr = "Equal";
                break;
        }
        if (typeStr == "Whitespace" || typeStr == "Newline") continue;
        else std::cout << "Type: " << typeStr << ", Value: " << token.substring << std::endl;
    }
}

static std::string getInstr_String(const std::vector<Instruction>& instruction_list) {
    std::string temp =  "";
    std::string output;

    for (size_t i = 0; i < instruction_list.size(); i++) {
        if (temp != instruction_list[i].name) {
            temp = instruction_list[i].name;
            output += temp + "|" + toLowerCase(temp) + "|";
        }
    }

    output.pop_back();
    return output;
}

static bool isLabel(const std::vector<Token>& token_list, const Token curr_token) {
    for (size_t i = 0; i < token_list.size(); i++) {
        if (token_list[i].type == TokenType::LABEL_DECLARE && curr_token.substring == token_list[i].substring) return true;
    }
    return false;
}

std::vector<Token> lexer(std::string text, const std::vector<Instruction>& instruction_list) {
    text = removeComments(text);
    std::string instruction_string = getInstr_String(instruction_list);

    //std::cout << instruction_string << std::endl;

    std::vector<Token> token_list;

    // Define a regular expression
    std::string string_regex = "(\"((?:\\\\.|[^\"\\\\])*)\")";
    std::string char_regex = "(\'((?:\\\\.|[^\'\\\\])*)\')";
    std::string preprocessor_regex = "(\\.(?!\\s)(\\w+))";
    std::string include_regex = "(#[a-zA-Z]+)";    
    std::string arguement_regex = "(<([^>]+)>)";
    std::string newline_regex = "([\\n]+)";
    std::string whitespace_regex = "([ \t]+)";
    std::string label_regex = "(^([a-zA-Z_]\\w*):)";
    std::string comma_regex = "(,)";
    std::string reg_regex = "(r[XY])";
    std::string paren_regex = "(\\(|\\))";
    std::string immediate_regex = "(#)";
    std::string binary_regex = "(%(\\d+))";
    std::string hex_regex = "(\\$(?!\\s)([a-zA-Z0-9]+))";
    std::string negative_regex = "(-(\\d+))";
    std::string number_regex = "(\\d+)";
    std::string instruction_regex =  "(\\b(" + instruction_string + ")\\b)";
    std::string identifier_regex = "(\\w+)";
    std::string equal_regex = "(=)";

    std::regex token_regex(string_regex + "|" + char_regex + "|" + include_regex + "|" + arguement_regex + "|" + preprocessor_regex + "|" + newline_regex + "|" + whitespace_regex + "|" + label_regex + "|" + 
                           comma_regex + "|" + reg_regex + "|" + paren_regex + "|" + immediate_regex + "|" + binary_regex + "|" + hex_regex + "|" + 
                           negative_regex + "|" + number_regex + "|" + instruction_regex + "|" + identifier_regex + "|" + equal_regex,
                           std::regex::multiline);

    // Tokenize the input text
    std::sregex_iterator it(text.begin(), text.end(), token_regex);
    std::sregex_iterator end;

    while (it != end) {
        std::smatch match = *it;
        Token token;
        token.substring = match.str();

        if (std::regex_match(match.str(), std::regex(string_regex))) {
            token.type = TokenType::STRING;
            token.substring.erase(0, 1);
            token.substring.pop_back();
            replaceAll(token.substring, "\\\"", "\"");

        } else if (std::regex_match(match.str(), std::regex(char_regex))) {
            token.type = TokenType::CHAR;
            token.substring.erase(0, 1);
            token.substring.pop_back();
            replaceAll(token.substring, "\\\'", "\'");
        
        } else if (std::regex_match(match.str(), std::regex(include_regex))) { token.type = TokenType::INCLUDE;
        
        } else if (std::regex_match(match.str(), std::regex(arguement_regex))) { 
            token.type = TokenType::ARGUEMENT;
            token.substring.erase(0, 1);
            token.substring.pop_back();

        } else if (std::regex_match(match.str(), std::regex(preprocessor_regex))) {
            token.type = TokenType::PREPROCESS;
            token.substring.erase(0, 1);
            token.substring = toLowerCase(token.substring);
        
        } else if (std::regex_match(match.str(), std::regex(newline_regex))) { token.type = TokenType::NEWLINE;

        } else if (std::regex_match(match.str(), std::regex(whitespace_regex))) { token.type = TokenType::WHITESPACE;

        } else if (std::regex_match(match.str(), std::regex(label_regex))) {
            token.type = TokenType::LABEL_DECLARE;
            token.substring.pop_back();

        } else if (std::regex_match(match.str(), std::regex(comma_regex))) { token.type = TokenType::COMMA;

        } else if (std::regex_match(match.str(), std::regex(reg_regex))) { 
            token.type = TokenType::REG;
            token.substring.erase(0, 1);

        } else if (std::regex_match(match.str(), std::regex(paren_regex))) { token.type = TokenType::PAREN;

        } else if (std::regex_match(match.str(), std::regex(immediate_regex))) { token.type = TokenType::IMMEDIATE;      

        } else if (std::regex_match(match.str(), std::regex(binary_regex))) { 
            token.type = TokenType::BINARY;      
            token.substring.erase(0, 1);

        } else if (std::regex_match(match.str(), std::regex(hex_regex))) { 
            token.type = TokenType::HEX;      
            token.substring.erase(0, 1);
        
        } else if (std::regex_match(match.str(), std::regex(negative_regex))) {  token.type = TokenType::NEGATIVE; 

        } else if (std::regex_match(match.str(), std::regex(number_regex))) {  token.type = TokenType::NUMBER;  

        } else if (std::regex_match(match.str(), std::regex(instruction_regex))) {  
            token.type = TokenType::INSTRUCTION; 
            token.substring = toUpperCase(token.substring);
        
        } else if (std::regex_match(match.str(), std::regex(identifier_regex))) {  token.type = TokenType::IDENTIFIER; 
        
        } else if (std::regex_match(match.str(), std::regex(equal_regex))) {  token.type = TokenType::EQUAL;  
        }

        if (token.type != TokenType::WHITESPACE) token_list.push_back(token);
        ++it;
        
    }

    for (size_t i = 0; i < token_list.size(); i++) {
        if (token_list[i].type == TokenType::IDENTIFIER && isLabel(token_list, token_list[i]))
            token_list[i].type = TokenType::LABEL_USED;
    }

    for (size_t i = 0; i < token_list.size(); i++) {
        if (token_list[i].type == TokenType::IDENTIFIER && token_list[i + 1].type == TokenType::EQUAL)
            token_list[i].type = TokenType::IDENTIFIER_DECLARE;
    }

    //printTokens(token_list);

    return token_list ;
}