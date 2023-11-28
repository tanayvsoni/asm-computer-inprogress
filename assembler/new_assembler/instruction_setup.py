import csv

def append_instructions_to_header(csv_filename, header_filename):
    # Read instructions from CSV file
    with open(csv_filename, 'r') as file:
        reader = csv.reader(file, delimiter='|')
        instructions = [row for row in reader if row]

    # Generate C++ code for the instruction set
    cpp_code = "\ninline std::vector<Instruction> createInstructionSet() {\n"
    cpp_code += "    std::vector<Instruction> instructionSet;\n"
    for name, opcode, addr_mode in instructions:
        cpp_code += f"    instructionSet.push_back({{\"{name}\", {opcode}, \"{addr_mode}\"}});\n"
    cpp_code += "    return instructionSet;\n"
    cpp_code += "}\n"

    # Read the current contents of the header file
    with open(header_filename, 'r') as file:
        lines = file.readlines()

    # Check if the function already exists
    func_start = None
    func_end = None
    for i, line in enumerate(lines):
        if 'inline std::vector<Instruction> createInstructionSet()' in line:
            func_start = i
        if func_start is not None and line.strip() == '}' and func_end is None:
            func_end = i
            break

    # Replace or insert the function
    if func_start is not None and func_end is not None:
        # Ensure only one newline before the function
        if func_start > 0 and lines[func_start - 1].strip() != '':
            cpp_code = '\n' + cpp_code
        lines[func_start-1:func_end + 1] = [cpp_code]
    else:
        # Find the position to insert the generated code
        insert_pos = next(i for i, line in enumerate(lines) if line.strip() == '#endif') - 1
        # Ensure only one newline before the function
        lines.insert(insert_pos, cpp_code)

    # Write back to the header file
    with open(header_filename, 'w') as file:
        file.writelines(lines)

def main():
    append_instructions_to_header("instructions.csv", "main.hpp")

if __name__ == '__main__':    
    main()