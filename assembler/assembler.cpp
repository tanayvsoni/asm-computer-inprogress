#include "assembler.hpp"

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

static bool isWhiteSpace(const char ch) {
    if (ch == ' ' || ch == '\t' || ch == '\n') return true;
    return false;
}

static bool endFile(const int i, const std::string input) {
    if (i == int(input.size())) return true;
    return false;
}

vector<Token> lexer(const string &input) {
    vector<Token> tokens;

    Token token;
    string substring;

    for (int i = 0; i < int(input.size()); i++) {

        // Filter Single Quotations
        if (input[i] == '\'') {
            i++;
            while (input[i] != '\'') {
                substring += input[i];
                i++;
            }

            token = {SQUOTATION, substring};
            tokens.push_back(token);
            substring.clear();
            i++;
        }

        // Filter Double Quotations
        if (input[i] == '"') {
            i++;
            while (input[i] != '"') {
                substring += input[i];
                i++;
            }

            token = {DQUOTATION, substring};
            tokens.push_back(token);
            substring.clear();
            i++;
        }

        // Filter inline comments
        if (input[i] == ';') {
            i++;
            while(true) {
                substring += input[i];

                if (input[i + 1] == '\n') break;
                if (endFile(i, input)) return tokens;
                i++;
            }

            token = {INLINE_COMMENTS, substring};
            tokens.push_back(token);
            substring.clear();
        }

        // Filter Block Comments
        if (input[i] == '/' && input[i + 1] == '*') {
            i += 2;
            while (true) {
                substring += input[i];

                if (input[i + 1] == '*' && input[i + 2] == '/') {
                    i += 2;
                    break;
                }
                
                if (endFile(i, input)) return tokens;
                i++;
            }

            token = {BLOCK_COMMENTS, substring};
            tokens.push_back(token);
            substring.clear();
        }

        // Filter Whitespace
        while (isWhiteSpace(input[i])) {
            substring += input[i];

            if (!isWhiteSpace(input[i + 1])) {
                token = {WHITESPACE, substring};
                tokens.push_back(token);
                substring.clear();
                break;
            }

            if (endFile(i, input)) return tokens;
            i++;
        }

        // Filter Declaritives
        if (input[i] == '.') {
            while (!isWhiteSpace(input[i])) {
                substring += input[i];
                i++;
            }

            token = {DECLARATIVE, substring};
            tokens.push_back(token);
            substring.clear();
            i--;
        }

        if (!isWhiteSpace(input[i])){
            for (int j = i; j < int(input.size()); j++) {
                substring += input[j];

                if (input[j + 1] == ':') {
                    token = {LABELS, substring};
                    tokens.push_back(token);
                    substring.clear();
                    i = j + 1;
                    break;
                }

                if (input[j] == '\n') {
                    substring.clear();
                    break;
                }

            }
        }
        
    
    }



    for (const Token& token : tokens) {
        cout << "TokenType: " << token.type << ", Value: " << token.substring << endl;
    }

    return tokens;
}
