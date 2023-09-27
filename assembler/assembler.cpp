#include <iostream>
#include <string>
#include <vector>
#include <regex>

#include "assembler.hpp"

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

static void printTokens(const std::vector<Token>& token_list) {
    for (const Token& token : token_list) {
        std::string typeStr;
        switch (token.type) {
            case TokenType::PREPROCESS:
                typeStr = "Preprocessor";
                break;
                
            case TokenType::WHITESPACE:
                typeStr = "Whitespace";
                break;
            // Add cases for other token types as needed
        }

        std::cout << "Type: " << typeStr << ", Value: " << token.substring << std::endl;
    }
}

std::string regex_to_string(const std::regex& re) {
    std::ostringstream oss;
    oss << re;
    std::string str = oss.str();
    // Remove the flags from the output and return the pattern
    return str.substr(1, str.find_last_of('/' ) - 1);
}

std::vector<Token> lexer(std::string text) {
    text = removeComments(text);

    std::vector<Token> token_list;

    // Define a regular expression
    std::regex preprocessor_regex("\\..*?\\s");
    std::regex whitespace_regex("[ \n\t]+");

    std::regex token_regex("(" + preprocessor_regex.pattern() + "|" + whitespace_regex.pattern() + ")");

    // Tokenize the input text
    std::sregex_iterator it(text.begin(), text.end(), token_regex);
    std::sregex_iterator end;

    while (it != end) {
        std::smatch match = *it;
        Token token;
        token.substring = match.str();

        if (std::regex_match(token.substring, preprocessor_regex)) {
            token.type = TokenType::PREPROCESS;
        } else if (std::regex_match(token.substring, whitespace_regex)) {
            token.type = TokenType::WHITESPACE;
        }

        token_list.push_back(token);
        ++it;
    }


    printTokens(token_list);

    return token_list;
}