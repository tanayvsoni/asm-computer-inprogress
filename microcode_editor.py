
# INS #
CIDL  = 0b0000010000000000000000000000000000  # Program counter LSB in #
CIDH  = 0b0000100000000000000000000000000000  # Program counter MSB in #
RI    = 0b0000110000000000000000000000000000  # RAM data in #
MI    = 0b1000000000000000000000000000000000  # Memory address register in #
EI    = 0b0001000000000000000000000000000000  # ALU in #
AI    = 0b0001010000000000000000000000000000  # A register in #
XI    = 0b0001100000000000000000000000000000  # X register in #
YI    = 0b0001110000000000000000000000000000  # Y register in #
SRDI  = 0b0010000000000000000000000000000000  # Status Register data bus in #
SPI   = 0b0010010000000000000000000000000000  # Stack pointer in #
TRLI  = 0b0000000000000000000000000100000000  # Transfer register LSB in #
TRHI  = 0b0010110000000000000000000000000000  # Transfer register MSB in # 
OI    = 0b0011000000000000000000000000000000  # Output register in #
FI    = 0b0000000000000000001000000000000000  # Status register in #
II    = 0b0000000000000000000010000000000000  # Instruction register in #

# OUTS #
COA   = 0b0100000000000000000000000000000000  # Program counter address bus out #
CODL  = 0b0000000010000000000000000000000000  # Program counter LSB data bus out #
CODH  = 0b0000000011000000000000000000000000  # Program counter MSB data bus out #
AO    = 0b0000000100000000000000000000000000  # A register data bus out #
XO    = 0b0000000000000000000000000000000100  # X register data bus out #
YO    = 0b0000000000000000000000000000000001  # Y register data bus out #
EO    = 0b0000000111000000000000000000000000  # ALU out #
SPAO  = 0b0000001000000000000000000000000000  # Stack pointer address bus out #
SPDO  = 0b0000001001000000000000000000000000  # Stack pointer data bus out #
SRO   = 0b0000001010000000000000000000000000  # Status register data bus out #
RO    = 0b0000001011000000000000000000000000  # RAM data out #
TRO   = 0b0000000000000000000000000001000000  # Transfer register out #
XOX1  = 0b0000001100000000000000000000001000  # X register aux bus 1 out #
YOX1  = 0b0000001101000000000000000000000010  # Y register aux bus 1 out #
XOX2  = 0b0000001110000000000000000000001100  # X register aux bus 2 out #
YOX2  = 0b0000001111000000000000000000000011  # Y register aux bus 2 out #
ES1   = 0b0000000000000000000000000010000000  # ALU input data bus out #
ES2   = 0b0000000000000000000000000010010000  # ALU input data bus out #

# ARITHEMETIC #
AND   = 0b0000000000000100000000000000000000  # AND
OR    = 0b0000000000001000000000000000000000  # OR
XOR   = 0b0000000000001100000000000000000000  # XOR
SU    = 0b0000000000010000000000000000000000  # Subtract
LSHFR = 0b0000000000010100000000000000000000  # Logical shift right
ASHFL = 0b0000000000011000000000000000000000  # Arithemetic shift left
ROR   = 0b0000000000011100000000000000000000  # Rotate right
ROL   = 0b0000000000100000000000000000000000  # Rotate left
NOT   = 0b0000000000100100000000000000000000  # NOT
INC   = 0b0000000000110100000000000000000000  # Increment 
DEC   = 0b0000000000111000000000000000000000  # Deccrement 

# GENERAL #
DSP   = 0b0000000000101000000000000000000000  # Decrement stack pointer #
CLC   = 0b0000000000101100000000000000000000  # Clear carry flag #
CLV   = 0b0000000000110000000000000000000000  # Clear overflow flag #
CE    = 0b0000000000000010000000000000000000  # Increment program counter #
J     = 0b0000000000000001000000000000000000  # Load program counter #
SPE   = 0b0000000000000000100000000000000000  # Stack pointer enable #
I     = 0b0000000000000000010000000000000000  # Interupt clear/disable# #
IJ    = 0b0000000000000000001000000000000000  # Jump to interupt subroutine ($BFFA) #
EP    = 0b0000000000000000000010000000000000  # End program #
NOP   = 0b0000000000000000000000100000000000  # No operation #
FEC   = 0b0000000000000000000000010000000000  # Fetch into pipeline
RTS   = 0b0000000000000000000000001000000000  # Reset Transfer register MSB
ECLK  = 0b0000000000000000000000000000100000  # CLK invert for ALU

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
        # NOP # No Operation                                                                                        # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|COA|CE|FEC, MI|COA|CE|II|EP,                0, 0, 0, 0, 0, 0, 0 ],                                     # 000 - implied      ; 
        
        # ADC # Add with Carry                                                                                      # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|COA|CE|FEC|RO|EI|ES2, MI|COA|CE|II|EO|AI|FI|EP, 0, 0, 0, 0, 0, 0 ],                                    # 001 - immediate    ; #oper
        [ MI|COA|CE|FEC|RO|TRLI|ECLK, MI|TRO|RO|ECLK|EI|ES2, MI|COA|CE|II|EO|AI|FI|EP, 0, 0, 0, 0, 0, 0 ],          # 002 - zeropage     ; oper
        [ MI|COA|CE|FEC|RO|EI|ES1|XOX1|ES2, EO|TRLI, MI|TRO, MI|COA|CE|II|RO|AI|EP, 0, 0, 0 ],                      # 003 - zeropage,X   ; oper,X
        [ MI|COA|CE|FEC|RO|EI|ES1|YOX1|ES2, EO|TRLI, MI|TRO, MI|COA|CE|II|RO|AI|EP, 0, 0, 0 ],                      # 004 - zeropage,Y   ; oper,Y
        
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 005 - absolute     ; oper
        
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 006 - absolute,X   ; oper,X
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 007 - absolute,Y   ; oper,Y
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 008 - (indirect,X) ; (oper,X)
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 009 - (indirect,Y) ; (oper,Y)
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 010 - (indirect),X ; (oper),X
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 011 - (indirect),Y ; (oper),Y
        
        # AND #                                                                  # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 012 - immediate    ; #oper
        [ MI|CO, RO|II|CE, IO|AI,           0,           0, 0, 0, 0, 0 ],        # 013 - zeropage     ; oper
        [ MI|CO, RO|II|CE,  IO|J,           0,           0, 0, 0, 0, 0 ],        # 014 - zeropage,X   ; oper,X
        [ MI|CO, RO|II|CE,     0,           0,           0, 0, 0, 0, 0 ],        # 015 - zeropage,Y   ; oper,Y
        [ MI|CO, RO|II|CE,     0,           0,           0, 0, 0, 0, 0 ],        # 016 - absolute     ; oper
        [ MI|CO, RO|II|CE,     0,           0,           0, 0, 0, 0, 0 ],        # 017 - absolute,X   ; oper,X
        [ MI|CO, RO|II|CE,     0,           0,           0, 0, 0, 0, 0 ],        # 018 - absolute,Y   ; oper,Y
        [ MI|CO, RO|II|CE, IO|BI,    EO|AI|FI,           0, 0, 0, 0, 0 ],        # 019 - (indirect,X) ; (oper,X)
        [ MI|CO, RO|II|CE, IO|BI, EO|AI|SU|FI,           0, 0, 0, 0, 0 ],        # 020 - (indirect,Y) ; (oper,Y)
        [ MI|CO, RO|II|CE, IO|MI,       RO|OI,           0, 0, 0, 0, 0 ],        # 021 - (indirect),X ; (oper),X
        [ MI|CO, RO|II|CE, AO|OI,           0,           0, 0, 0, 0, 0 ],        # 022 - (indirect),Y ; (oper),Y
        
        # ASL # Arithemic Shift Left                                             # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 023 - accumulator  ; A
        [ MI|CO, RO|II|CE, IO|AI,           0,           0, 0, 0, 0, 0 ],        # 024 - zeropage     ; oper
        [ MI|CO, RO|II|CE,  IO|J,           0,           0, 0, 0, 0, 0 ],        # 025 - zeropage,X   ; oper,X
        [ MI|CO, RO|II|CE,     0,           0,           0, 0, 0, 0, 0 ],        # 026 - zeropage,Y   ; oper,Y
        [ MI|CO, RO|II|CE,     0,           0,           0, 0, 0, 0, 0 ],        # 027 - absolute     ; oper
        [ MI|CO, RO|II|CE,     0,           0,           0, 0, 0, 0, 0 ],        # 028 - absolute,X   ; oper,X
        [ MI|CO, RO|II|CE,     0,           0,           0, 0, 0, 0, 0 ],        # 029 - absolute,Y   ; oper,Y
        
        # BCC # Branch on Carry Clear                                            # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 030 - relative     ; oper
        
        # BCS # Breanch on Carry Set                                             # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 031 - relative     ; oper
        
        # BEQ # Branch on Zero                                                   # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 032 - relative     ; oper
        
        # BIT # Test Bits in Memory with Accumulator                             # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 033 - zeropage     ; oper
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 034 - absolute     ; oper
        
        # BMI # Branch on Minus                                                  # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 035 - relative     ; oper
        
        # BNE # Branch on not Zero                                               # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 036 - relative     ; oper
        
        # BPL # Branch on Plus                                                   # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 037 - relative     ; oper
        
        # BRK # Forced Break                                                     # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 038 - implied      ;
        
        # BVC # Branch on Overflow Clear                                         # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 039 - relative     ; oper 
        
        # BVS # Branch on Overflow Set                                           # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 040 - relative     ; oper
        
        # CLC # Clear Carry Flag                                                 # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 041 - implied      ; 
        
        # CLV # Clear Overflow Flag                                              # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 042 - implied      ; 
        
        # CMP # Compare Memory with Accumulator                                  # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 043 - immediate    ; #oper
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 044 - zeropage     ; oper
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 045 - zeropage,X   ; oper,X
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 046 - zeropage,Y   ; oper,Y
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 047 - absolute     ; oper
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 048 - absolute,X   ; oper,X
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 049 - absolute,Y   ; oper,Y 
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 048 - (indirect,X) ; (oper,X)
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 049 - (indirect,Y) ; (oper,Y)
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 050 - (indirect),X ; (oper),X
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 051 - (indirect),Y ; (oper),Y
        
        # CPX # Compare Memory with Index X                                      # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 052 - immediate    ; #oper
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 053 - zeropage     ; oper
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 054 - absolute     ; oper
        
        # CPY # Compare Memory with Index X                                      # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 055 - immediate    ; #oper
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 056 - zeropage     ; oper
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 057 - absolute     ; oper
        
        # DEC # Decrement Memory by One                                          # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 058 - zeropage     ; oper
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 059 - zeropage,X   ; oper,X
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 060 - zeropage,Y   ; oper,Y
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 061 - absolute     ; oper
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 062 - absolute,X   ; oper,X
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 063 - absolute,Y   ; oper,Y
        
        # DEX # Decrement Index X by One                                         # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 064 - implied     ; 
        
        # DEC # Decrement Index Y by One                                         # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 065 - implied      ; 
        
        # EOR # Exclusive-OR Memory with Accumulator                             # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|COA|RO, CE|IO, IO|MI,       RO|AI,           0, 0, 0, 0, 0 ],       # 066 - immediate    ; #oper
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI,    EO|AI|FI, 0, 0, 0, 0 ],        # 067 - zeropage     ; oper
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 068 - zeropage,X   ; oper,X
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 069 - zeropage,Y   ; oper,Y
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 070 - absolute     ; oper
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 071 - absolute,X   ; oper,X
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 072 - absolute,Y   ; oper,Y
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 073 - (indirect,X) ; (oper,X)
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 074 - (indirect,Y) ; (oper,Y)
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 075 - (indirect),X ; (oper),X
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 076 - (indirect),Y ; (oper),Y
        
        # INC # Increment Memory by One                                          # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 077 - zeropage     ; oper
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 078 - zeropage,X   ; oper,X
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 079 - zeropage,Y   ; oper,Y
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 080 - absolute     ; oper
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 081 - absolute,X   ; oper,X
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 082 - absolute,Y   ; oper,Y
        
        # INX # Increment Index X by One                                         # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 083 - implied     ; 
        
        # INY # Increment Index Y by One                                         # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 084 - implied      ; 
        
        # JMP # Jump to new location                                             # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 085 - absolute     ; oper
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 086 - indirect     ; (oper)
        
        # JSR # Jump to new location Saving Return Address                       # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|CO, RO|II|CE, IO|MI,       RI|AO,           0, 0, 0, 0, 0 ],        # 087 - absolute     ; oper
        
        # LDA # Load Accumulator with Memory                                     # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|COA|RO, CE|IO, IO|MI,       RO|AI,           0, 0, 0, 0, 0 ],       # 088 - immediate    ; #oper
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI,    EO|AI|FI, 0, 0, 0, 0 ],        # 089 - zeropage     ; oper
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 090 - zeropage,X   ; oper,X
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 091 - zeropage,Y   ; oper,Y
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 092 - absolute     ; oper
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 093 - absolute,X   ; oper,X
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 094 - absolute,Y   ; oper,Y
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 095 - (indirect,X) ; (oper,X)
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 096 - (indirect,Y) ; (oper,Y)
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 097 - (indirect),X ; (oper),X
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 098 - (indirect),Y ; (oper),Y
        
        # LDX # Load Index X with Memory                                         # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|COA|RO, CE|IO, IO|MI,       RO|AI,           0, 0, 0, 0, 0 ],       # 099 - immediate    ; #oper
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI,    EO|AI|FI, 0, 0, 0, 0 ],        # 100 - zeropage     ; oper
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 101 - zeropage,Y   ; oper,Y
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 102 - absolute     ; oper
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 103 - absolute,Y   ; oper,Y  
        
        # LDY # Load Index Y with Memory                                         # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|COA|RO, CE|IO, IO|MI,       RO|AI,           0, 0, 0, 0, 0 ],       # 104 - immediate    ; #oper
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI,    EO|AI|FI, 0, 0, 0, 0 ],        # 105 - zeropage     ; oper
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 106 - zeropage,X   ; oper,X
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 107 - absolute     ; oper
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 108 - absolute,X   ; oper,X
        
        # LSR # Shift One Bit Right (Memory or Accumulator)                      # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|COA|RO, CE|IO, IO|MI,       RO|AI,           0, 0, 0, 0, 0 ],       # 109 - accumulator  ; A
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI,    EO|AI|FI, 0, 0, 0, 0 ],        # 110 - zeropage     ; oper
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 111 - zeropage,X   ; oper,X
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 112 - zeropage,Y   ; oper,Y
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 113 - absolute     ; oper
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 114 - absolute,X   ; oper,X
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 115 - zeropage,Y   ; oper,Y
        
        # ORA # OR Memory with Accumulator                                       # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|COA|RO, CE|IO, IO|MI,       RO|AI,           0, 0, 0, 0, 0 ],       # 116 - immediate    ; #oper
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI,    EO|AI|FI, 0, 0, 0, 0 ],        # 117 - zeropage     ; oper
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 118 - zeropage,X   ; oper,X
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 119 - zeropage,Y   ; oper,Y
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 120 - absolute     ; oper
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 121 - absolute,X   ; oper,X
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 122 - absolute,Y   ; oper,Y
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 123 - (indirect,X) ; (oper,X)
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 124 - (indirect,Y) ; (oper,Y)
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 125 - (indirect),X ; (oper),X
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 126 - (indirect),Y ; (oper),Y
        
        # PHA # Push Accumulator on Stack                                        # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|COA|RO, CE|IO, IO|MI,       RO|AI,           0, 0, 0, 0, 0 ],       # 127 - implied      ;
        
        # PHP # Push Processor Status on Stack                                   # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|COA|RO, CE|IO, IO|MI,       RO|AI,           0, 0, 0, 0, 0 ],       # 128 - implied      ;
        
        # PLA # Pull Accumulator from Stack                                      # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|COA|RO, CE|IO, IO|MI,       RO|AI,           0, 0, 0, 0, 0 ],       # 129 - implied      ;
        
        # PLP # Pull Processor Status from Stack                                 # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|COA|RO, CE|IO, IO|MI,       RO|AI,           0, 0, 0, 0, 0 ],       # 130 - implied      ;
        
        # ROR # Rotate One Bit Right (Memory or Accumulator)                     # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|COA|RO, CE|IO, IO|MI,       RO|AI,           0, 0, 0, 0, 0 ],       # 131 - accumulator  ; A
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI,    EO|AI|FI, 0, 0, 0, 0 ],        # 132 - zeropage     ; oper
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 133 - zeropage,X   ; oper,X
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 134 - zeropage,Y   ; oper,Y
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 135 - absolute     ; oper
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 136 - absolute,X   ; oper,X
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 137 - zeropage,Y   ; oper,Y
        
        # RTI # Return from Interrupt                                            # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|COA|RO, CE|IO, IO|MI,       RO|AI,           0, 0, 0, 0, 0 ],       # 138 - implied      ;
        
        # RTI # Return from Subroutine                                           # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|COA|RO, CE|IO, IO|MI,       RO|AI,           0, 0, 0, 0, 0 ],       # 139 - implied      ;
        
        # SUB # Subtract Memory from Accumulator with Borrow                     # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|COA|RO, CE|IO, IO|MI,       RO|AI,           0, 0, 0, 0, 0 ],       # 140 - immediate    ; #oper
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI,    EO|AI|FI, 0, 0, 0, 0 ],        # 141 - zeropage     ; oper
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 142 - zeropage,X   ; oper,X
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 143 - zeropage,Y   ; oper,Y
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 144 - absolute     ; oper
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 145 - absolute,X   ; oper,X
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 146 - absolute,Y   ; oper,Y
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 147 - (indirect,X) ; (oper,X)
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 148 - (indirect,Y) ; (oper,Y)
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 149 - (indirect),X ; (oper),X
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 150 - (indirect),Y ; (oper),Y
        
        # SEI # Set Interrupt Disable Status                                     # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|COA|RO, CE|IO, IO|MI,       RO|AI,           0, 0, 0, 0, 0 ],       # 151 - implied      ;
        
        # STA # Store Accumulator in Memory                                      # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI,    EO|AI|FI, 0, 0, 0, 0 ],        # 152 - zeropage     ; oper
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 153 - zeropage,X   ; oper,X
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 154 - zeropage,Y   ; oper,Y
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 155 - absolute     ; oper
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 156 - absolute,X   ; oper,X
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 157 - absolute,Y   ; oper,Y
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 158 - (indirect,X) ; (oper,X)
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 159 - (indirect,Y) ; (oper,Y)
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 160 - (indirect),X ; (oper),X
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 161 - (indirect),Y ; (oper),Y
        
        # STX # Store Index X in Memory                                          # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI,    EO|AI|FI, 0, 0, 0, 0 ],        # 162 - zeropage     ; oper
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 163 - zeropage,Y   ; oper,Y
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 164 - absolute     ; oper
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 165 - absolute,Y   ; oper,Y
        
        # STY # Store Index Y in Memory                                          # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI,    EO|AI|FI, 0, 0, 0, 0 ],        # 166 - zeropage     ; oper
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 167 - zeropage,X   ; oper,X
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 168 - absolute     ; oper
        [ MI|CO, RO|II|CE, IO|MI,       RO|BI, EO|AI|SU|FI, 0, 0, 0, 0 ],        # 169 - absolute,X   ; oper,X
        
        # TAX # Transfer Accumulator to Index X                                  # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|COA|RO, CE|IO, IO|MI,       RO|AI,           0, 0, 0, 0, 0 ],       # 170 - implied      ;
        
        # TAY # Transfer Accumulator to Index Y                                  # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|COA|RO, CE|IO, IO|MI,       RO|AI,           0, 0, 0, 0, 0 ],       # 171 - implied      ;
        
        # TSX # Transfer Stack Pointer to Index X                                # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|COA|RO, CE|IO, IO|MI,       RO|AI,           0, 0, 0, 0, 0 ],       # 172 - implied      ;
        
        # TSA # Transfer Index X to Accumulator                                  # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|COA|RO, CE|IO, IO|MI,       RO|AI,           0, 0, 0, 0, 0 ],       # 173 - implied      ;
        
        # TXS # Transfer Index X to Stack Register                               # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|COA|RO, CE|IO, IO|MI,       RO|AI,           0, 0, 0, 0, 0 ],       # 174 - implied      ;
        
        # TYA # Transfer Index Y to Accumulator                                  # OPC - ADDRESSING   ; ASSEMBLER
        [ MI|COA|RO, CE|IO, IO|MI,       RO|AI,           0, 0, 0, 0, 0 ],       # 175 - implied      ;
    ]
    
    rom_data = createMicroCode(instructions_data)
    export(rom_data)
    
main()