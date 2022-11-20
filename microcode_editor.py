# Section 1 #
MI    = 0b10_0000_000_0000_0000_0000_0000_00_00_00_0_0000_00  # Memory address register in
COA   = 0b01_0000_000_0000_0000_0000_0000_00_00_00_0_0000_00  # Program counter address bus out

# Decoder 1 #
CIDL  = 0b00_0001_000_0000_0000_0000_0000_00_00_00_0_0000_00  # Program counter LSB in
CIDH  = 0b00_0010_000_0000_0000_0000_0000_00_00_00_0_0000_00  # Program counter MSB in
RI    = 0b00_0011_000_0000_0000_0000_0000_00_00_00_0_0000_00  # RAM data in
EI    = 0b00_0100_000_0000_0000_0000_0000_00_00_00_0_0000_00  # ALU in
AI    = 0b00_0101_000_0000_0000_0000_0000_00_00_00_0_0000_00  # A register in
XI    = 0b00_0110_000_0000_0000_0000_0000_00_00_00_0_0000_00  # X register in
YI    = 0b00_0111_000_0000_0000_0000_0000_00_00_00_0_0000_00  # Y register in
SRDI  = 0b00_1000_000_0000_0000_0000_0000_00_00_00_0_0000_00  # Status Register data bus in
SPI   = 0b00_1001_000_0000_0000_0000_0000_00_00_00_0_0000_00  # Stack pointer in
CI    = 0b00_1010_000_0000_0000_0000_0000_00_00_00_0_0000_00  # Clear Interupt Disable
TRHI  = 0b00_1011_000_0000_0000_0000_0000_00_00_00_0_0000_00  # Transfer register MSB in 
OI    = 0b00_1100_000_0000_0000_0000_0000_00_00_00_0_0000_00  # Output register in
BR    = 0b00_1101_000_0000_0000_0000_0000_00_00_00_0_0000_00  # Invert Memory Address Register CLK
BIT   = 0b00_1110_000_0000_0000_0000_0000_00_00_00_0_0000_00  # Bit Test
SC    = 0b00_1111_000_0000_0000_0000_0000_00_00_00_0_0000_00  # Set Carry Flag

# Decoder 2 #
CODL  = 0b00_0000_001_0000_0000_0000_0000_00_00_00_0_0000_00  # Program counter LSB data bus out
CODH  = 0b00_0000_010_0000_0000_0000_0000_00_00_00_0_0000_00  # Program counter MSB data bus out
AO    = 0b00_0000_011_0000_0000_0000_0000_00_00_00_0_0000_00  # A register data bus out
DRF   = 0b00_0000_100_0000_0000_0000_0000_00_00_00_0_0000_00  # Direct Fetch into Instruction Register
SPDO  = 0b00_0000_101_0000_0000_0000_0000_00_00_00_0_0000_00  # Stack pointer data bus out
SRO   = 0b00_0000_110_0000_0000_0000_0000_00_00_00_0_0000_00  # Status register data bus out
RO    = 0b00_0000_111_0000_0000_0000_0000_00_00_00_0_0000_00  # RAM data out

# Decoder 3 #
AND   = 0b00_0000_000_0001_0000_0000_0000_00_00_00_0_0000_00  # AND
OR    = 0b00_0000_000_0010_0000_0000_0000_00_00_00_0_0000_00  # OR
XOR   = 0b00_0000_000_0011_0000_0000_0000_00_00_00_0_0000_00  # XOR
SU    = 0b00_0000_000_0100_0000_0000_0000_00_00_00_0_0000_00  # Subtract
LSHFR = 0b00_0000_000_0101_0000_0000_0000_00_00_00_0_0000_00  # Logical shift right
ASHFL = 0b00_0000_000_0110_0000_0000_0000_00_00_00_0_0000_00  # Arithemetic shift left
ROR   = 0b00_0000_000_0111_0000_0000_0000_00_00_00_0_0000_00  # Rotate right
ROL   = 0b00_0000_000_1000_0000_0000_0000_00_00_00_0_0000_00  # Rotate left
CMP   = 0b00_0000_000_1001_0000_0000_0000_00_00_00_0_0000_00  # Compare 
DSP   = 0b00_0000_000_1010_0000_0000_0000_00_00_00_0_0000_00  # Decrement stack pointer 
NOP   = 0b00_0000_000_1011_0000_0000_0000_00_00_00_0_0000_00  # No operation/Invert Instruction Register CLK
SI    = 0b00_0000_000_1100_0000_0000_0000_00_00_00_0_0000_00  # Set Interupt Disable
INC   = 0b00_0000_000_1101_0000_0000_0000_00_00_00_0_0000_00  # Increment
DEC   = 0b00_0000_000_1110_0000_0000_0000_00_00_00_0_0000_00  # Deccrement 
ADD   = 0b00_0000_000_1111_0000_0000_0000_00_00_00_0_0000_00  # Add without Carry

# Section 2 #
CE    = 0b00_0000_000_0000_1000_0000_0000_00_00_00_0_0000_00  # Increment program counter
J     = 0b00_0000_000_0000_0100_0000_0000_00_00_00_0_0000_00  # Load program counter
SPE   = 0b00_0000_000_0000_0010_0000_0000_00_00_00_0_0000_00  # Stack pointer enable
IJ    = 0b00_0000_000_0000_0001_0000_0000_00_00_00_0_0000_00  # Jump to interupt subroutine ($FFFA)

# Section 3 #
FI    = 0b00_0000_000_0000_0000_1000_0000_00_00_00_0_0000_00  # Status Register In
EP    = 0b00_0000_000_0000_0000_0100_0000_00_00_00_0_0000_00  # End program
II    = 0b00_0000_000_0000_0000_0010_0000_00_00_00_0_0000_00  # Instruction Register In
FEC   = 0b00_0000_000_0000_0000_0001_0000_00_00_00_0_0000_00  # Fetch into pipeline

# Section 4 #
RTR   = 0b00_0000_000_0000_0000_0000_1000_00_00_00_0_0000_00  # Reset Transfer register MSB
EO    = 0b00_0000_000_0000_0000_0000_0100_00_00_00_0_0000_00  # ALU Register Out
ES1   = 0b00_0000_000_0000_0000_0000_0010_00_00_00_0_0000_00  # ALU A Data Select
TRO   = 0b00_0000_000_0000_0000_0000_0001_00_00_00_0_0000_00  # Transfer Register Out

# Section 5 #
ECLK  = 0b00_0000_000_0000_0000_0000_0000_10_00_00_0_0000_00  # CLK invert for ALU & SR
ES2   = 0b00_0000_000_0000_0000_0000_0000_01_00_00_0_0000_00  # ALU B Data Select

# X Regsiter Outs #
XO    = 0b00_0000_000_0000_0000_0000_0000_00_01_00_0_0000_00  # X Register Data Bus Out
XOX1  = 0b00_0000_000_0000_0000_0000_0000_00_10_00_0_0000_00  # X Register Aux Bus 1 Out
XOX2  = 0b00_0000_000_0000_0000_0000_0000_00_11_00_0_0000_00  # X Register Aux Bus 2 Out

# Y Regsiter Outs #
YO    = 0b00_0000_000_0000_0000_0000_0000_00_00_01_0_0000_00  # Y Register Data Bus Out
YOX1  = 0b00_0000_000_0000_0000_0000_0000_00_00_10_0_0000_00  # Y Register Aux Bus 1 Out
YOX2  = 0b00_0000_000_0000_0000_0000_0000_00_00_11_0_0000_00  # Y Register Aux Bus 2 Out

# Section 6 #
TRLI  = 0b00_0000_000_0000_0000_0000_0000_00_00_00_1_0000_00  # Transfer Register LSB In

# Decoder 4 #
CTR   = 0b00_0000_000_0000_0000_0000_0000_00_00_00_0_0001_00  # Carry into TRHI
IE    = 0b00_0000_000_0000_0000_0000_0000_00_00_00_0_0010_00  # Interupt End
CLC   = 0b00_0000_000_0000_0000_0000_0000_00_00_00_0_0011_00  # Clear carry flag
HLT   = 0b00_0000_000_0000_0000_0000_0000_00_00_00_0_0100_00  # Halt CLK
CLV   = 0b00_0000_000_0000_0000_0000_0000_00_00_00_0_0101_00  # Clear overflow flag
LD    = 0b00_0000_000_0000_0000_0000_0000_00_00_00_0_0110_00  # Load Registers
SPAO  = 0b00_0000_000_0000_0000_0000_0000_00_00_00_0_0111_00  # Stack Pointer Address Bus Out
PEC   = 0b00_0000_000_0000_0000_0000_0000_00_00_00_0_1000_00  # Set JUMP
CJ    = 0b00_0000_000_0000_0000_0000_0000_00_00_00_0_1001_00  # Clear JUMP

# Section 7 #
CSB   = 0b00_0000_000_0000_0000_0000_0000_00_00_00_0_0000_10  # Counter Dec
RCC   = 0b00_0000_000_0000_0000_0000_0000_00_00_00_0_0000_01  # Reverse Counter Clock

def createMicroCode(data):  
    """
    Creates the microcode for the computer
    """
    rom_data = [0] * (1024 * 256)
    
    for flag in range(0, 128):
        for instr in range(0, 256):
            for substep in range(0, 9):

                # Address setup and storing data into rom_data
                address = (flag << 11) | (instr << 3) | substep
                 
                try: rom_data[address] = data[instr][substep]
                except: pass
                
                conditionalJumps_Expections(flag,instr,substep,address,rom_data) 
                
    return rom_data

def substeps_CJ(substep, rom_data, address):
    match substep:
        case 0: rom_data[address] = RO|CIDL
        case 1: rom_data[address] = MI|COA|RO|CIDH|RCC 
        case 2: rom_data[address] = MI|COA|BR|RCC|J
        case 3: rom_data[address] = MI|COA|RCC|FEC
        case 4: rom_data[address] = MI|COA|CE|II|EP
     

def conditionalJumps_Expections(flag, instr, substep, address, rom_data):
    """
    Adds in expections for conditional jumps
    """
    
    CF  = bool((flag>>0)&1)
    VF  = bool((flag>>1)&1)
    NF  = bool((flag>>2)&1)
    ZF  = bool((flag>>3)&1)
    BF  = bool((flag>>4)&1)
    I   = bool((flag>>5)&1)
    IMG = bool((flag>>6)&1)
    
    # BCC - Branch on Carry Clear
    if (not CF) and (instr == 30): substeps_CJ(substep, rom_data, address)

    # BCS - Branch on Carry Set
    elif CF and (instr == 31): substeps_CJ(substep, rom_data, address)
    
    # BEQ - Branch on Zero Set
    elif ZF and (instr == 32): substeps_CJ(substep, rom_data, address)
    
    # BMI - Branch on Minus
    elif NF and (instr == 35): substeps_CJ(substep, rom_data, address)
    
    # BNE - Branch on not Zero
    elif (not ZF) and (instr == 36): substeps_CJ(substep, rom_data, address)
    
    # BPL - Branch on Plus
    elif (not NF) and (instr == 37): substeps_CJ(substep, rom_data, address)
    
    # BVC - Branch on Overflow Clear
    elif (not VF) and (instr == 39): substeps_CJ(substep, rom_data, address)
    
    # BVS - Branch on Overflow Set 
    elif VF and (instr == 40): substeps_CJ(substep, rom_data, address)
    
def export(rom_data):            
    """
    Export Microcode into text file
    """     
    with open('microcode.txt','w') as microcode:
        for i in range(len(rom_data)):
            microcode.write(f'{hex(rom_data[i])[2:]}\n')

def main():    
    # Instruction Data
    instructions_data = [
        # NOP # No operation                                                                                                                                   # OPC - ADDRESSING    ; ASSEMBLER
        [FEC, MI|COA|CE|II|EP],                                                                                                                                # 000 - implied       ;
        
        # ADC # Add with Carry                                                                                                                                 # OPC - ADDRESSING    ; ASSEMBLER
        [MI|COA|CE|FEC|RO|EI|ES2|FI, MI|COA|EO|AI, CE|II|EP],                                                                                                  # 001 - immediate     ; #oper
        [MI|COA|CE|FEC|RO|TRLI|ECLK|RTR, MI|TRO|RO|ECLK|EI|ES2|FI, MI|COA|CE|II|EO|AI|EP],                                                                     # 002 - zeropage      ; oper
        [MI|COA|CE|FEC|RO|EI|ES1|XOX1|ES2|ADD, EO|TRLI|ECLK|RTR, MI|TRO|RO|ECLK|EI|ES2|FI, MI|COA|CE|II|EO|AI|EP],                                             # 003 - zeropage,X    ; oper,X
        [MI|COA|CE|FEC|RO|EI|ES1|YOX1|ES2|ADD, EO|TRLI|ECLK|RTR, MI|TRO|RO|ECLK|EI|ES2|FI, MI|COA|CE|II|EO|AI|EP],                                             # 004 - zeropage,Y    ; oper,Y
        [MI|COA|CE|RO|TRLI, MI|COA|CE|FEC|RO|TRHI|ECLK, MI|TRO|RO|ECLK|EI|ES2|FI, MI|COA|CE|II|EO|AI|EP],                                                      # 005 - absolute      ; oper 
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|XOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO|RO|ECLK|EI|ES2|FI, MI|COA|CE|II|EO|AI|EP],                       # 006 - absolute,X    ; oper,X
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|YOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO|RO|ECLK|EI|ES2|FI, MI|COA|CE|II|EO|AI|EP],                       # 007 - absolute,Y    ; oper,Y
        [MI|COA|CE|FEC|RO|EI|ES1|ADD|XOX1|ES2, EO|TRLI|RTR, MI|TRO, RO|TRLI|ECLK, MI|TRO|RO|ECLK|EI|ES2|FI, MI|COA|CE|II|EO|AI|EP],                            # 008 - (indirect,X)  ; (oper,X)
        [MI|COA|CE|FEC|RO|EI|ES1|ADD|YOX1|ES2, EO|TRLI|RTR, MI|TRO, RO|TRLI|ECLK, MI|TRO|RO|ECLK|EI|ES2|FI, MI|COA|CE|II|EO|AI|EP],                            # 009 - (indirect,Y)  ; (oper,Y)
        [MI|COA|CE|FEC|RO|TRLI|RTR|ECLK, MI|TRO|RO|ECLK|EI|ES1|XOX1|ES2|ADD|CTR, EO|TRLI|ECLK|TRHI|CTR, MI|TRO|RO|ECLK|EI|ES2|FI, MI|COA|CE|II|EO|AI|EP],      # 010 - (indirect),X  ; (oper),X
        [MI|COA|CE|FEC|RO|TRLI|RTR|ECLK, MI|TRO|RO|ECLK|EI|ES1|YOX1|ES2|ADD|CTR, EO|TRLI|ECLK|TRHI|CTR, MI|TRO|RO|ECLK|EI|ES2|FI, MI|COA|CE|II|EO|AI|EP],      # 011 - (indirect),Y  ; (oper),Y
        
        # AND #                                                                                                                                                # OPC - ADDRESSING    ; ASSEMBLER
        [MI|COA|CE|FEC|RO|AND|EI|ES2, MI|COA|EO|AI, CE|II|EP],                                                                                                 # 012 - immediate     ; #oper
        [MI|COA|CE|FEC|RO|TRLI|ECLK|RTR, MI|TRO|RO|AND|ECLK|EI|ES2, MI|COA|CE|II|EO|AI|EP],                                                                    # 013 - zeropage      ; oper
        [MI|COA|CE|FEC|RO|EI|ES1|XOX1|ES2|ADD, EO|TRLI|ECLK|RTR, MI|TRO|RO|AND|ECLK|EI|ES2, MI|COA|CE|II|EO|AI|EP],                                            # 014 - zeropage,X    ; oper,X
        [MI|COA|CE|FEC|RO|EI|ES1|YOX1|ES2|ADD, EO|TRLI|ECLK|RTR, MI|TRO|RO|AND|ECLK|EI|ES2, MI|COA|CE|II|EO|AI|EP],                                            # 015 - zeropage,Y    ; oper,Y
        [MI|COA|CE|RO|TRLI, MI|COA|CE|FEC|RO|TRHI|ECLK, MI|TRO|RO|AND|ECLK|EI|ES2, MI|COA|CE|II|EO|AI|EP],                                                     # 016 - absolute      ; oper
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|XOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO|RO|AND|ECLK|EI|ES2, MI|COA|CE|II|EO|AI|EP],                      # 017 - absolute,X    ; oper,X
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|YOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO|RO|AND|ECLK|EI|ES2, MI|COA|CE|II|EO|AI|EP],                      # 018 - absolute,Y    ; oper,Y
        [MI|COA|CE|FEC|RO|EI|ES1|ADD|XOX1|ES2, EO|TRLI|RTR, MI|TRO, RO|TRLI|ECLK, MI|TRO|RO|AND|ECLK|EI|ES2, MI|COA|CE|II|EO|AI|EP],                           # 019 - (indirect,X)  ; (oper,X)
        [MI|COA|CE|FEC|RO|EI|ES1|ADD|YOX1|ES2, EO|TRLI|RTR, MI|TRO, RO|TRLI|ECLK, MI|TRO|RO|AND|ECLK|EI|ES2, MI|COA|CE|II|EO|AI|EP],                           # 020 - (indirect,Y)  ; (oper,Y)
        [MI|COA|CE|FEC|RO|TRLI|RTR|ECLK, MI|TRO|RO|ECLK|EI|ES1|XOX1|ES2|ADD|CTR, EO|TRLI|ECLK|TRHI|CTR, MI|TRO|RO|AND|ECLK|EI|ES2, MI|COA|CE|II|EO|AI|EP],     # 021 - (indirect),X  ; (oper),X
        [MI|COA|CE|FEC|RO|TRLI|RTR|ECLK, MI|TRO|RO|ECLK|EI|ES1|YOX1|ES2|ADD|CTR, EO|TRLI|ECLK|TRHI|CTR, MI|TRO|RO|AND|ECLK|EI|ES2, MI|COA|CE|II|EO|AI|EP],     # 022 - (indirect),Y  ; (oper),Y
        
        # ASL # Arithemic Shift Left                                                                                                                           # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|ASHFL|EI, MI|COA|EO|AI, CE|II|EP],                                                                                                      # 023 - accumulator  ; A
        [MI|COA|CE|FEC|RO|TRLI|RTR, MI|TRO, RO|AI, ASHFL|EI, MI|COA|CE|II|EO|AI|EP],                                                                           # 024 - zeropage     ; oper
        [MI|COA|CE|FEC|RO|EI|ES1|XOX1|ES2|ADD, EO|TRLI|RTR, MI|TRO, RO|AI, ASHFL|EI, MI|COA|CE|II|EO|AI|EP],                                                   # 025 - zeropage,X   ; oper,X
        [MI|COA|CE|FEC|RO|EI|ES1|YOX1|ES2|ADD, EO|TRLI|RTR, MI|TRO, RO|AI, ASHFL|EI, MI|COA|CE|II|EO|AI|EP],                                                   # 026 - zeropage,Y   ; oper,Y
        [MI|COA|CE|RO|TRLI, MI|COA|CE|FEC|RO|TRHI, MI|TRO, RO|AI, ASHFL|EI, MI|COA|CE|II|EO|AI|EP],                                                            # 027 - absolute     ; oper
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|XOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO, RO|AI, ASHFL|EI, MI|COA|CE|II|EO|AI|EP],                        # 028 - absolute,X   ; oper,X
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|YOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO, RO|AI, ASHFL|EI, MI|COA|CE|II|EO|AI|EP],                        # 029 - absolute,Y   ; oper,Y
        
        # BCC # Branch on Carry Clear                                                                                                                          # OPC - ADDRESSING   ; ASSEMBLER
        [CE, MI|COA|CE|FEC, MI|COA|CE|II|EP],                                                                                                                  # 030 - relative     ; oper
        
        # BCS # Branch on Carry Set                                                                                                                            # OPC - ADDRESSING   ; ASSEMBLER
        [CE, MI|COA|CE|FEC, MI|COA|CE|II|EP],                                                                                                                  # 031 - relative     ; oper
        
        # BEQ # Branch on Zero                                                                                                                                 # OPC - ADDRESSING   ; ASSEMBLER
        [CE, MI|COA|CE|FEC, MI|COA|CE|II|EP],                                                                                                                  # 032 - relative     ; oper
        
        # BIT # Test Bits in Memory with Accumulator                                                                                                           # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|RO|TRLI|RTR|ECLK, MI|TRO|RO|BIT|ES2|ECLK, MI|COA|CE|II|EP],                                                                             # 033 - zeropage     ; oper
        [MI|COA|CE|RO|TRLI, MI|COA|CE|FEC|RO|TRHI|ECLK, MI|TRO|RO|BIT|ECLK|ES2, MI|COA|CE|II|EP],                                                              # 034 - absolute     ; oper
        
        # BMI # Branch on Minus                                                                                                                                # OPC - ADDRESSING   ; ASSEMBLER
        [CE, MI|COA|CE|FEC, MI|COA|CE|II|EP],                                                                                                                  # 035 - relative     ; oper
        
        # BNE # Branch on not Zero                                                                                                                             # OPC - ADDRESSING   ; ASSEMBLER
        [CE, MI|COA|CE|FEC, MI|COA|CE|II|EP],                                                                                                                  # 036 - relative     ; oper
        
        # BPL # Branch on Plus                                                                                                                                 # OPC - ADDRESSING   ; ASSEMBLER
        [CE, MI|COA|CE|FEC, MI|COA|CE|II|EP],                                                                                                                  # 037 - relative     ; oper
        
        # BRK # Hard/Soft Interrupt                                                                                                                            # OPC - ADDRESSING   ; ASSEMBLER
        [MI|SPAO|SI|CODH|RI|SPE|CSB, MI|SPAO|CODL|RI|SPE|CSB, MI|SPAO|SRO|RI|SPE, IJ|J, MI|COA|CE|FEC, MI|COA, CE|II|EP],                                      # 038 - implied      ;
        
        # BVC # Branch on Overflow Clear                                                                                                                       # OPC - ADDRESSING   ; ASSEMBLER
        [CE, MI|COA|CE|FEC, MI|COA|CE|II|EP],                                                                                                                  # 039 - relative     ; oper 
        
        # BVS # Branch on Overflow Set                                                                                                                         # OPC - ADDRESSING   ; ASSEMBLER
        [CE, MI|COA|CE|FEC, MI|COA|CE|II|EP],                                                                                                                  # 040 - relative     ; oper
        
        # CLC # Clear Carry Flag                                                                                                                               # OPC - ADDRESSING   ; ASSEMBLER
        [FEC|CLC, MI|COA|CE|II|EP],                                                                                                                            # 041 - implied      ; 
        
        # CLI # Clear Interupt Disable Bit                                                                                                                     # OPC - ADDRESSING   ; ASSEMBLER
        [FEC|CI, MI|COA|CE|II|EP],                                                                                                                             # 042 - implied      ; 
        
        # CLV # Clear Overflow Flag                                                                                                                            # OPC - ADDRESSING   ; ASSEMBLER
        [FEC|CLV, MI|COA|CE|II|EP],                                                                                                                            # 043 - implied      ; 
        
        # CMP # Compare Memory with Accumulator                                                                                                                # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|RO|CMP|ES2, MI|COA, CE|II|EP],                                                                                                          # 044 - immediate    ; #oper
        [MI|COA|CE|FEC|RO|TRLI|ECLK|RTR, MI|TRO|RO|ECLK|CMP|ES2, MI|COA|CE|II|EP],                                                                             # 045 - zeropage     ; oper
        [MI|COA|CE|FEC|RO|EI|ES1|XOX1|ES2|ADD, EO|TRLI|ECLK|RTR, MI|TRO|RO|ECLK|CMP|ES2, MI|COA|CE|II|EP],                                                     # 046 - zeropage,X   ; oper,X
        [MI|COA|CE|FEC|RO|EI|ES1|YOX1|ES2|ADD, EO|TRLI|ECLK|RTR, MI|TRO|RO|ECLK|CMP|ES2, MI|COA|CE|II|EP],                                                     # 047 - zeropage,Y   ; oper,Y
        [MI|COA|CE|RO|TRLI, MI|COA|CE|FEC|RO|TRHI|ECLK, MI|TRO|RO|ECLK|CMP|ES2, MI|COA|CE|II|EP],                                                              # 048 - absolute     ; oper
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|XOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO|RO|ECLK|CMP|ES2, MI|COA|CE|II|EP],                               # 049 - absolute,X   ; oper,X
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|YOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO|RO|ECLK|CMP|ES2, MI|COA|CE|II|EP],                               # 050 - absolute,Y   ; oper,Y 
        [MI|COA|CE|FEC|RO|EI|ES1|ADD|XOX1|ES2, EO|TRLI|RTR, MI|TRO, RO|TRLI|ECLK, MI|TRO|RO|ECLK|CMP|ES2, MI|COA|CE|II|EP],                                    # 051 - (indirect,X) ; (oper,X)
        [MI|COA|CE|FEC|RO|EI|ES1|ADD|YOX1|ES2, EO|TRLI|RTR, MI|TRO, RO|TRLI|ECLK, MI|TRO|RO|ECLK|CMP|ES2, MI|COA|CE|II|EP],                                    # 052 - (indirect,Y) ; (oper,Y)
        [MI|COA|CE|FEC|RO|TRLI|RTR|ECLK, MI|TRO|RO|ECLK|EI|ES1|XOX1|ES2|ADD|CTR, EO|TRLI|ECLK|TRHI|CTR, MI|TRO|RO|ECLK|CMP|ES2, MI|COA|CE|II|EP],              # 053 - (indirect),X ; (oper),X
        [MI|COA|CE|FEC|RO|TRLI|RTR|ECLK, MI|TRO|RO|ECLK|EI|ES1|YOX1|ES2|ADD|CTR, EO|TRLI|ECLK|TRHI|CTR, MI|TRO|RO|ECLK|CMP|ES2, MI|COA|CE|II|EP],              # 054 - (indirect),Y ; (oper),Y
        
        # CPX # Compare Memory with Index X                                                                                                                    # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|RO|CMP|XOX1|ES1|ES2, MI|COA, CE|II|EP],                                                                                                 # 055 - immediate    ; #oper
        [MI|COA|CE|FEC|RO|TRLI|ECLK|RTR, MI|TRO|RO|ECLK|CMP|XOX1|ES1|ES2, MI|COA|CE|II|EP],                                                                    # 056 - zeropage     ; oper
        [MI|COA|CE|RO|TRLI, MI|COA|CE|FEC|RO|TRHI|ECLK, MI|TRO|RO|ECLK|CMP|XOX1|ES1|ES2, MI|COA|CE|II|EP],                                                     # 057 - absolute     ; oper
        
        # CPY # Compare Memory with Index X                                                                                                                    # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|RO|CMP|YOX1|ES1|ES2, MI|COA, CE|II|EP],                                                                                                 # 058 - immediate    ; #oper
        [MI|COA|CE|FEC|RO|TRLI|ECLK|RTR, MI|TRO|RO|ECLK|CMP|YOX1|ES1|ES2, MI|COA|CE|II|EP],                                                                    # 059 - zeropage     ; oper
        [MI|COA|CE|RO|TRLI, MI|COA|CE|FEC|RO|TRHI|ECLK, MI|TRO|RO|ECLK|CMP|YOX1|ES1|ES2, MI|COA|CE|II|EP],                                                     # 060 - absolute     ; oper
        
        # DEC # Decrement Memory by One                                                                                                                        # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|RO|TRLI|ECLK|RTR, MI|TRO|RO|ECLK|EI|ES2|DEC, EO|RI, MI|COA|CE|II|EP],                                                                   # 061 - zeropage     ; oper
        [MI|COA|CE|FEC|RO|EI|ES1|XOX1|ES2|ADD, EO|TRLI|ECLK|RTR, MI|TRO|RO|ECLK|EI|ES2|DEC, EO|RI, MI|COA|CE|II|EP],                                           # 062 - zeropage,X   ; oper,X
        [MI|COA|CE|FEC|RO|EI|ES1|YOX1|ES2|ADD, EO|TRLI|ECLK|RTR, MI|TRO|RO|ECLK|EI|ES2|DEC, EO|RI, MI|COA|CE|II|EP],                                           # 063 - zeropage,Y   ; oper,Y
        [MI|COA|CE|RO|TRLI, MI|COA|CE|FEC|RO|TRHI|ECLK, MI|TRO|RO|ECLK|EI|ES2|DEC, EO|RI, MI|COA|CE|II|EP],                                                    # 064 - absolute     ; oper
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|XOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO|RO|ECLK|EI|ES2|DEC, EO|RI, MI|COA|CE|II|EP],                     # 065 - absolute,X   ; oper,X
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|YOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO|RO|ECLK|EI|ES2|DEC, EO|RI, MI|COA|CE|II|EP],                     # 066 - absolute,Y   ; oper,Y
        
        # DEX # Decrement Index X by One                                                                                                                       # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|XOX2|EI|ES2|DEC, MI|COA|EO|XI, CE|II|EP],                                                                                               # 067 - implied     ; 
        
        # DEC # Decrement Index Y by One                                                                                                                       # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|YOX2|EI|ES2|DEC, MI|COA|EO|YI, CE|II|EP],                                                                                               # 068 - implied      ; 
        
        # EOR # Exclusive-OR Memory with Accumulator                                                                                                           # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|RO|XOR|EI|ES2, MI|COA|EO|AI, CE|II|EP],                                                                                                 # 069 - immediate    ; #oper
        [MI|COA|CE|FEC|RO|TRLI|ECLK|RTR, MI|TRO|RO|XOR|ECLK|EI|ES2, MI|COA|CE|II|EO|AI|EP],                                                                    # 070 - zeropage     ; oper
        [MI|COA|CE|FEC|RO|EI|ES1|XOX1|ES2|ADD, EO|TRLI|ECLK|RTR, MI|TRO|RO|XOR|ECLK|EI|ES2, MI|COA|CE|II|EO|AI|EP],                                            # 071 - zeropage,X   ; oper,X
        [MI|COA|CE|FEC|RO|EI|ES1|YOX1|ES2|ADD, EO|TRLI|ECLK|RTR, MI|TRO|RO|XOR|ECLK|EI|ES2, MI|COA|CE|II|EO|AI|EP],                                            # 072 - zeropage,Y   ; oper,Y
        [MI|COA|CE|RO|TRLI, MI|COA|CE|FEC|RO|TRHI|ECLK, MI|TRO|RO|XOR|ECLK|EI|ES2, MI|COA|CE|II|EO|AI|EP],                                                     # 073 - absolute     ; oper
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|XOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO|RO|XOR|ECLK|EI|ES2, MI|COA|CE|II|EO|AI|EP],                      # 074 - absolute,X   ; oper,X
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|YOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO|RO|XOR|ECLK|EI|ES2, MI|COA|CE|II|EO|AI|EP],                      # 075 - absolute,Y   ; oper,Y
        [MI|COA|CE|FEC|RO|EI|ES1|ADD|XOX1|ES2, EO|TRLI|RTR, MI|TRO, RO|TRLI|ECLK, MI|TRO|RO|XOR|ECLK|EI|ES2, MI|COA|CE|II|EO|AI|EP],                           # 076 - (indirect,X) ; (oper,X)
        [MI|COA|CE|FEC|RO|EI|ES1|ADD|YOX1|ES2, EO|TRLI|RTR, MI|TRO, RO|TRLI|ECLK, MI|TRO|RO|XOR|ECLK|EI|ES2, MI|COA|CE|II|EO|AI|EP],                           # 077 - (indirect,Y) ; (oper,Y)
        [MI|COA|CE|FEC|RO|TRLI|RTR|ECLK, MI|TRO|RO|ECLK|EI|ES1|XOX1|ES2|ADD|CTR, EO|TRLI|ECLK|TRHI|CTR, MI|TRO|RO|XOR|ECLK|EI|ES2, MI|COA|CE|II|EO|AI|EP],     # 078 - (indirect),X ; (oper),X
        [MI|COA|CE|FEC|RO|TRLI|RTR|ECLK, MI|TRO|RO|ECLK|EI|ES1|YOX1|ES2|ADD|CTR, EO|TRLI|ECLK|TRHI|CTR, MI|TRO|RO|XOR|ECLK|EI|ES2, MI|COA|CE|II|EO|AI|EP],     # 079 - (indirect),Y ; (oper),Y
        
        # INC # Increment Memory by One                                                                                                                        # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|RO|TRLI|ECLK|RTR, MI|TRO|RO|ECLK|EI|ES2|INC, EO|RI, MI|COA|CE|II|EP],                                                                   # 080 - zeropage     ; oper
        [MI|COA|CE|FEC|RO|EI|ES1|XOX1|ES2|ADD, EO|TRLI|ECLK|RTR, MI|TRO|RO|ECLK|EI|ES2|INC, EO|RI, MI|COA|CE|II|EP],                                           # 081 - zeropage,X   ; oper,X
        [MI|COA|CE|FEC|RO|EI|ES1|YOX1|ES2|ADD, EO|TRLI|ECLK|RTR, MI|TRO|RO|ECLK|EI|ES2|INC, EO|RI, MI|COA|CE|II|EP],                                           # 082 - zeropage,Y   ; oper,Y
        [MI|COA|CE|RO|TRLI, MI|COA|CE|FEC|RO|TRHI|ECLK, MI|TRO|RO|ECLK|EI|ES2|INC, EO|RI, MI|COA|CE|II|EP],                                                    # 083 - absolute     ; oper
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|XOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO|RO|ECLK|EI|ES2|INC, EO|RI, MI|COA|CE|II|EP],                     # 084 - absolute,X   ; oper,X
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|YOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO|RO|ECLK|EI|ES2|INC, EO|RI, MI|COA|CE|II|EP],                     # 085 - absolute,Y   ; oper,Y
        
        # INX # Increment Index X by One                                                                                                                       # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|XOX2|EI|ES2|INC, MI|COA|EO|XI, CE|II|EP],                                                                                               # 086 - implied     ; 
        
        # INY # Increment Index Y by One                                                                                                                       # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|YOX2|EI|ES2|DEC, MI|COA|EO|YI, CE|II|EP],                                                                                               # 087 - implied      ; 
        
        # JMP # Jump to new location                                                                                                                           # OPC - ADDRESSING   ; ASSEMBLER
        [RO|CIDL, MI|COA|RO|CIDH|RCC, MI|COA|BR|RCC|J, MI|COA|RCC|FEC, MI|COA|CE|II|EP],                                                                       # 088 - absolute     ; oper
        [RO|CIDL, MI|COA|RO|CIDH|RCC, MI|COA|BR|RCC|J, RCC|CE|RO|CIDL, MI|COA|RO|CIDH, MI|COA|CE|FEC|BR, CE|II|EP],                                            # 089 - indirect     ; (oper)
        
        # JSR # Jump to new location Saving Return Address                                                                                                     # OPC - ADDRESSING   ; ASSEMBLER
        [RO|CIDL, MI|COA|CE|RO|CIDH, MI|SPAO|CODH|RI|SPE, MI|SPAO|CODL|RI|SPE, MI|COA|BR|J, MI|COA|CE|FEC|BR, CE|II|EP],                                       # 090 - absolute     ; oper
        
        # LDA # Load Accumulator with Memory                                                                                                                   # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|RO|AI, MI|COA|LD, CE|II|EP],                                                                                                            # 091 - immediate    ; #oper
        [MI|COA|CE|FEC|RO|TRLI|RTR, MI|TRO, MI|COA|CE|RO|AI, LD|II|EP],                                                                                        # 092 - zeropage     ; oper
        [MI|COA|CE|FEC|RO|EI|ES1|XOX1|ES2|ADD, EO|TRLI|RTR, MI|TRO, MI|COA|CE|RO|AI, LD|II|EP],                                                                # 093 - zeropage,X   ; oper,X
        [MI|COA|CE|FEC|RO|EI|ES1|YOX1|ES2|ADD, EO|TRLI|RTR, MI|TRO, MI|COA|CE|RO|AI, LD|II|EP],                                                                # 094 - zeropage,Y   ; oper,Y
        [MI|COA|CE|RO|TRLI, MI|COA|CE|FEC|RO|TRHI, MI|TRO, MI|COA|CE|RO|AI, LD|II|EP],                                                                         # 095 - absolute     ; oper
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|XOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO|ECLK, MI|COA|CE|RO|AI, LD|II|EP],                                # 096 - absolute,X   ; oper,X
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|YOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO|ECLK, MI|COA|CE|RO|AI, LD|II|EP],                                # 097 - absolute,Y   ; oper,Y
        [MI|COA|CE|FEC|RO|EI|ES1|ADD|XOX1|ES2, EO|TRLI|RTR, MI|TRO, RO|TRLI|ECLK, MI|TRO|ECLK, MI|COA|CE|RO|AI, LD|II|EP],                                     # 098 - (indirect,X) ; (oper,X)
        [MI|COA|CE|FEC|RO|EI|ES1|ADD|YOX1|ES2, EO|TRLI|RTR, MI|TRO, RO|TRLI|ECLK, MI|TRO|ECLK, MI|COA|CE|RO|AI, LD|II|EP],                                     # 099 - (indirect,Y) ; (oper,Y)
        [MI|COA|CE|FEC|RO|TRLI|RTR|ECLK, MI|TRO|RO|ECLK|EI|ES1|XOX1|ES2|ADD|CTR, EO|TRLI|ECLK|TRHI|CTR, MI|TRO|ECLK, MI|COA|CE|RO|AI, LD|II|EP],               # 100 - (indirect),X ; (oper),X
        [MI|COA|CE|FEC|RO|TRLI|RTR|ECLK, MI|TRO|RO|ECLK|EI|ES1|YOX1|ES2|ADD|CTR, EO|TRLI|ECLK|TRHI|CTR, MI|TRO|ECLK, MI|COA|CE|RO|AI, LD|II|EP],               # 101 - (indirect),Y ; (oper),Y
        
        # LDX # Load Index X with Memory                                                                                                                       # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|RO|XI, MI|COA|XOX1|ES1|LD, CE|II|EP],                                                                                                   # 102 - immediate    ; #oper
        [MI|COA|CE|FEC|RO|TRLI|RTR, MI|TRO|ECLK, MI|COA|CE|RO|XI, XOX1|ES1|LD|II|EP],                                                                          # 103 - zeropage     ; oper
        [MI|COA|CE|FEC|RO|EI|ES1|YOX1|ES2|ADD, EO|TRLI|ECLK|RTR, MI|TRO|ECLK, MI|COA|CE|RO|XI, XOX1|ES1|LD|II|EP],                                             # 104 - zeropage,Y   ; oper,Y
        [MI|COA|CE|RO|TRLI, MI|COA|CE|FEC|RO|TRHI, MI|TRO|ECLK, MI|COA|CE|RO|XI, XOX1|ES1|LD|II|EP],                                                           # 105 - absolute     ; oper
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|YOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO|ECLK, MI|COA|CE|RO|XI, XOX1|ES1|LD|II|EP],                       # 106 - absolute,Y   ; oper,Y  
    
        # LDY # Load Index Y with Memory                                                                                                                       # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|RO|YI, MI|COA|YOX1|ES1|LD, CE|II|EP],                                                                                                   # 107 - immediate    ; #oper
        [MI|COA|CE|FEC|RO|TRLI|RTR, MI|TRO|ECLK, MI|COA|CE|RO|YI, YOX1|ES1|LD|II|EP],                                                                          # 108 - zeropage     ; oper
        [MI|COA|CE|FEC|RO|EI|ES1|XOX1|ES2|ADD, EO|TRLI|ECLK|RTR, MI|TRO|ECLK, MI|COA|CE|RO|YI, YOX1|ES1|LD|II|EP],                                             # 109 - zeropage,X   ; oper,X
        [MI|COA|CE|RO|TRLI, MI|COA|CE|FEC|RO|TRHI, MI|TRO|ECLK, MI|COA|CE|RO|YI, YOX1|ES1|LD|II|EP],                                                           # 110 - absolute     ; oper
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|XOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO|ECLK, MI|COA|CE|RO|YI, YOX1|ES1|LD|II|EP],                       # 111 - absolute,X   ; oper,X
        
        # LSR # Shift One Bit Right (Memory or Accumulator)                                                                                                    # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|LSHFR|EI, MI|COA|EO|AI, CE|II|EP],                                                                                                      # 112 - accumulator  ; A
        [MI|COA|CE|FEC|RO|TRLI|RTR, MI|TRO, RO|AI, LSHFR|EI, MI|COA|CE|II|EO|AI|EP],                                                                           # 113 - zeropage     ; oper
        [MI|COA|CE|FEC|RO|EI|ES1|XOX1|ES2|ADD, EO|TRLI|RTR, MI|TRO, RO|AI, LSHFR|EI, MI|COA|CE|II|EO|AI|EP],                                                   # 114 - zeropage,X   ; oper,X
        [MI|COA|CE|FEC|RO|EI|ES1|YOX1|ES2|ADD, EO|TRLI|RTR, MI|TRO, RO|AI, LSHFR|EI, MI|COA|CE|II|EO|AI|EP],                                                   # 115 - zeropage,Y   ; oper,Y
        [MI|COA|CE|RO|TRLI, MI|COA|CE|FEC|RO|TRHI, MI|TRO, RO|AI, LSHFR|EI, MI|COA|CE|II|EO|AI|EP],                                                            # 116 - absolute     ; oper
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|XOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO, RO|AI, LSHFR|EI, MI|COA|CE|II|EO|AI|EP],                        # 117 - absolute,X   ; oper,X
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|YOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO, RO|AI, LSHFR|EI, MI|COA|CE|II|EO|AI|EP],                        # 118 - zeropage,Y   ; oper,Y
            
        # ORA # OR Memory with Accumulator                                                                                                                     # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|RO|OR|EI|ES2, MI|COA|EO|AI, CE|II|EP],                                                                                                  # 119 - immediate    ; #oper
        [MI|COA|CE|FEC|RO|TRLI|ECLK|RTR, MI|TRO|RO|OR|ECLK|EI|ES2, MI|COA|CE|II|EO|AI|EP],                                                                     # 120 - zeropage     ; oper
        [MI|COA|CE|FEC|RO|EI|ES1|XOX1|ES2|ADD, EO|TRLI|ECLK|RTR, MI|TRO|RO|OR|ECLK|EI|ES2, MI|COA|CE|II|EO|AI|EP],                                             # 121 - zeropage,X   ; oper,X
        [MI|COA|CE|FEC|RO|EI|ES1|YOX1|ES2|ADD, EO|TRLI|ECLK|RTR, MI|TRO|RO|OR|ECLK|EI|ES2, MI|COA|CE|II|EO|AI|EP],                                             # 122 - zeropage,Y   ; oper,Y
        [MI|COA|CE|RO|TRLI, MI|COA|CE|FEC|RO|TRHI|ECLK, MI|TRO|RO|OR|ECLK|EI|ES2, MI|COA|CE|II|EO|AI|EP],                                                      # 123 - absolute     ; oper
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|XOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO|RO|OR|ECLK|EI|ES2, MI|COA|CE|II|EO|AI|EP],                       # 124 - absolute,X   ; oper,X  
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|YOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO|RO|OR|ECLK|EI|ES2, MI|COA|CE|II|EO|AI|EP],                       # 125 - absolute,Y   ; oper,Y
        [MI|COA|CE|FEC|RO|EI|ES1|ADD|XOX1|ES2, EO|TRLI|RTR, MI|TRO, RO|TRLI|ECLK, MI|TRO|RO|OR|ECLK|EI|ES2, MI|COA|CE|II|EO|AI|EP],                            # 126 - (indirect,X) ; (oper,X)
        [MI|COA|CE|FEC|RO|EI|ES1|ADD|YOX1|ES2, EO|TRLI|RTR, MI|TRO, RO|TRLI|ECLK, MI|TRO|RO|OR|ECLK|EI|ES2, MI|COA|CE|II|EO|AI|EP],                            # 127 - (indirect,Y) ; (oper,Y)
        [MI|COA|CE|FEC|RO|TRLI|RTR|ECLK, MI|TRO|RO|ECLK|EI|ES1|XOX1|ES2|ADD|CTR, EO|TRLI|ECLK|TRHI|CTR, MI|TRO|RO|OR|ECLK|EI|ES2, MI|COA|CE|II|EO|AI|EP],      # 128 - (indirect),X ; (oper),X
        [MI|COA|CE|FEC|RO|TRLI|RTR|ECLK, MI|TRO|RO|ECLK|EI|ES1|YOX1|ES2|ADD|CTR, EO|TRLI|ECLK|TRHI|CTR, MI|TRO|RO|OR|ECLK|EI|ES2, MI|COA|CE|II|EO|AI|EP],      # 129 - (indirect),Y ; (oper),Y
        
        # PHA # Push Accumulator on Stack                                                                                                                      # OPC - ADDRESSING   ; ASSEMBLER
        [FEC, MI|SPAO|SPE|AO|RI, MI|COA|CE|II|EP],                                                                                                             # 130 - implied      ;
        
        # PHP # Push Processor Status on Stack                                                                                                                 # OPC - ADDRESSING   ; ASSEMBLER
        [FEC, MI|SPAO|SPE|SRO|RI, MI|COA|CE|II|EP],                                                                                                            # 131 - implied      ;
        
        # PLA # Pull Accumulator from Stack                                                                                                                    # OPC - ADDRESSING   ; ASSEMBLER
        [FEC|DSP|SPE, MI|SPAO, RO|AI, MI|COA|CE|II|EP],                                                                                                        # 132 - implied      ;
        
        # PLP # Pull Processor Status from Stack                                                                                                               # OPC - ADDRESSING   ; ASSEMBLER
        [FEC|DSP|SPE, MI|SPAO, RO|SRDI, MI|COA|CE|II|EP],                                                                                                      # 133 - implied      ;
        
        # ROL # Rotate One Bit Left (Memory or Accumulator)                                                                                                    # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|ROL|EI, MI|COA|EO|AI, CE|II|EP],                                                                                                        # 134 - accumulator  ; A
        [MI|COA|CE|FEC|RO|TRLI|RTR, MI|TRO, RO|AI, ROL|EI, MI|COA|CE|II|EO|AI|EP],                                                                             # 135 - zeropage     ; oper
        [MI|COA|CE|FEC|RO|EI|ES1|XOX1|ES2|ADD, EO|TRLI|RTR, MI|TRO, RO|AI, ROL|EI, MI|COA|CE|II|EO|AI|EP],                                                     # 136 - zeropage,X   ; oper,X
        [MI|COA|CE|FEC|RO|EI|ES1|YOX1|ES2|ADD, EO|TRLI|RTR, MI|TRO, RO|AI, ROL|EI, MI|COA|CE|II|EO|AI|EP],                                                     # 137 - zeropage,Y   ; oper,Y
        [MI|COA|CE|RO|TRLI, MI|COA|CE|FEC|RO|TRHI, MI|TRO, RO|AI, ROL|EI, MI|COA|CE|II|EO|AI|EP],                                                              # 138 - absolute     ; oper
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|XOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO, RO|AI, ROL|EI, MI|COA|CE|II|EO|AI|EP],                          # 139 - absolute,X   ; oper,X
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|YOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO, RO|AI, ROL|EI, MI|COA|CE|II|EO|AI|EP],                          # 140 - zeropage,Y   ; oper,Y
        
        # ROR # Rotate One Bit Right (Memory or Accumulator)                                                                                                   # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|ROR|EI, MI|COA|EO|AI, CE|II|EP],                                                                                                        # 141 - accumulator  ; A
        [MI|COA|CE|FEC|RO|TRLI|RTR, MI|TRO, RO|AI, ROR|EI, MI|COA|CE|II|EO|AI|EP],                                                                             # 142 - zeropage     ; oper
        [MI|COA|CE|FEC|RO|EI|ES1|XOX1|ES2|ADD, EO|TRLI|RTR, MI|TRO, RO|AI, ROR|EI, MI|COA|CE|II|EO|AI|EP],                                                     # 143 - zeropage,X   ; oper,X
        [MI|COA|CE|FEC|RO|EI|ES1|YOX1|ES2|ADD, EO|TRLI|RTR, MI|TRO, RO|AI, ROR|EI, MI|COA|CE|II|EO|AI|EP],                                                     # 144 - zeropage,Y   ; oper,Y
        [MI|COA|CE|RO|TRLI, MI|COA|CE|FEC|RO|TRHI, MI|TRO, RO|AI, ROR|EI, MI|COA|CE|II|EO|AI|EP],                                                              # 145 - absolute     ; oper
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|XOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO, RO|AI, ROR|EI, MI|COA|CE|II|EO|AI|EP],                          # 146 - absolute,X   ; oper,X
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|YOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO, RO|AI, ROR|EI, MI|COA|CE|II|EO|AI|EP],                          # 147 - zeropage,Y   ; oper,Y
        
        # RTI # Return from Interrupt                                                                                                                          # OPC - ADDRESSING   ; ASSEMBLER
        [DSP|SPE|ECLK, MI|SPAO|RO|SRDI|DSP|SPE|FI|ECLK, MI|SPAO|RO|CIDL|DSP|SPE, MI|SPAO|RO|CIDH, J, MI|COA|CE|IE|EP|CI],                                      # 148 - implied      ;
        
        # RTI # Return from Subroutine                                                                                                                         # OPC - ADDRESSING   ; ASSEMBLER
        [DSP|SPE, MI|SPAO|RO|CIDL|DSP|SPE, MI|SPAO|RO|CIDH, MI|COA|J|BR, MI|COA|CE|FEC|BR, CE|II|EP],                                                          # 149 - implied      ;        
        
        # SUB # Subtract Memory from Accumulator with Borrow                                                                                                   # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|RO|SU|EI|ES2|FI, MI|COA|EO|AI, CE|II|EP],                                                                                               # 150 - immediate    ; #oper
        [MI|COA|CE|FEC|RO|TRLI|ECLK|RTR, MI|TRO|RO|ECLK|EI|ES2|SU|FI, MI|COA|CE|II|EO|AI|EP],                                                                  # 151 - zeropage     ; oper
        [MI|COA|CE|FEC|RO|EI|ES1|XOX1|ES2|ADD, EO|TRLI|ECLK|RTR, MI|TRO|RO|ECLK|EI|ES2|SU|FI, MI|COA|CE|II|EO|AI|EP],                                          # 152 - zeropage,X   ; oper,X
        [MI|COA|CE|FEC|RO|EI|ES1|YOX1|ES2|ADD, EO|TRLI|ECLK|RTR, MI|TRO|RO|ECLK|EI|ES2|SU|FI, MI|COA|CE|II|EO|AI|EP],                                          # 153 - zeropage,Y   ; oper,Y
        [MI|COA|CE|RO|TRLI, MI|COA|CE|FEC|RO|TRHI|ECLK, MI|TRO|RO|ECLK|EI|ES2|SU|FI, MI|COA|CE|II|EO|AI|EP],                                                   # 154 - absolute     ; oper
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|XOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO|RO|ECLK|EI|ES2|SU|FI, MI|COA|CE|II|EO|AI|EP],                    # 155 - absolute,X   ; oper,X
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|YOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO|RO|ECLK|EI|ES2|SU|FI, MI|COA|CE|II|EO|AI|EP],                    # 156 - absolute,Y   ; oper,Y
        [MI|COA|CE|FEC|RO|EI|ES1|ADD|XOX1|ES2, EO|TRLI|RTR, MI|TRO, RO|TRLI|ECLK, MI|TRO|RO|ECLK|EI|ES2|SU|FI, MI|COA|CE|II|EO|AI|EP],                         # 157 - (indirect,X) ; (oper,X)
        [MI|COA|CE|FEC|RO|EI|ES1|ADD|YOX1|ES2, EO|TRLI|RTR, MI|TRO, RO|TRLI|ECLK, MI|TRO|RO|ECLK|EI|ES2|SU|FI, MI|COA|CE|II|EO|AI|EP],                         # 158 - (indirect,Y) ; (oper,Y)
        [MI|COA|CE|FEC|RO|TRLI|RTR|ECLK, MI|TRO|RO|ECLK|EI|ES1|XOX1|ES2|ADD|CTR, EO|TRLI|ECLK|TRHI|CTR, MI|TRO|RO|ECLK|EI|ES2|SU|FI, MI|COA|CE|II|EO|AI|EP],   # 159 - (indirect),X ; (oper),X
        [MI|COA|CE|FEC|RO|TRLI|RTR|ECLK, MI|TRO|RO|ECLK|EI|ES1|YOX1|ES2|ADD|CTR, EO|TRLI|ECLK|TRHI|CTR, MI|TRO|RO|ECLK|EI|ES2|SU|FI, MI|COA|CE|II|EO|AI|EP],   # 160 - (indirect),Y ; (oper),Y
        
        # SEC # Set Carry Flag                                                                                                                                 # OPC - ADDRESSING   ; ASSEMBLER
        [FEC|SC, MI|COA|CE|II|EP],                                                                                                                             # 161 - implied      ;
        
        # SEI # Set Interrupt Disable Status                                                                                                                   # OPC - ADDRESSING   ; ASSEMBLER
        [FEC|SI, MI|COA|CE|II|EP],                                                                                                                             # 162 - implied      ;
        
        # STA # Store Accumulator in Memory                                                                                                                    # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|RO|TRLI|RTR, MI|TRO|AO|RI, MI|COA|CE|II|EP],                                                                                            # 163 - zeropage     ; oper
        [MI|COA|CE|FEC|RO|EI|ES1|XOX1|ES2|ADD, EO|TRLI|RTR, MI|TRO|AO|RI, MI|COA|CE|II|EP],                                                                    # 164 - zeropage,X   ; oper,X
        [MI|COA|CE|FEC|RO|EI|ES1|YOX1|ES2|ADD, EO|TRLI|RTR, MI|TRO|AO|RI, MI|COA|CE|II|EP],                                                                    # 165 - zeropage,Y   ; oper,Y
        [MI|COA|CE|RO|TRLI, MI|COA|CE|FEC|RO|TRHI, MI|TRO|AO|RI, MI|COA|CE|II|EP],                                                                             # 166 - absolute     ; oper
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|XOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO|AO|RI|ECLK, MI|COA|CE|II|EP],                                    # 167 - absolute,X   ; oper,X
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|YOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO|AO|RI|ECLK, MI|COA|CE|II|EP],                                    # 168 - absolute,Y   ; oper,Y
        [MI|COA|CE|FEC|RO|EI|ES1|ADD|XOX1|ES2, EO|TRLI|RTR, MI|TRO, RO|TRLI, MI|TRO|AO|RI, MI|COA|CE|II|EP],                                                   # 169 - (indirect,X) ; (oper,X)
        [MI|COA|CE|FEC|RO|EI|ES1|ADD|YOX1|ES2, EO|TRLI|RTR, MI|TRO, RO|TRLI, MI|TRO|AO|RI, MI|COA|CE|II|EP],                                                   # 170 - (indirect,Y) ; (oper,Y)
        [MI|COA|CE|FEC|RO|TRLI|RTR|ECLK, MI|TRO|RO|ECLK|EI|ES1|XOX1|ES2|ADD|CTR, EO|TRLI|ECLK|TRHI|CTR, MI|TRO|AO|RI, MI|COA|CE|II|EP],                        # 171 - (indirect),X ; (oper),X
        [MI|COA|CE|FEC|RO|TRLI|RTR|ECLK, MI|TRO|RO|ECLK|EI|ES1|YOX1|ES2|ADD|CTR, EO|TRLI|ECLK|TRHI|CTR, MI|TRO|AO|RI, MI|COA|CE|II|EP],                        # 172 - (indirect),Y ; (oper),Y
        
        # STX # Store Index X in Memory                                                                                                                        # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|RO|TRLI|RTR, MI|TRO|XO|RI, MI|COA|CE|II|EP],                                                                                            # 173 - zeropage     ; oper
        [MI|COA|CE|FEC|RO|EI|ES1|YOX1|ES2|ADD, EO|TRLI|RTR, MI|TRO|XO|RI, MI|COA|CE|II|EP],                                                                    # 174 - zeropage,Y   ; oper,Y
        [MI|COA|CE|RO|TRLI, MI|COA|CE|FEC|RO|TRHI, MI|TRO|XO|RI, MI|COA|CE|II|EP],                                                                             # 175 - absolute     ; oper
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|YOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO|XO|RI|ECLK, MI|COA|CE|II|EP],                                    # 176 - absolute,Y   ; oper,Y
        
        # STY # Store Index Y in Memory                                                                                                                        # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|RO|TRLI|RTR, MI|TRO|YO|RI, MI|COA|CE|II|EP],                                                                                            # 177 - zeropage     ; oper
        [MI|COA|CE|FEC|RO|EI|ES1|XOX1|ES2|ADD, EO|TRLI|RTR, MI|TRO|YO|RI, MI|COA|CE|II|EP],                                                                    # 178 - zeropage,X   ; oper,X
        [MI|COA|CE|RO|TRLI, MI|COA|CE|FEC|RO|TRHI, MI|TRO|YO|RI, MI|COA|CE|II|EP],                                                                             # 179 - absolute     ; oper
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|XOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO|YO|RI|ECLK, MI|COA|CE|II|EP],                                    # 180 - absolute,X   ; oper,X

        # TAX # Transfer Accumulator to Index X                                                                                                                # OPC - ADDRESSING   ; ASSEMBLER
        [FEC|AO|XI, MI|COA|CE|II|EP],                                                                                                                          # 181 - implied      ;
        
        # TAY # Transfer Accumulator to Index Y                                                                                                                # OPC - ADDRESSING   ; ASSEMBLER
        [FEC|AO|YI, MI|COA|CE|II|EP],                                                                                                                          # 182 - implied      ;
        
        # TSX # Transfer Stack Pointer to Index X                                                                                                              # OPC - ADDRESSING   ; ASSEMBLER
        [FEC|SPDO|XI, MI|COA|CE|II|EP],                                                                                                                        # 183 - implied      ;
        
        # TSA # Transfer Index X to Accumulator                                                                                                                # OPC - ADDRESSING   ; ASSEMBLER
        [FEC|XO|AI, MI|COA|CE|II|EP],                                                                                                                          # 184 - implied      ;
        
        # TXS # Transfer Index X to Stack Register                                                                                                             # OPC - ADDRESSING   ; ASSEMBLER
        [FEC|XO|SPI, MI|COA|CE|II|EP],                                                                                                                         # 185 - implied      ;
        
        # TYA # Transfer Index Y to Accumulator                                                                                                                # OPC - ADDRESSING   ; ASSEMBLER
        [FEC|YO|AI, MI|COA|CE|II|EP],                                                                                                                          # 186 - implied      ;
        
        # HLT # Halt Operation                                                                                                                                 # OPC - ADDRESSING   ; ASSEMBLER
        [HLT],                                                                                                                                                 # 187 - implied      ;
        
        # OUT # Output to ASCII Terminal                                                                                                                       # OPC - ADDRESSING   ; ASSEMBLER
        [AO|OI|FEC, MI|COA|CE|II|EP],                                                                                                                          # 188 - implied      ;
    ]
    
    rom_data = createMicroCode(instructions_data)
    export(rom_data)
    
main()