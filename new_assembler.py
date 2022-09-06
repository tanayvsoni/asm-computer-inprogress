import pathlib

opcodes = {'NOP':'0','LDA':'1', 'ADD':'2', 'SUB':'3', 'STA':'4', 'LDI':'5', 'JMP':'6', 'JC':'7', 
           'JZ':'8', 'JNC':'9', 'JNZ':'10', 'INC':'11', 'DEC':'12', 'DSP':'13', 'OUT':'14','HLT':'15' }

LINEINFO_NONE, LINEINFO_ORG, LINEINFO_END	= 0x00000, 0x20000, 0x40000
FILENAME = input('Please enter sourcefile name: ')

def read_sourcefile(lines):
    """ 
    Read <sourcefile> and remove all whitespace in the front and back of every line
    """
    
    sourcefile = pathlib.Path(__file__).parent.resolve().joinpath('programs').joinpath(FILENAME)
    
    with open(sourcefile, 'r') as file: 
        for line in file:
            if line.strip():
                lines.append(line.strip())  # remove whitespace infront and back of line 

    return lines

def str_ASCII(lines):
    """
    Converts strings('...') to binary (ASCII Values) by line
    """

    for i in range(len(lines)):

        while(lines[i].find('\'') != -1):  
            # Gets locations of first ' and second '
            k = lines[i].find('\'')
            l = lines[i].find('\'',k+1)
            
            
            # Replaces each letter within '...' one by one with ASCII value
            if k != -1 and l != -1:
                replaced = ''
        
                for c in lines[i][k+1:l]: 
                    replaced += str(ord(c)) + ' '
                    
                lines[i] = lines[i][0:k] + replaced + lines[i][l+1:]
            else: break

        if(lines[i].find(';') != -1): 
            lines[i] = lines[i][0:lines[i].find(';')]   # deletes anything written after ';' ie. any comments
        
        lines[i] = lines[i].replace(',', ' ')           # replaces commas with spaces

def remove_preprocessor(lines, lineinfo, labels):    
    """ 
    Stores and deletes the preprocesser statements from line and remove blank lines
    """
    new_lines = []      # creates new list to store all lines without blank spaces
    new_lineNum = 0     # keep track of the new line number

    for i in range(len(lines)):
            
        lineinfo.append(LINEINFO_NONE)                  # generate a separate lineinfo
        k = lines[i].find('.org')
        
        if lines[i].find('.end') != -1:
            lineinfo[new_lineNum-1] |= LINEINFO_END
        
        elif (k != -1):
            s = lines[i][k:].split();                   # split from .org onwards
            lineinfo[new_lineNum] |= LINEINFO_ORG + int(s[1], 0)  # use element after .org as origin address
            
        elif lines[i].find(':') != -1:
            labels[lines[i][:lines[i].find(':')]] = new_lineNum     # store label and it's line number in dictionary
            
            if lines[i][lines[i].find(':') + 1:] != '':
                new_lines.append(lines[i][lines[i].find(':') + 1:])  # cut out the label
                new_lineNum += 1
        
        elif lines[i] != '':
            new_lines.append(lines[i])
            new_lineNum += 1
    
    # remove blank spaces within lines
    for i in range(len(new_lines)):
        new_lines[i] = new_lines[i].split()    
    
    return new_lines

def convert_decimal(lines,i,j):
    if lines[i][j].find('0x') == 0:
        val = int(lines[i][j], 16)
        lines[i][j] = str(val)
        
    elif lines[i][j].find('0b') == 0:
        val = int(lines[i][j], 2)
        lines[i][j] = str(val)
   
def decode_opcodes(lines):
    """
    Decodes program's opcodes and sorts numbers into LSB and MSB
    """
    
    for i in range(len(lines)):
        for j in range(len(lines[i])-1,-1,-1):                            # iterate from back to front while inserting stuff
            try: 
                lines[i][j] = opcodes[lines[i][j].upper()]

            except:
                convert_decimal(lines,i,j)                                # convert all types of nums into decimal
                
                if lines[i][j].isnumeric() and int(lines[i][j]) > 0xff:    # sorts them into LSB and MSB
                    val = int(lines[i][j],10)
                    lines[i][j] = str(val & 0xff)
                    lines[i].insert(j+1, str((val >> 8) & 0xff))

def setAddresses(lines,lineinfo,labels,lineadr):
    adr = 0                                             # PASS 2: default start address
    for i in range(len(lines)):

        for j in range(len(lines[i])-1, -1, -1):
            e = lines[i][j]
            try:
                labels[e]; lines[i].insert(j+1, '')
            except: pass
        
        if lineinfo[i] & LINEINFO_ORG:
            adr = lineinfo[i] & 0xffff                 # react to .org by resetting the address
        if lineinfo[i] & LINEINFO_END:                 # react to .end by resetting the address
            adr = lineinfo[i] & 0xffff
            
        lineadr.append(adr)                           
        
        # advance address by number of (byte) elements
        adr += len(lines[i])

    for l in labels:
        # update label dictionary from 'line number' to 'address'
        labels[l] = lineadr[labels[l]]

    # PASS 3: replace 'reference + placeholder' with 'MSB LSB'
    for i in range(len(lines)):
        for j in range(len(lines[i])):
            e = lines[i][j]
            off = 0
            try:
                adr = labels[e] + off
                lines[i][j] = str(adr & 0xff)
                lines[i][j+1] = str((adr >> 8) & 0xff)
            except: pass
            
            try:
                # check if ALL elements are numeric
                int(lines[i][j], 0)
            except:
                print('ERROR in line ' + str(i+1) +
                    ': Undefined expression \'' + lines[i][j] + '\'')
                exit(1)

def print_program(lines,lineadr):
    """
    Print out assembled program
    """
       
    output = pathlib.Path(__file__).parent.resolve().joinpath('assembler output').joinpath(FILENAME[:-2] + '_output.txt')
    
    with open(output, 'w') as outfile:
        for i in range(len(lines)):
            s = ('%02.1x' % lineadr[i]) + ': '
            for e in lines[i]: 
                s += ('%02.2x' % (int(e,0) & 0xff)) + ' '
            print(s)
            outfile.write(s + '\n')
            
def main():
    lines, lineadr, lineinfo, labels = [],[],[],{}
    
    lines = read_sourcefile(lines)
    
    # PASS 1
    str_ASCII(lines)
    lines = remove_preprocessor(lines, lineinfo, labels)
    
    decode_opcodes(lines)
    
    # PASS 2 & 3
    setAddresses(lines,lineinfo,labels,lineadr)
    print_program(lines,lineadr)
    
main()
     