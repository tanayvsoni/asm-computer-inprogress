#include "assembler.hpp"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]){
    if (argc != 2) {
        cerr << "Usage: ./assembler <filename>" << endl;
        return 1;
    }

    string filename = argv[1];

    ifstream inputFile(filename);

    if(!inputFile.is_open()) {
        cerr << "Error: Unable to open file '" << filename << "'" << endl;
        return 1;
    }

    string fileContents;
    string line;

    while(getline(inputFile, line)) {
        fileContents += line + '\n';
    }

    inputFile.close();

    cout << "File Contents:" << endl;
    cout << fileContents;
         


    return 0;
}
