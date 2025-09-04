import emulator

def main():
    cpu = emulator.CPU16()
    cpu.tick()
    cpu.tick()
    
    print(cpu.clock)

if __name__ == "__main__":
    main()