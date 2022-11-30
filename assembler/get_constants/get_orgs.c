#include "../header.h"

char **get_orgs(orgs *orgs_list, char **code, int *code_size)
{
    int i, j, amount_orgs;

    char *org_adr, **newcode;
    int int_orgAdr;

    // Initialize orgs list 
    for(int i = 0; i < MAX_ORGS; ++i)
    {
        orgs_list[i].address = 0;
        orgs_list[i].linenum = 0;
    }

    newcode = (char**)(malloc(MAX_LINES_NUM*sizeof(char)));

    for (i = 0, j = 0, amount_orgs = 0; i < *code_size; ++i)
    {
        if (strstr(code[i], ".org"))
        {
            rm_whitespace(code[i]);
            org_adr = strtok(code[i], ".org");

            int_orgAdr = convert_num(org_adr);

            orgs_list[amount_orgs].linenum = j;
            orgs_list[amount_orgs].address = int_orgAdr;
            ++amount_orgs;
        }

        else newcode[j++] = code[i];
    }

    *code_size = j;
    free(code);
    return newcode;
    
}