#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>


#if defined(__WIN32)
    #define PATH "\\programs\\"
#elif defined(__APPLE__)
    #define PATH "/assembler/programs/"
    #define PATH_MAX 100
#endif

#define NAMESIZE         60
#define MAX_CHARS        80
#define MAX_LINES_NUM    60000

#define MAX_ORGS        1000
#define MAX_VARS        1000
#define MAX_LABELS      100

#define AMOUNT_INSTR    56
#define AMOUNT_ADR_MODE 189


typedef struct
{
    char *name;
    int linenum;
    int address;
} labels;

typedef struct 
{
    char *name;
    int value;
} vars;

typedef struct 
{
    int linenum;
    int address;
} orgs;

typedef struct
{
    char *instr;
    char *adr_m;
    char *operand;
    int opcode;
    int adr_del;

} instr;

bool isInVars(vars *v, char *operand)
{
    for (int i = 0; i < MAX_VARS; ++i)
    {
        if (v[i].name == NULL)
            break;
        else if (strcmp(v[i].name, operand) == 0)
        {
            return true;
        }
    }

    return false;
}

int find_varVal(vars *v, char *var_name)
{
    int output;

    for (int i = 0; i < MAX_VARS; ++i)
    {
        if (v[i].name != NULL && (strcmp(v[i].name, var_name) == 0))
        {
            output = v[i].value;   
        }
    }
    return output;
}

bool isInt(char *var)
{
    int start = 0;

    if (*var == '$' || *var == '%')
        return true;

    for (int i = 0; i < strlen(var); ++i)
    {   
        if (isdigit(var[i]) == 0)
        {
            return false;
        }
    }

    return true;
}

void rm_whitespace(char *word)
{
    char *d = word;

    do {
        while (*d == ' ' || *d =='\n' || *d == '\t') {
            ++d;
        }
    } while (*word++ = *d++);

}

int convert_num(char *num)
{
    char *token;
    int int_num;

    switch (*num)
    {
    case '$':
        token = strtok(num,"$");
        int_num = (int)strtol(token, NULL, 16);
        break;
    
    case '%':
        token = strtok(num,"%%");
        int_num = (int)strtol(token, NULL, 2);
        break;

    default:
        int_num = (int)strtol(num, NULL, 10); 
        break;
    }

    return int_num;
}

void print_arr(char **file, int *size)
{
    for (int i = 0; i < *size; ++i) {
        printf("%s", file[i]);
    }

    printf("\n");
}

void sort_operand(vars *v, char *operand)
{
    char *op1, *op2;
    int op1_int, op2_int;
    int new_val;

    if (strstr(operand, "+"))
    {
        op1 = strtok(operand, "+");
        op2 = strtok(NULL, "+");
        
        switch (op1[0])
        {
        case '$'|'%':
            op1_int = convert_num(op1);
            break;
        
        default:
            if (isInt(op1)) 
                op1_int = convert_num(op1); 
            else 
                op1_int = find_varVal(v,op1);
            break;
        }
        
        switch (op2[0])
        {
        case '$'|'%':
            op2_int= convert_num(op2);
            break;
        
        default:
            if (isInt(op2)) 
                op2_int = convert_num(op2); 
            else 
                op2_int = find_varVal(v,op2); 
            break;
        }

        new_val = op1_int+op2_int;

        sprintf(operand, "%d", new_val);    
    }

    else if (strstr(operand, "-"))
    {
        op1 = strtok(operand, "-");
        op2 = strtok(NULL, "-");
        
        switch (op1[0])
        {
        case '$'|'%':
            op1_int = convert_num(op1);
            break;
        
        default:
            if (isInt(op1))
                op1_int = convert_num(op1);
            else 
                op1_int = find_varVal(v,op1);
            break;
        }
        
        switch (op2[0])
        {
        case '$'|'%':
            op2_int= convert_num(op2);
            break;
        
        default:
            if (isInt(op2))
                op2_int = convert_num(op2);
            else
                op2_int = find_varVal(v,op2);
            break;
        }

        new_val = op1_int-op2_int;
        sprintf(operand, "%d", new_val);
    }

    else if (!isInt(operand) && isInVars(v, operand)) 
    { 
        new_val = find_varVal(v,operand);
        sprintf(operand, "%d", new_val);
    }

    else if (isInt(operand))
    {
        new_val = convert_num(operand);
        sprintf(operand, "%d", new_val); 
    }
}

void append(char *str, char c, int n) 
{
    int size = strlen(str)+1;
    char *new_str = (char*)(malloc((size+1)*sizeof(char)));
    int i,j;

    for (i = 0, j = 0; i < size; ++i, ++j)
    {
        if (i == n)
        {
            new_str[j++] = c;
        }

        new_str[j] = str[i];
    } 

    memcpy(str, new_str,j);

    free(new_str);
}

// Instructions, Addressing Modes, and OPCODEs for each one
char *INSTR[] = {"NOP", "ADC", "AND", "ASL", "BCC", "BCS", "BEQ", "BIT", "BMI", "BNE", "BPL", "BRK", "BVC", "BVS", "CLC", "CLI", "CLV",
                      "CMP", "CPX", "CPY", "DEC", "DEX", "DEY", "EOR", "INC", "INX", "INY", "JMP", "JSR", "LDA", "LDX", "LDY", "LSR", "ORA",
                      "PHA", "PHP", "PLA", "PLP", "ROL", "ROR", "RTI", "RTS", "SBC", "SEC", "SEI", "STA", "STX", "STY", "TAX", "TAY", "TSX",
                      "TSA", "TXS", "TYA", "HLT", "OUT"
                    };

char *ADR_MODE[189][12] = {
        /*NOP*/       {"implied"}, 
        /*ADC*/       {"immediate", "zeropage", "zeropageX", "zeropageY", "absolute", "absoluteX", "absoluteY", "BindirectXB", "BindirectYB", "BindirectBX" , "BindirectBY"},
        /*AND*/       {"immediate", "zeropage", "zeropageX", "zeropageY", "absolute", "absoluteX", "absoluteY", "BindirectXB", "BindirectYB", "BindirectBX" , "BindirectBY"},
        /*ASL*/       {"implied", "zeropage", "zeropageX", "zeropageY", "absolute", "absoluteX", "absoluteY"},
        /*BCC*/       {"relative"},
        /*BCS*/       {"relative"},
        /*BEQ*/       {"relative"},
        /*BIT*/       {"zeropage", "absolute"},
        /*BMI*/       {"relative"},
        /*BNE*/       {"relative"},
        /*BPL*/       {"relative"},
        /*BRK*/       {"implied"},
        /*BVC*/       {"relative"},
        /*BVS*/       {"relative"},
        /*CLC*/       {"implied"},
        /*CLI*/       {"implied"},
        /*CLV*/       {"implied"},
        /*CMP*/       {"immediate", "zeropage", "zeropageX", "zeropageY", "absolute", "absoluteX", "absoluteY", "BindirectXB", "BindirectYB", "BindirectBX" , "BindirectBY"},
        /*CPX*/       {"immediate", "zeropage", "absolute"},
        /*CPY*/       {"immediate", "zeropage", "absolute"},
        /*DEC*/       {"zeropage", "zeropageX", "zeropageY", "absolute", "absoluteX", "absoluteY"},
        /*DEX*/       {"implied"},
        /*DEY*/       {"implied"},
        /*EOR*/       {"immediate", "zeropage", "zeropageX", "zeropageY", "absolute", "absoluteX", "absoluteY", "BindirectXB", "BindirectYB", "BindirectBX" , "BindirectBY"},
        /*INC*/       {"zeropage", "zeropageX", "zeropageY", "absolute", "absoluteX", "absoluteY"},
        /*INX*/       {"implied"},
        /*INY*/       {"implied"},
        /*JMP*/       {"absolute", "BindirectB"},
        /*JSR*/       {"absolute"},
        /*LDA*/       {"immediate", "zeropage", "zeropageX", "zeropageY", "absolute", "absoluteX", "absoluteY", "BindirectXB", "BindirectYB", "BindirectBX" , "BindirectBY"},
        /*LDX*/       {"immediate", "zeropage", "zeropageY", "absolute", "absoluteY"},
        /*LDY*/       {"immediate", "zeropage", "zeropageX", "absolute", "absoluteX"},
        /*LSR*/       {"implied", "zeropage", "zeropageX", "zeropageY", "absolute", "absoluteX", "absoluteY"},
        /*ORA*/       {"immediate", "zeropage", "zeropageX", "zeropageY", "absolute", "absoluteX", "absoluteY", "BindirectXB", "BindirectYB", "BindirectBX" , "BindirectBY"},
        /*PHA*/       {"implied"},
        /*PHP*/       {"implied"},
        /*PLA*/       {"implied"},
        /*PLP*/       {"implied"},
        /*ROL*/       {"implied", "zeropage", "zeropageX", "zeropageY", "absolute", "absoluteX", "absoluteY"},
        /*ROR*/       {"implied", "zeropage", "zeropageX", "zeropageY", "absolute", "absoluteX", "absoluteY"},
        /*RTI*/       {"implied"},
        /*RTS*/       {"implied"},
        /*SUB*/       {"immediate", "zeropage", "zeropageX", "zeropageY", "absolute", "absoluteX", "absoluteY", "BindirectXB", "BindirectYB", "BindirectBX" , "BindirectBY"},
        /*SEC*/       {"implied"},
        /*SEI*/       {"implied"},
        /*STA*/       {"zeropage", "zeropageX", "zeropageY", "absolute", "absoluteX", "absoluteY", "BindirectXB", "BindirectYB", "BindirectBX" , "BindirectBY"},
        /*STX*/       {"zeropage", "zeropageY", "absolute", "absoluteY"},
        /*STY*/       {"zeropage", "zeropageX", "absolute", "absoluteX"},
        /*TAX*/       {"implied"},
        /*TAY*/       {"implied"},
        /*TSX*/       {"implied"},
        /*TSA*/       {"implied"},
        /*TXS*/       {"implied"},
        /*TYA*/       {"implied"},
        /*HLT*/       {"implied"},
        /*OUT*/       {"implied"}
        };

int OPCODE[189][12] = {
        /*NOP*/     {0},
        /*ADC*/     {1,2,3,4,5,6,7,8,9,10,11},
        /*AND*/     {12,13,14,15,16,17,18,19,20,21,22},
        /*ASL*/     {23,24,25,26,27,28,29},
        /*BCC*/     {30},
        /*BCS*/     {31},
        /*BEQ*/     {32},
        /*BIT*/     {33,34},
        /*BMI*/     {35},
        /*BNE*/     {36},
        /*BPL*/     {37},
        /*BRK*/     {38},
        /*BVC*/     {39},
        /*BVS*/     {40},
        /*CLC*/     {41},
        /*CLI*/     {42},
        /*CLV*/     {43},
        /*CMP*/     {44,45,46,47,48,49,50,51,52,53,54},
        /*CPX*/     {55,56,57},
        /*CPY*/     {58,59,60},
        /*DEC*/     {61,62,63,64,65,66},
        /*DEX*/     {67},
        /*DEY*/     {68},
        /*EOR*/     {69,70,71,72,73,74,75,76,77,78,79},
        /*INC*/     {80,81,82,83,84,85},
        /*INX*/     {86},
        /*INY*/     {87},
        /*JMP*/     {88,89},
        /*JSR*/     {90},
        /*LDA*/     {91,92,93,94,95,96,97,98,99,100,101},
        /*LDX*/     {102,103,104,105,106},
        /*LDY*/     {107,108,109,110,111},
        /*LSR*/     {112,113,114,115,116,117,118},
        /*ORA*/     {119,120,121,122,123,124,125,126,127,128,129},
        /*PHA*/     {130},
        /*PHP*/     {131},
        /*PLA*/     {132},
        /*PLP*/     {133},
        /*ROL*/     {134,135,136,137,138,139,140},
        /*ROR*/     {141,142,143,144,145,146,147},
        /*RTI*/     {148},
        /*RTS*/     {149},
        /*SUB*/     {150,151,152,153,154,155,156,157,158,159,160},
        /*SEC*/     {161},
        /*SEI*/     {162},
        /*STA*/     {163,164,165,166,167,168,169,170,171,172},
        /*STX*/     {173,174,175,176},
        /*STY*/     {177,178,179,180},
        /*TAX*/     {181},
        /*TAY*/     {182},
        /*TSX*/     {183},
        /*TSA*/     {184},
        /*TXS*/     {185},
        /*TYA*/     {186},
        /*HLT*/     {187},
        /*OUT*/     {188}
        };



#endif