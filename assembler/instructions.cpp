#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "instructions.hpp"

std::vector<Instrcution> get_instr() {
    std::vector<Instrcution> instructions;
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
        std::string addr_mode_str;

        if (std::getline(iss, name, '|') &&
            (iss >> std::hex >> opcode) &&
            std::getline(iss >> std::ws, addr_mode_str)) {
            Address_Mode addr_mode = static_cast<Address_Mode>(std::stoi(addr_mode_str));
            instructions.push_back({name, opcode, addr_mode});
        } else {
            std::cerr << "Error: Invalid line in CSV file: " << line << std::endl;
        }
    }
}