#include "main.hpp"

int main(int argc, char* argv[]) {
    // Check if file is provided
    if (argc != 2) {
        std::cerr << "Usage: ./emulator <filename>" << std::endl;
        exit(ERROR);
    }

    std::string programFile = argv[1];

    return 0;
}