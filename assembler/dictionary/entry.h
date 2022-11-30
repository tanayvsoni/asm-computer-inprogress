#ifndef ENTRY_H
#define ENTRY_H

#include "../header.h"

typedef struct 
{
    char *instr;
    char *adr_mode;
    int value;

} dictionary;

static int value_string(char *str)
{
    int sum = 0;
    for (int i = 0; i < strlen(str); ++i)
    {
        sum += str[i];
    }

    return sum;
}

void new_entry(dictionary *d, char *instruction, char **adr_mode, int value[])
{
    int val1 = value_string(instruction);

    for (int i = 0; i < sizeof(adr_mode)/sizeof(adr_mode[0]); ++i)
    {
        int sum = val1;
        sum += value_string(adr_mode[i]);
        d[sum].instr = instruction;
        d[sum].adr_mode = adr_mode[i];
        d[sum].value = value[i];   
    }
}



#endif