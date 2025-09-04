#ifndef EMULATOR_HPP
#define EMULATOR_HPP

#include "main.hpp"

class Emulator {
public:
    Emulator(const std::string& programFile);

    void emulate();

private:
    // Memory
    std::vector<uint8_t> _memory = std::vector<uint8_t>(MAX_MEMORY + 1, 0);

    // GP Registers
    uint8_t _regA = 0;
    uint8_t _regX = 0;
    uint8_t _regY = 0;

    // Special Registers
    uint8_t _instrReg = 0;
    uint8_t _flagsReg = 0;
    uint8_t _stackPointer = 0;
    uint16_t _memoryAddressReg = 0x4000;
    uint16_t _programCounter = 0x4001;

    // Vectors
    const uint16_t irqVec = 0xfffd;

    // Flags
    const uint8_t _CF  = 0b00000001;        // Carry Flag
    const uint8_t _VF  = 0b00000010;        // Overflow Flag
    const uint8_t _NF  = 0b00000100;        // Negative Flag
    const uint8_t _ZF  = 0b00001000;        // Zero Flag
    const uint8_t _IF  = 0b00100000;        // Interupt Flag

    // Running
    bool _RUN = true;

    // Functions
    void _performInstr(uint8_t instr);
};

#endif