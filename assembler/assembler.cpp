#include "assembler.hpp"

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

static bool isWhiteSpace(const char ch) {
    if (ch == ' ' || ch == '\t' || ch == '\n') return true;
    return false;
}

static void whiteSpaceStore(vector<Token>& tokens, string input, int& i) {
    Token token;
    string substring;

    while (isWhiteSpace(input[i])) {
        substring += input[i];

        if (!isWhiteSpace(input[i + 1])) {
            token = {WHITESPACE, substring};
            tokens.push_back(token);
            substring.clear();
            break;
        }
        i++;
    }
}

static void storeSingleValues(vector<Token>& tokens, string input, const char c, int& i) {
    Token token;
    string substring;

    if (input[i] == c) {
        while (!isWhiteSpace(input[i])) {
            substring += input[i];
            i++;
        }

        if (isWhiteSpace(input[i])) whiteSpaceStore(tokens, input, i);

        token = {DECLARATIVE, substring};
        tokens.push_back(token);
    }  
}

static void storeStringChar(vector<Token>& tokens, string input, const char c, int& i) {
    Token token;
    string substring;

    if (input[i] == c) {
        i++;
        while (input[i] != c) {
            substring += input[i];
            i++;
        }

        token = {SQUOTATION, substring};
        tokens.push_back(token);
        substring.clear();
        i++;
    } 
}

vector<Token> lexer(const string &input) {
    vector<Token> tokens;

    Token token;
    string substring;

    for (int i = 0; i < int(input.size()); i++) {

        // Filter Single Quotations
        storeStringChar(tokens, input, '\'', i);

        // Filter Double Quotations
        storeStringChar(tokens, input, '\"', i); 

        // Filter inline comments
        if (input[i] == ';') {
            while(input[i + 1] != '\n') i++;
        }

        // Filter Block Comments
        if (input[i] == '/' && input[i + 1] == '*') {
            i += 2;
            while (input[i] != '*' && input[i + 1] != '/') i++;
            i += 2;
        }

        // Filter Whitespace
        whiteSpaceStore(tokens, input, i);

        // Filter Declaritives
        storeSingleValues(tokens, input, '.', i);

        // Label Start
        if (!isWhiteSpace(input[i])){
            for (int j = i; j < int(input.size()); j++) {
                substring += input[j];

                if (input[j + 1] == ':') {
                    token = {LABELS, substring};
                    tokens.push_back(token);
                    substring.clear();
                    i = j + 2;
                    //break;
                }

                if (input[j] == '\n') {
                    substring.clear();
                    break;
                }
            }
            //continue;
        }
        
        // Store Hex values
        storeSingleValues(tokens, input, '$', i);
    
        // Store Binary values
        storeSingleValues(tokens, input, '%', i);

        // Store Immediate values
        storeSingleValues(tokens, input, '#', i);
    
    
    }



    for (const Token& token : tokens) {
        cout << "TokenType: " << token.type << ", Value: " << token.substring << endl;
    }


    return tokens;
}
