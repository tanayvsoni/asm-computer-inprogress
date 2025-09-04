from enum import IntEnum

class Opcode(IntEnum):
    NOP   = 0x0   # No operation
    LDI   = 0x1   # Load immediate into register
    ADDI  = 0x2   # Add immediate to register
    LDR   = 0x3   # Load from memory into register
    STR   = 0x4   # Store register into memory
    ADD   = 0x5   # Add reg + reg
    JMP   = 0x7   # Jump to address
    JZ    = 0x8   # Jump if zero flag set
    JNZ   = 0x9   # Jump if zero flag clear
    PUSH  = 0xA   # Push register to stack
    POP   = 0xB   # Pop value from stack into register
    CALL  = 0xC   # Call subroutine
    RET   = 0xD   # Return from subroutine
    OUT   = 0xE   # Output register (I/O or VRAM)
    HLT   = 0xF   # Halt