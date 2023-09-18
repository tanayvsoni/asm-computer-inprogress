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
            //i++;
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

        token = {DECLARATIVE, substring};
        tokens.push_back(token);
        whiteSpaceStore(tokens, input, i);
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

        if (c == '\'') token = {SQUOTATION, substring};
        if (c == '\"') token = {DQUOTATION, substring};
        tokens.push_back(token);
        substring.clear();
        i++;
    } 
}

string extractMatchingSubstring(const string& input, const vector<string>& substrings) {
    for (const string& substring : substrings) {
        size_t foundPos = input.find(substring);
        if (foundPos != string::npos) return substring;
    }
    return "";
}

vector<Token> lexer(const string &input) {
    vector<Token> tokens;

    Token token;
    string substring;

    // Get all labels
    vector<string> label_list;
    for (size_t i = 0; i < input.size(); i++) {
        substring += input[i];

        if (input[i + 1] == ':') {
            label_list.push_back(substring);
            i++;
        }

        if (input[i] == '\n') substring.clear();
    }

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

        // Label Labels
        if (!isWhiteSpace(input[i])) {
            for (size_t j = i; j < input.size(); j++) {
                substring += input[j];

                if (input[j + 1] == ':') {
                    token = {LABELS, substring};
                    tokens.push_back(token);  
                    substring.clear();
                    i = int(j + 1);
                    break;
                }

                if (input[j] == '\n') {
                    string temp = extractMatchingSubstring(substring, label_list);
                    if (!temp.empty()) {
                        token = {LABELS, temp};
                        tokens.push_back(token);
                        substring.clear();
                        i = int(j);
                        break;
                    } else {
                        substring.clear();
                        break;
                    }

                }
            }
        }

        // Store Hex values
        storeSingleValues(tokens, input, '$', i);
    
        // Store Binary values
        storeSingleValues(tokens, input, '%', i);

        // Store Immediate values
        storeSingleValues(tokens, input, '#', i);

    }



    for (const Token& token : tokens) {
        if (token.type == 1) cout << "TokenType: " << token.type << ", Value: " << endl;
        else cout << "TokenType: " << token.type << ", Value: " << token.substring << endl;
    }


    return tokens;
}
