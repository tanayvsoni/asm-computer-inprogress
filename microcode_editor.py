# Section 1 #
MI    = 0b10_0000_000_0000_0000_0000_0000_0000_0000_00  # Memory address register in
COA   = 0b01_0000_000_0000_0000_0000_0000_0000_0000_00  # Program counter address bus out

# Decoder 1 #
CIDL  = 0b00_0001_000_0000_0000_0000_0000_0000_0000_00  # Program counter LSB in
CIDH  = 0b00_0010_000_0000_0000_0000_0000_0000_0000_00  # Program counter MSB in
RI    = 0b00_0011_000_0000_0000_0000_0000_0000_0000_00  # RAM data in
EI    = 0b00_0100_000_0000_0000_0000_0000_0000_0000_00  # ALU in
AI    = 0b00_0101_000_0000_0000_0000_0000_0000_0000_00  # A register in
XI    = 0b00_0110_000_0000_0000_0000_0000_0000_0000_00  # X register in
YI    = 0b00_0111_000_0000_0000_0000_0000_0000_0000_00  # Y register in
SRDI  = 0b00_1000_000_0000_0000_0000_0000_0000_0000_00  # Status Register data bus in
SPI   = 0b0010010000000000000000000000000000  # Stack pointer in #
TRLI  = 0b0000000000000000000000000100000000  # Transfer register LSB in #
TRHI  = 0b0010110000000000000000000000000000  # Transfer register MSB in # 
OI    = 0b0011000000000000000000000000000000  # Output register in #
FI    = 0b0000000000000000001000000000000000  # Status register in #
II    = 0b0000000000000000000010000000000000  # Instruction register in #

# OUTS #
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
CMP   = 0b0000000000100100000000000000000000  # Compare 
INC   = 0b0000000000110100000000000000000000  # Increment x
DEC   = 0b0000000000111000000000000000000000  # Deccrement 
ADD   = 0b0000000000111100000000000000000000  # Add without Carry
BIT   = 0b0000000000111100000000000000000000  # Bitwise Accumulator with Memory
LD    = 0b0000000000111100000000000000000000  # Load

# GENERAL #
DSP   = 0b00000000001010000000000000000000000  # Decrement stack pointer #
CLC   = 0b00000000001011000000000000000000000  # Clear carry flag #
CLV   = 0b00000000001100000000000000000000000  # Clear overflow flag #
CSB   = 0b00000000001100000000000000000000000  # Counter Dec #
SC    = 0b00000000001100000000000000000000000  # Set Carry Flag #
SI    = 0b00000000001100000000000000000000000  # Set Interupt Disable #
CI    = 0b00000000001100000000000000000000000  # Clear Interupt Disable #
CE    = 0b00000000000000100000000000000000000  # Increment program counter #
J     = 0b00000000000000010000000000000000000  # Load program counter #
SPE   = 0b00000000000000001000000000000000000  # Stack pointer enable #
IE    = 0b00000000000000000100000000000000000  # Interupt clear/disable #
IJ    = 0b00000000000000000010000000000000000  # Jump to interupt subroutine ($BFFA) #
EP    = 0b00000000000000000000100000000000000  # End program #
NOP   = 0b00000000000000000000001000000000000  # No operation #
FEC   = 0b00000000000000000000000100000000000  # Fetch into pipeline
DRF   = 0b00000000000000000000000100000000000  # Direct Fetch into Instruction
RTR   = 0b00000000000000000000000010000000000  # Reset Transfer register MSB
ECLK  = 0b00000000000000000000000000001000000  # CLK invert for ALU
CTR   = 0b00000000000000000000000000000000001  # Carry into TRHI
BR    = 0b00000000000000000000000000000000001  # Branch Invert MI CLK

def createMicroCode(data):  
    """
    Creates the microcode for the computer
    """
    rom_data = [0] * (1024 * 256)
    
    for flag in range(0, 7):
        for instr in range(0, 256):
            for substep in range(0, 9):

                # Address setup and storing data into rom_data
                address = (flag << 11) | (instr << 3) | substep
                 
                try: rom_data[address] = data[instr][substep]
                except: rom_data[address] = 0
                
                conditionalJumps_Expections(flag,instr,substep,address,rom_data)
       
    return rom_data

def substeps_CJ(substep, rom_data, address):
    match substep:
        case 0: rom_data[address] = RO|CIDL
        case 1: rom_data[address] = MI|COA|RO|CIDH 
        case 2: rom_data[address] = MI|COA|BR|J
        case 3: rom_data[address] = MI|COA|CE|FEC|BR
        case 4: rom_data[address] = CE|II|EP
     

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
        for code in rom_data:
            microcode.write("%s\n" % hex(code)[2:])

def main():    
    # Instruction Data
    instructions_data = [
        # NOP # No operation                                                                                                                                   # OPC - ADDRESSING    ; ASSEMBLER
        [MI|COA|CE|DRF|II|EP|NOP],                                                                                                                             # 000 - implied       ; 
        
        # ADC # Add with Carry                                                                                                                                 # OPC - ADDRESSING    ; ASSEMBLER
        [MI|COA|CE|FEC|RO|EI|ES2|FI, MI|COA|CE|II|EO|AI|EP],                                                                                                   # 001 - immediate     ; #oper
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
        [MI|COA|CE|FEC|RO|AND|EI|ES2, MI|COA|CE|II|EO|AI|EP],                                                                                                  # 012 - immediate     ; #oper
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
        [MI|COA|CE|FEC|ASHFL|EI, MI|COA|CE|II|EO|AI|EP],                                                                                                       # 023 - accumulator  ; A
        [MI|COA|CE|FEC|RO|TRLI|RTR, MI|TRO, RO|AI, ASHFL|EI, MI|COA|CE|II|EO|AI|EP],                                                                           # 024 - zeropage     ; oper
        [MI|COA|CE|FEC|RO|EI|ES1|XOX1|ES2|ADD, EO|TRLI|RTR, MI|TRO, RO|AI, ASHFL|EI, MI|COA|CE|II|EO|AI|EP],                                                   # 025 - zeropage,X   ; oper,X
        [MI|COA|CE|FEC|RO|EI|ES1|YOX1|ES2|ADD, EO|TRLI|RTR, MI|TRO, RO|AI, ASHFL|EI, MI|COA|CE|II|EO|AI|EP],                                                   # 026 - zeropage,Y   ; oper,Y
        [MI|COA|CE|RO|TRLI, MI|COA|CE|FEC|RO|TRHI, MI|TRO, RO|AI, ASHFL|EI, MI|COA|CE|II|EO|AI|EP],                                                            # 027 - absolute     ; oper
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|XOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO, RO|AI, ASHFL|EI, MI|COA|CE|II|EO|AI|EP],                        # 028 - absolute,X   ; oper,X
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|YOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO, RO|AI, ASHFL|EI, MI|COA|CE|II|EO|AI|EP],                        # 029 - absolute,Y   ; oper,Y
        
        # BCC # Branch on Carry Clear                                                                                                                          # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|DRF|II|EP|NOP],                                                                                                                             # 030 - relative     ; oper
        
        # BCS # Breanch on Carry Set                                                                                                                           # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|DRF|II|EP|NOP],                                                                                                                             # 031 - relative     ; oper
        
        # BEQ # Branch on Zero                                                                                                                                 # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|DRF|II|EP|NOP],                                                                                                                             # 032 - relative     ; oper
        
        # BIT # Test Bits in Memory with Accumulator                                                                                                           # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|RO|TRLI|RTR|ECLK, MI|TRO|RO|BIT|ES2|ECLK, MI|COA|CE|II|EP],                                                                             # 033 - zeropage     ; oper
        [MI|COA|CE|RO|TRLI, MI|COA|CE|FEC|RO|TRHI|ECLK, MI|TRO|RO|BIT|ECLK|ES2, MI|COA|CE|II|EP],                                                              # 034 - absolute     ; oper
        
        # BMI # Branch on Minus                                                                                                                                # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|DRF|II|EP|NOP],                                                                                                                             # 035 - relative     ; oper
        
        # BNE # Branch on not Zero                                                                                                                             # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|DRF|II|EP|NOP],                                                                                                                             # 036 - relative     ; oper
        
        # BPL # Branch on Plus                                                                                                                                 # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|DRF|II|EP|NOP],                                                                                                                             # 037 - relative     ; oper
        
        # BRK # Hard/Soft Interrupt                                                                                                                            # OPC - ADDRESSING   ; ASSEMBLER
        [MI|SPAO|CODH|RI|SPE|SI|CSB, MI|SPAO|CODL|RI|SPE|CSB, MI|SPAO|SRO|RI|SPE, MI|COA|BR|IJ|J, MI|COA|CE|FEC|BR, CE|II|EP],                                 # 038 - implied      ;
        
        # BVC # Branch on Overflow Clear                                                                                                                       # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|DRF|II|EP|NOP],                                                                                                                             # 039 - relative     ; oper 
        
        # BVS # Branch on Overflow Set                                                                                                                         # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|DRF|II|EP|NOP],                                                                                                                             # 040 - relative     ; oper
        
        # CLC # Clear Carry Flag                                                                                                                               # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|DRF|II|EP|CLC|NOP],                                                                                                                         # 041 - implied      ; 
        
        # CLC # Clear Interupt Disable Bit                                                                                                                     # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|DRF|II|EP|CI|NOP],                                                                                                                          # 042 - implied      ; 
        
        # CLV # Clear Overflow Flag                                                                                                                            # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|DRF|II|EP|CLV|NOP],                                                                                                                         # 043 - implied      ; 
        
        # CMP # Compare Memory with Accumulator                                                                                                                # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|RO|CMP|ES2, MI|COA|CE|II|EP],                                                                                                           # 044 - immediate    ; #oper
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
        [MI|COA|CE|FEC|RO|CMP|XOX1|ES1|ES2, MI|COA|CE|II|EP],                                                                                                  # 055 - immediate    ; #oper
        [MI|COA|CE|FEC|RO|TRLI|ECLK|RTR, MI|TRO|RO|ECLK|CMP|XOX1|ES1|ES2, MI|COA|CE|II|EP],                                                                    # 056 - zeropage     ; oper
        [MI|COA|CE|RO|TRLI, MI|COA|CE|FEC|RO|TRHI|ECLK, MI|TRO|RO|ECLK|CMP|XOX1|ES1|ES2, MI|COA|CE|II|EP],                                                     # 057 - absolute     ; oper
        
        # CPY # Compare Memory with Index X                                                                                                                    # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|RO|CMP|YOX1|ES1|ES2, MI|COA|CE|II|EP],                                                                                                  # 058 - immediate    ; #oper
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
        [MI|COA|CE|FEC|XOX2|EI|ES2|DEC, MI|COA|CE|II|EO|XI|EP],                                                                                                # 067 - implied     ; 
        
        # DEC # Decrement Index Y by One                                                                                                                       # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|YOX2|EI|ES2|DEC, MI|COA|CE|II|EO|YI|EP],                                                                                                # 068 - implied      ; 
        
        # EOR # Exclusive-OR Memory with Accumulator                                                                                                           # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|RO|XOR|EI|ES2, MI|COA|CE|II|EO|AI|EP],                                                                                                  # 069 - immediate    ; #oper
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
        [MI|COA|CE|FEC|XOX2|EI|ES2|INC, MI|COA|CE|II|EO|XI|EP],                                                                                                # 086 - implied     ; 
        
        # INY # Increment Index Y by One                                                                                                                       # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|YOX2|EI|ES2|DEC, MI|COA|CE|II|EO|YI|EP],                                                                                                # 087 - implied      ; 
        
        # JMP # Jump to new location                                                                                                                           # OPC - ADDRESSING   ; ASSEMBLER
        [RO|CIDL, MI|COA|RO|CIDH, MI|COA|BR|J, MI|COA|CE|FEC|BR, CE|II|EP],                                                                                    # 088 - absolute     ; oper
        [RO|CIDL, MI|COA|RO|CIDH, MI|COA|BR|J, CE|RO|CIDL, MI|COA|RO|CIDH, MI|COA|CE|FEC|BR, CE|II|EP],                                                        # 089 - indirect     ; (oper)
        
        # JSR # Jump to new location Saving Return Address                                                                                                     # OPC - ADDRESSING   ; ASSEMBLER
        [RO|CIDL, MI|COA|CE|RO|CIDH, MI|SPAO|CODH|RI|SPE, MI|SPAO|CODL|RI|SPE, MI|COA|BR|J, MI|COA|CE|FEC|BR, CE|II|EP],                                       # 090 - absolute     ; oper
        
        # LDA # Load Accumulator with Memory                                                                                                                   # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|RO|AI, MI|COA|CE|II|LD|EP],                                                                                                             # 091 - immediate    ; #oper
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
        [MI|COA|CE|FEC|RO|XI, MI|COA|CE|II|XOX1|ES1|LD|EP],                                                                                                    # 102 - immediate    ; #oper
        [MI|COA|CE|FEC|RO|TRLI|RTR, MI|TRO|ECLK, MI|COA|CE|RO|XI, XOX1|ES1|LD|II|EP],                                                                          # 103 - zeropage     ; oper
        [MI|COA|CE|FEC|RO|EI|ES1|YOX1|ES2|ADD, EO|TRLI|ECLK|RTR, MI|TRO|ECLK, MI|COA|CE|RO|XI, XOX1|ES1|LD|II|EP],                                             # 104 - zeropage,Y   ; oper,Y
        [MI|COA|CE|RO|TRLI, MI|COA|CE|FEC|RO|TRHI, MI|TRO|ECLK, MI|COA|CE|RO|XI, XOX1|ES1|LD|II|EP],                                                           # 105 - absolute     ; oper
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|YOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO|ECLK, MI|COA|CE|RO|XI, XOX1|ES1|LD|II|EP],                       # 106 - absolute,Y   ; oper,Y  
    
        # LDY # Load Index Y with Memory                                                                                                                       # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|RO|YI, MI|COA|CE|II|YOX1|ES1|LD|EP],                                                                                                    # 107 - immediate    ; #oper
        [MI|COA|CE|FEC|RO|TRLI|RTR, MI|TRO|ECLK, MI|COA|CE|RO|YI, YOX1|ES1|LD|II|EP],                                                                          # 108 - zeropage     ; oper
        [MI|COA|CE|FEC|RO|EI|ES1|XOX1|ES2|ADD, EO|TRLI|ECLK|RTR, MI|TRO|ECLK, MI|COA|CE|RO|YI, YOX1|ES1|LD|II|EP],                                             # 109 - zeropage,X   ; oper,X
        [MI|COA|CE|RO|TRLI, MI|COA|CE|FEC|RO|TRHI, MI|TRO|ECLK, MI|COA|CE|RO|YI, YOX1|ES1|LD|II|EP],                                                           # 110 - absolute     ; oper
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|XOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO|ECLK, MI|COA|CE|RO|YI, YOX1|ES1|LD|II|EP],                       # 111 - absolute,X   ; oper,X
        
        # LSR # Shift One Bit Right (Memory or Accumulator)                                                                                                    # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|LSHFR|EI, MI|COA|CE|II|EO|AI|EP],                                                                                                       # 112 - accumulator  ; A
        [MI|COA|CE|FEC|RO|TRLI|RTR, MI|TRO, RO|AI, LSHFR|EI, MI|COA|CE|II|EO|AI|EP],                                                                           # 113 - zeropage     ; oper
        [MI|COA|CE|FEC|RO|EI|ES1|XOX1|ES2|ADD, EO|TRLI|RTR, MI|TRO, RO|AI, LSHFR|EI, MI|COA|CE|II|EO|AI|EP],                                                   # 114 - zeropage,X   ; oper,X
        [MI|COA|CE|FEC|RO|EI|ES1|YOX1|ES2|ADD, EO|TRLI|RTR, MI|TRO, RO|AI, LSHFR|EI, MI|COA|CE|II|EO|AI|EP],                                                   # 115 - zeropage,Y   ; oper,Y
        [MI|COA|CE|RO|TRLI, MI|COA|CE|FEC|RO|TRHI, MI|TRO, RO|AI, LSHFR|EI, MI|COA|CE|II|EO|AI|EP],                                                            # 116 - absolute     ; oper
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|XOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO, RO|AI, LSHFR|EI, MI|COA|CE|II|EO|AI|EP],                        # 117 - absolute,X   ; oper,X
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|YOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO, RO|AI, LSHFR|EI, MI|COA|CE|II|EO|AI|EP],                        # 118 - zeropage,Y   ; oper,Y
            
        # ORA # OR Memory with Accumulator                                                                                                                     # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|RO|OR|EI|ES2, MI|COA|CE|II|EO|AI|EP],                                                                                                   # 119 - immediate    ; #oper
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
        [MI|COA|CE|FEC|ROL|EI, MI|COA|CE|II|EO|AI|EP],                                                                                                         # 134 - accumulator  ; A
        [MI|COA|CE|FEC|RO|TRLI|RTR, MI|TRO, RO|AI, ROL|EI, MI|COA|CE|II|EO|AI|EP],                                                                             # 135 - zeropage     ; oper
        [MI|COA|CE|FEC|RO|EI|ES1|XOX1|ES2|ADD, EO|TRLI|RTR, MI|TRO, RO|AI, ROL|EI, MI|COA|CE|II|EO|AI|EP],                                                     # 136 - zeropage,X   ; oper,X
        [MI|COA|CE|FEC|RO|EI|ES1|YOX1|ES2|ADD, EO|TRLI|RTR, MI|TRO, RO|AI, ROL|EI, MI|COA|CE|II|EO|AI|EP],                                                     # 137 - zeropage,Y   ; oper,Y
        [MI|COA|CE|RO|TRLI, MI|COA|CE|FEC|RO|TRHI, MI|TRO, RO|AI, ROL|EI, MI|COA|CE|II|EO|AI|EP],                                                              # 138 - absolute     ; oper
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|XOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO, RO|AI, ROL|EI, MI|COA|CE|II|EO|AI|EP],                          # 139 - absolute,X   ; oper,X
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|YOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO, RO|AI, ROL|EI, MI|COA|CE|II|EO|AI|EP],                          # 140 - zeropage,Y   ; oper,Y
        
        # ROR # Rotate One Bit Right (Memory or Accumulator)                                                                                                   # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|ROR|EI, MI|COA|CE|II|EO|AI|EP],                                                                                                         # 141 - accumulator  ; A
        [MI|COA|CE|FEC|RO|TRLI|RTR, MI|TRO, RO|AI, ROR|EI, MI|COA|CE|II|EO|AI|EP],                                                                             # 142 - zeropage     ; oper
        [MI|COA|CE|FEC|RO|EI|ES1|XOX1|ES2|ADD, EO|TRLI|RTR, MI|TRO, RO|AI, ROR|EI, MI|COA|CE|II|EO|AI|EP],                                                     # 143 - zeropage,X   ; oper,X
        [MI|COA|CE|FEC|RO|EI|ES1|YOX1|ES2|ADD, EO|TRLI|RTR, MI|TRO, RO|AI, ROR|EI, MI|COA|CE|II|EO|AI|EP],                                                     # 144 - zeropage,Y   ; oper,Y
        [MI|COA|CE|RO|TRLI, MI|COA|CE|FEC|RO|TRHI, MI|TRO, RO|AI, ROR|EI, MI|COA|CE|II|EO|AI|EP],                                                              # 145 - absolute     ; oper
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|XOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO, RO|AI, ROR|EI, MI|COA|CE|II|EO|AI|EP],                          # 146 - absolute,X   ; oper,X
        [MI|COA|CE|RO|EI|ES1|ES2|ADD|CTR|YOX1, MI|COA|CE|FEC|RO|EO|TRLI|TRHI|ECLK|CTR, MI|TRO, RO|AI, ROR|EI, MI|COA|CE|II|EO|AI|EP],                          # 147 - zeropage,Y   ; oper,Y
        
        # RTI # Return from Interrupt                                                                                                                          # OPC - ADDRESSING   ; ASSEMBLER
        [DSP|SPE, MI|SPAO|RO|SRDI|DSP|SPE|FI, MI|SPAO|RO|CIDL|DSP|SPE, MI|SPAO|RO|CIDH, MI|COA|J|BR, CE|IE|EP|CI, 0, 0 ],                                      # 148 - implied      ;
        
        # RTI # Return from Subroutine                                                                                                                         # OPC - ADDRESSING   ; ASSEMBLER
        [DSP|SPE, MI|SPAO|RO|CIDL|DSP|SPE, MI|SPAO|RO|CIDH, MI|COA|J|BR, MI|COA|CE|FEC|BR, CE|II|EP],                                                          # 149 - implied      ;        
        
        # SUB # Subtract Memory from Accumulator with Borrow                                                                                                   # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|RO|SU|EI|ES2|FI, MI|COA|CE|II|EO|AI|EP],                                                                                                # 150 - immediate    ; #oper
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
        [MI|COA|CE|DRF|II|EP|SC|NOP],                                                                                                                          # 161 - implied      ;
        
        # SEI # Set Interrupt Disable Status                                                                                                                   # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|DRF|II|EP|SI|NOP],                                                                                                                          # 162 - implied      ;
        
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
        [MI|COA|CE|FEC|AO|XI, MI|COA|CE|II|EP],                                                                                                                # 181 - implied      ;
        
        # TAY # Transfer Accumulator to Index Y                                                                                                                # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|AO|YI, MI|COA|CE|II|EP],                                                                                                                # 182 - implied      ;
        
        # TSX # Transfer Stack Pointer to Index X                                                                                                              # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|SPDO|XI, MI|COA|CE|II|EP],                                                                                                              # 183 - implied      ;
        
        # TSA # Transfer Index X to Accumulator                                                                                                                # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|XO|AI, MI|COA|CE|II|EP],                                                                                                                # 184 - implied      ;
        
        # TXS # Transfer Index X to Stack Register                                                                                                             # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|XO|SPI, MI|COA|CE|II|EP],                                                                                                               # 185 - implied      ;
        
        # TYA # Transfer Index Y to Accumulator                                                                                                                # OPC - ADDRESSING   ; ASSEMBLER
        [MI|COA|CE|FEC|YO|AI, MI|COA|CE|II|EP],                                                                                                                # 186 - implied      ;
    ]
    
    rom_data = createMicroCode(instructions_data)
    export(rom_data)
    
main()