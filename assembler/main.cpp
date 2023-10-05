#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdint>
#include <cstdio>

#include "instructions.hpp"
#include "lexer.hpp"
#include "parser.hpp"

uint8_t get_opcode(const std::string& instr_name, const std::string& instr_mode, const std::vector<Instruction>& instruction_list) {
    for (const Instruction& instruction : instruction_list) {
        if (instruction.name == instr_name && instruction.addr_mode == instr_mode) return instruction.opcode;
    }

    std::cerr << "Error: Instruction not found: " << instr_name << std::endl;
    exit(1);
} 

void code_gen(const std::vector<ParsedInstruction>& parsed_tokens, const std::vector<Instruction>& instruction_list, std::string& filename) { 
    filename.erase(filename.length() - 4);
    filename += ".bin";

    const char* output_name = filename.c_str();
    std::remove(output_name);

    std::ofstream outfile(output_name, std::ios::binary);

    char emptySpace[0xFFFF - 0x4000 + 1] = {0};
    outfile.write(emptySpace, sizeof(emptySpace));

    for (const ParsedInstruction& pToken : parsed_tokens) {
        uint8_t byteValue = 0;
        int address = pToken.address - 0x4000;

        if (pToken.instr.name != "W") {
            byteValue = get_opcode(pToken.instr.name, pToken.instr.addr_mode, instruction_list);

            outfile.seekp(address, std::ios::beg);
            outfile.write(reinterpret_cast<char*>(&byteValue), 1);

            if (pToken.argumentValue <= 0xFF) {
                address = pToken.address+1 - 0x4000;
                byteValue = static_cast<uint8_t>(pToken.argumentValue);

                outfile.seekp(address, std::ios::beg);
                outfile.write(reinterpret_cast<char*>(&byteValue), 1);
            } else {
                // Store LSB
                address = pToken.address+1 - 0x4000;
                byteValue = static_cast<uint8_t>(pToken.argumentValue);

                outfile.seekp(address, std::ios::beg);
                outfile.write(reinterpret_cast<char*>(&byteValue), 1);

                // Store MSB
                address = pToken.address+2 - 0x4000;
                byteValue = static_cast<uint8_t>(pToken.argumentValue >> 8);

                outfile.seekp(address, std::ios::beg);
                outfile.write(reinterpret_cast<char*>(&byteValue), 1);
            }


        } else {
            byteValue = static_cast<uint8_t>(pToken.argumentValue);
            outfile.seekp(address, std::ios::beg);
            outfile.write(reinterpret_cast<char*>(&byteValue), 1);
        }
    }

    outfile.close();
}   

int main(int argc, char* argv[]){
    if (argc != 2) {
        std::cerr << "Usage: ./assembler <filename>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];

    std::ifstream inputFile(filename);

    if(!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file '" << filename << "'" << std::endl;
        return 1;
    }

    std::string fileContents;
    std::string line;

    while(getline(inputFile, line)) fileContents += line + '\n';

    inputFile.close();

    std::vector<Instruction> instruction_list  = get_instr();
    std::vector<Token> tokens = lexer(fileContents, instruction_list);
    std::vector<ParsedInstruction> parsed_tokens = parse(tokens);
    code_gen(parsed_tokens, instruction_list, filename);

    

    return 0;
}
