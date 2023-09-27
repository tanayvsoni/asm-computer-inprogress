#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "instructions.hpp"

std::vector<std::string> address_modes  = {
    "accumulator",
    "implied",
    "immediate",
    "zeropage",
    "zeropage,X",
    "zeropage,Y",
    "absolute",
    "absolute,X",
    "absolute,Y",
    "relative",
    "indirect",
    "(indirect,X)",
    "(indirect,Y)",
    "(indirect),X",
    "(indirect),Y"
};

static void printInstructions(const std::vector<Instruction>& instructions) {
    for (const Instruction& instr : instructions) {
        std::cout << "Name: " << instr.name << std::endl;
        std::cout << "Opcode: " << instr.opcode << std::endl;
        std::cout << "Address Mode: " << instr.addr_mode << std::endl;
        std::cout << "--------------------------" << std::endl;
    }
}

std::vector<Instruction> get_instr() {
    /*
    
    Gets list of instructions alongside it's possible modes

    Returns vector<Instrctions>
    
    */

    std::vector<Instruction> instructions;
    std::ifstream file("instructions.csv");

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file instructions.csv" << std::endl;
        return instructions; // Return an error code
    }

    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name;
        int opcode;
        std::string addr_mode = "test";

        if (
            std::getline(iss, name, '|') &&             // Gets Name of Instructions
            (iss >> opcode) &&                          // Gets Opcode
            std::getline(iss >> std::ws, addr_mode)     // Gets Addressing Mode
            ) {

            addr_mode.erase(std::remove(addr_mode.begin(), addr_mode.end(), '|'), addr_mode.end());     // Remove '|' Char
            instructions.push_back({name, opcode, addr_mode});
        }
    }

    return instructions;
}