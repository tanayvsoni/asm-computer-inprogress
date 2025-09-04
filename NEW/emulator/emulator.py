from isa import Opcode

class CPU16:

    def __init__(self):
        self.clock = 0
        self.power = True
        self.registers = [0] * 8
        self.memory = [0] * (2**21)   # 2 MB memory
        self.pc = 0                   # 21-bit PC (just int in Python)

        # Pipeline registers (with valid/ready flags)
        self.IF_ID  = {"valid": False, "instr": None}
        self.ID_EX  = {"valid": False, "decoded": None}
        self.EX_MEM = {"valid": False, "alu_result": None, "dest": None}
        self.MEM_WB = {"valid": False, "value": None, "dest": None}

    # ------------------------
    # Pipeline stages
    # ------------------------
    def fetch(self):
        instr = self.memory[self.pc]
        self.pc = (self.pc + 1) & ((1 << 21) - 1)   # wrap 21-bit PC
        print(f"FETCH: instr {hex(instr)} from PC={hex(self.pc)}")
        return instr

    def decode(self, instr):
        opcode  = (instr & 0xF000) >> 12
        reg     = (instr & 0x0F00) >> 8
        operand = instr & 0x00FF
        print(f"DECODE: opcode={opcode}, reg={reg}, operand={operand}")
        return (opcode, reg, operand)

    def execute(self, decoded):
        opcode, reg, operand = decoded
        print(f"EXECUTE: opcode={opcode}, reg={reg}, operand={operand}")

        if opcode == opcode.LDI:  # LDI reg, imm
            result = operand
            dest = reg
            return result, dest

        elif opcode == opcode.ADDI:  # ADDI reg, imm
            result = self.registers[reg] + operand
            dest = reg
            return result, dest

        else:
            return None, None

    def mem_stage(self, alu_result, dest):
        # for load/store later
        print(f"MEM: alu_result={alu_result}, dest={dest}")
        return alu_result, dest

    def writeback(self, value, dest):
        if dest is not None:
            self.registers[dest] = value
            print(f"WB: R{dest} = {value}")

    # ------------------------
    # Pipeline tick
    # ------------------------
    def tick(self):
        self.clock += 1
        print(f"\n[Clock {self.clock}]")

        # WB stage
        if self.MEM_WB["valid"]:
            value, dest = self.MEM_WB["value"], self.MEM_WB["dest"]
            if dest is not None:
                self.registers[dest] = value
                print(f"WB: R{dest} = {value}")
            self.MEM_WB["valid"] = False

        # MEM stage
        if self.EX_MEM["valid"]:
            alu_result, dest = self.EX_MEM["alu_result"], self.EX_MEM["dest"]
            value, reg_dest = self.mem_stage(alu_result, dest)
            self.MEM_WB.update({"valid": True, "value": value, "dest": reg_dest})
            self.EX_MEM["valid"] = False

        # EX stage
        if self.ID_EX["valid"]:
            alu_result, dest = self.execute(self.ID_EX["decoded"])
            self.EX_MEM.update({"valid": True, "alu_result": alu_result, "dest": dest})
            self.ID_EX["valid"] = False

        # ID stage
        if self.IF_ID["valid"]:
            decoded = self.decode(self.IF_ID["instr"])
            self.ID_EX.update({"valid": True, "decoded": decoded})
            self.IF_ID["valid"] = False

        # IF stage
        instr = self.fetch()
        self.IF_ID.update({"valid": True, "instr": instr})

    # ------------------------
    # Run loop
    # ------------------------
    def run(self):
        while self.power:
            self.tick()
