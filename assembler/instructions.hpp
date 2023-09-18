#include <iostream>
#include <string>
#include <vector>

enum Address_Mode {
    accumulator,
    implied,
    immediate,
    zeropage,
    zeropage_X,
    zeropage_Y,
    absolute,
    absolute_X,
    absolute_Y,
    relative,
    indirect,
    B_indirect_X_B,
    B_indirect_Y_B,
    B_indirect_B_X,
    B_indirect_B_Y,
};

struct Instrcution {
    std::string name;
    int opcode;
    Address_Mode addr_mode;
};
