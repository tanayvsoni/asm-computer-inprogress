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

char *implied_instr[] = {"NOP", "ASL", "BRK", "CLC", "CLI", "CLV", "DEX", "DEY",
                         "INX", "INY", "LSR", "PHA", "PHP", "PLA", "PLP", "ROL",
                         "ROR", "RTI", "RTS", "SEC", "SEI", "TAX", "TAY", "TSX", 
                         "TSA", "TXS", "TYA", "HLT", "OUT"};

char *immediate_instr[] = {"ADC", "AND", "CMP", "CPX", "CPY", "EOR", "LDA", "LDX",
                           "LDY", "ORA", "SUB"};              

#endif