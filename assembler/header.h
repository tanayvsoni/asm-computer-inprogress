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

void rm_whitespace(char *word)
{
    char *d = word;

    do {
        while (*d == ' ' || *d == '\n' || *d == '\t') {
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

char *instr[] = {"NOP", "ADC", "AND", "ASL", "BCC", "BCS", "BCS", "BEQ", "BIT",
                 "BMI", "BNE", "BPL", "BRK", "BVS", "CLC", "CLI", "CLC", "CMP",
                 "CMP", "CPX", "CPX", "CPY", "DEC", "DEX", "DEY", "EOR", "INC",
                 "INX", "INY", "JMP", "JSR", "LDA", "LDX", "LDY", "LSR", "ORA", 
                 "PHA", "PHP", "PLA", "ROL", "ROR", "RTI", "RTS", "SUB", "SEC",
                 "SEI", "STA", "STX", "STY", "TAX", "TAY", "TSX", "TSA", "TXS",
                 "TYA", "HLT", "OUT"};

#endif