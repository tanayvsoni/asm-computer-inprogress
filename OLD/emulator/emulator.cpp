#include "emulator.hpp"

Emulator::Emulator(const std::string& programFile) {
    const size_t startAddress = 0x4000;
    std::ifstream file(programFile, std::ios::binary);
    
    if (!file) {
        std::cerr << "Unable to open file: " << programFile << std::endl;
        exit(ERROR);
    }

     // Ensure that the file contents do not exceed the memory size
    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();
    if (fileSize > _memory.size() - startAddress) {
        std::cerr << "Error: File size exceeds available memory." << std::endl;
        exit(ERROR);
    }
    file.seekg(0, std::ios::beg);

    file.read(reinterpret_cast<char*>(&_memory[startAddress]), fileSize);
}

void Emulator::emulate() {
    while (_RUN) {
        _instrReg = _memory[_memoryAddressReg];
        _performInstr(_instrReg);
    }
}

