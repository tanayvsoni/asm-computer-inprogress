#ifndef ENTRY_H
#define ENTRY_H

#include "../header.h"

typedef struct 
{
    char *instr;
    char *adr_mode;
    int value;
    //bool exists;

} dictionary;

static int get_hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % MAX_LINES_NUM;
}

void new_entry(dictionary *d)
{
    int val1, sum, i, j;
    

    for (i = 0; i < AMOUNT_INSTR; ++i)
    {
        sum = 0;

        for (j = 0; j < AMOUNT_ADR_MODE; ++j)
        {
            if (ADR_MODE[i][j] == NULL) break;

            sum = (get_hash(INSTR[i]) + get_hash(ADR_MODE[i][j])) % MAX_LINES_NUM;

            /*if (d[sum].instr != NULL)
            {
                printf("\n--%s--%s--\n", d[sum].instr, d[sum].adr_mode);
            }*/

            d[sum].instr = INSTR[i];
            d[sum].adr_mode = ADR_MODE[i][j];
            d[sum].value = OPCODE[i][j]; 
            //d[sum].exists = true;

        }
    }
}

int find_entry_val(dictionary *d, char *instruction, char *adr_mode)
{

    int sum = (get_hash(instruction) + get_hash(adr_mode)) % MAX_LINES_NUM;

    return d[sum].value;
}

void print_dictionary(dictionary *d)
{
    printf("\n");
    for (int i = 0; i < MAX_LINES_NUM; ++i)
    {
        if (d[i].instr != NULL)
        {
            //printf("%s %s: %d\n", d[i].instr, d[i].adr_mode, (get_hash(d[i].instr) + get_hash(d[i].adr_mode)) % MAX_LINES_NUM);
            printf("%d,", (get_hash(d[i].instr) + get_hash(d[i].adr_mode)) % MAX_LINES_NUM);
        }
    }
}

#endif