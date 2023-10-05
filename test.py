def make_case_insensitive(mnemonic):
    return ''.join(f"[{char.lower()}{char.upper()}]" for char in mnemonic)

def main():
    mnemonic = "NOP|ADC|AND|ASL|BCC|BCS|BEQ|BIT|BMI|BNE|BPL|BRK|BVC|BVS|CLC|CLI|CLV|CMP|CPX|CPY|DEC|DEX|DEY|EOR|INC|INX|INY|JMP|JSR|LDA|LDX|LDY|LSR|ORA|PHA|PHP|PLA|PLP|ROL|ROR|RTI|RTS|SUB|SEC|SEI|STA|STX|STY|TAX|TAY|TSX|TSA|TXS|TYA|HLT|OUT"
    
    print(make_case_insensitive(mnemonic))
    
if __name__ == "__main__":
    main()