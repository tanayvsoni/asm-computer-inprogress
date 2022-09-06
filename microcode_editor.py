
# INS #
CIDL  = 0b0001000000000000000000  # Program counter LSB in
CIDH  = 0b0010000000000000000000  # Program counter MSB in
RI    = 0b0011000000000000000000  # RAM data in
MI    = 0b0100000000000000000000  # Memory address register in
AI    = 0b0101000000000000000000  # A register in
XI    = 0b0110000000000000000000  # X register in
YI    = 0b0111000000000000000000  # Y register in
SRDI  = 0b1000000000000000000000  # Status Register in
SPI   = 0b1001000000000000000000  # Stack pointer in
TRLI  = 0b1010000000000000000000  # Transfer register LSB in
TRHI  = 0b1011000000000000000000  # Transfer register MSB in
OI    = 0b1100000000000000000000  # Output register in
SRI   = 0b0000000000000000010000  # Status register in
II    = 0b0000000000000000000100  # Instruction register in

# OUTS #
COA   = 0b0000000100000000000000  # Program counter address bus out
CODL  = 0b0000001000000000000000  # Program counter LSB data bus out
CODH  = 0b0000001100000000000000  # Program counter MSB data bus out
AO    = 0b0000010000000000000000  # A register out
XO    = 0b0000010100000000000000  # X register out
YO    = 0b0000011000000000000000  # Y register out
EO    = 0b0000011100000000000000  # ALU out
SPAO  = 0b0000100000000000000000  # Stack pointer address bus out
SPDO  = 0b0000100100000000000000  # Stack pointer data bus out
SRO   = 0b0000101000000000000000  # Status register out
RO    = 0b0000101100000000000000  # RAM data out
TRO   = 0b0000110000000000000000  # Transfer register out

# ARITHEMETIC #
AND   = 0b0000000000010000000000  # AND
OR    = 0b0000000000100000000000  # OR
XOR   = 0b0000000000110000000000  # XOR
SU    = 0b0000000001000000000000  # Subtract
LSHFR = 0b0000000001010000000000  # Logical shift right
ASHFL = 0b0000000001100000000000  # Arithemetic shift left
ROR   = 0b0000000001110000000000  # Rotate right
ROL   = 0b0000000010000000000000  # Rotate left
NOT   = 0b0000000010010000000000  # NOT

# GENERAL #
DSP   = 0b0000000010100000000000  # Decrement stack pointer
CLC   = 0b0000000010110000000000  # Clear carry flag
CLV   = 0b0000000011000000000000  # Clear overflow flag
CE    = 0b0000000000001000000000  # Increment program counter
J     = 0b0000000000000100000000  # Load program counter
SPE   = 0b0000000000000010000000  # Stack pointer enable
I     = 0b0000000000000001000000  # Interupt clear/disable
IJ    = 0b0000000000000000100000  # Jump to interupt subroutine ($BFFA)
EP    = 0b0000000000000000001000  # End program
NOP   = 0b0000000000000000000010  # No operation
FEC   = 0b0000000000000000000001  # Fetch into pipeline

FLAGS_C0Z0 = 0
FLAGS_C0Z1 = 1
FLAGS_C1Z0 = 2
FLAGS_C1Z1 = 3

BCC = 0b0111
BCS = 0b1000
BEQ = 0b1001
BMI = 0b1010
BNE = 0b01
BPL = 0b01
BVC = 0b01
BVS = 0b01


def createMicroCode(data):
    """
    Creates the microcode for the computer
    """
    rom_data = [0] * 512
    
    for instr in range(0, 16):
        for substep in range(0, 8):
            for flag in range(0, 4):

                # Address setup and storing data into rom_data
                address = (flag << 7) | (instr << 3) | substep
                    
                rom_data[address] = data[instr][substep]
                # Ensures FETCH instruction is the first run for all programs
                string_address = str(format(address, '09'))

                if string_address[7:] == '00':
                    rom_data[address] = MI | CO
                elif string_address[7:] == '01':
                    rom_data[address] = RO | II | CE
                    
                conditionalJumps_Expections(instr,substep,flag,address,rom_data)

                # Convert float array to integer array
                rom_data = [int(rom_data[i]) for i in range(0, 512)]
       
    return rom_data
        
def conditionalJumps_Expections(instr, substep, flag, address, rom_data):
        """
        Adds in expections for conditional jumps
        """
        # JC Expection
        if instr == JC and substep == 2 and (flag == FLAGS_C1Z0 or flag == FLAGS_C1Z1):
            rom_data[address] = IO | J

        # JZ Expection
        elif instr == JZ and substep == 2 and (flag == FLAGS_C1Z1 or flag == FLAGS_C0Z1):
            rom_data[address] = IO |J

        # JNC Expection
        elif instr == JNC and substep == 2 and (flag == FLAGS_C0Z0 or flag == FLAGS_C0Z1):
            rom_data[address] = IO |J

        # JNZ Expection
        elif instr == JNZ and substep == 2 and (flag == FLAGS_C1Z0 or flag == FLAGS_C0Z0):
            rom_data[address] = IO|J

def export(rom_data):            
    """
    Export Microcode into text file
    """     
    
                 
    with open('microcode.txt','w') as microcode:
        for code in rom_data:
            microcode.write("%s\n" % hex(code)[2:])

def main():    
    # Instruction Data
    instructions_data = [
        [ MI|COA|FEC, CE|II|EP,     0,           0,         0, 0, 0, 0, 0 ],     # 0000 - NOP
        
        # ADC #                                                                  # OPC       - ADDRESSING   ; ASSEMBLER
        [ MI|CO, RO|II|CE, IO|MI,       RO|AI,           0, 0, 0, 0, 0 ],        # 0000 0001 - immediate    ; #oper
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI,    EO|AI|FI, 0, 0, 0, 0 ],        # 0000 0010 - zeropage     ; oper
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 0000 0011 - zeropage     ; oper,X
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 0000 0100 - zeropage     ; oper,Y
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 0000 0101 - absolute     ; oper
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 0000 0110 - absolute     ; oper,X
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 0000 0111 - absolute     ; oper,Y
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 0000 1000 - (indirect,X) ; (oper,X)
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 0000 1001 - (indirect,Y) ; (oper,Y)
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 0000 1010 - (indirect),X ; (oper),X
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 0000 1011 - (indirect),Y ; (oper),Y
        
        
        
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 0100 - STA
        [ MI|CO, RO|II|CE, IO|AI,           0,           0, 0, 0, 0, 0 ],        # 0101 - LDI
        [ MI|CO, RO|II|CE,  IO|J,           0,           0, 0, 0, 0, 0 ],        # 0110 - JMP
        [ MI|CO, RO|II|CE,     0,           0,           0, 0, 0, 0, 0 ],        # 0111 - JC
        [ MI|CO, RO|II|CE,     0,           0,           0, 0, 0, 0, 0 ],        # 1000 - JZ
        [ MI|CO, RO|II|CE,     0,           0,           0, 0, 0, 0, 0 ],        # 1001 - JNC
        [ MI|CO, RO|II|CE,     0,           0,           0, 0, 0, 0, 0 ],        # 1010 - JNZ
        [ MI|CO, RO|II|CE, IO|BI,    EO|AI|FI,           0, 0, 0, 0, 0 ],        # 1011 - INC
        [ MI|CO, RO|II|CE, IO|BI, EO|AI|SU|FI,           0, 0, 0, 0, 0 ],        # 1100 - DEC
        [ MI|CO, RO|II|CE, IO|MI,       RO|OI,           0, 0, 0, 0, 0 ],        # 1101 - DSP
        [ MI|CO, RO|II|CE, AO|OI,           0,           0, 0, 0, 0, 0 ],        # 1110 - OUT
        [ MI|CO, RO|II|CE,   HLT,           0,           0, 0, 0, 0, 0 ],        # 1111 - HLT
    ]
    
    rom_data = createMicroCode(instructions_data)
    export(rom_data)
    
main()