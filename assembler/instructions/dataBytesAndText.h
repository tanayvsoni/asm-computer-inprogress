#include "../header.h"
#include "../dictionary/entry.h"

void data_bytes(dictionary *d, instr *code_list)
{
    int temp;

    for (int i = 0; i < MAX_LINES_NUM; ++i)
    {
        if (code_list[i].instr == NULL) break;

        if (strcmp(code_list[i].instr, ".DW") == 0)
        {   
            code_list[i].adr_del = 2;
            //code_list[i].adr_del = 2;
            //code_list[i].opcode = d[i].value;
        }

        if (strcmp(code_list[i].instr, ".DB") == 0)
        {
            if (strstr(code_list[i].operand, ",") == NULL)
            {
                code_list[i].adr_del = 1;
            }
            else
            {
                for (int j = 0; j <= amount_commas(code_list[i].operand); ++j)
                {
                    code_list[i].adr_del++;
                }
            }
        }

        if (strcmp(code_list[i].instr, ".TX") == 0)
        {
            code_list[i].operand = &code_list[i].operand[1];
            strtok(code_list[i].operand, "\"");

            code_list[i].adr_del = strlen(code_list[i].operand);
        }   
    }   
}