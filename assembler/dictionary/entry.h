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

void new_entry(dictionary *d)
{
    int val1, sum, i, j;

    for (i = 0; i < AMOUNT_INSTR; ++i)
    {
        val1 = value_string(INSTR[i]);
        sum = 0;

        for (j = 0; j < AMOUNT_ADR_MODE; ++j)
        {
            if (ADR_MODE[i][j] == NULL) break;

            sum = val1 + value_string(ADR_MODE[i][j]);

            d[sum].instr = INSTR[i];
            d[sum].adr_mode = ADR_MODE[i][j];
            d[sum].value = OPCODE[i][j]; 

        }
    }
}

int find_entry_val(dictionary *d, char *instruction, char *adr_mode)
{
    int sum = value_string(instruction) + value_string(adr_mode);
    return d[sum].value;
}

#endif