import csv
import re

def generate_cpp_code(csv_filename, header_filename):
    # Read instructions from CSV file
    with open(csv_filename, 'r') as file:
        reader = csv.reader(file, delimiter='|')
        instructions = [row for row in reader if row]

    # Generate C++ code for handling instructions
    cpp_code = "\nvoid Emulator::_performInstr(uint8_t instr) {\n"
    first = True
    for name, opcode, addr_mode in instructions:
        if first:
            cpp_code += f"    if (instr == {opcode}) {{\n        {name}(instr); // {addr_mode}\n    }}\n"
            first = False
        else:
            cpp_code += f"    else if (instr == {opcode}) {{\n        {name}(instr); // {addr_mode}\n    }}\n"
    cpp_code += "}\n"

    # Append the generated code to the header file
    with open(header_filename, 'a') as file:
        file.write(cpp_code)

def main():
    generate_cpp_code('instructions.csv', 'emulator.cpp')

if __name__ == "__main__":
    main()
    