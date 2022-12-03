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
            code_list[i].adr_m = "dataWord";
            //code_list[i].adr_del = 2;
            //code_list[i].opcode = d[i].value;
        }

        if (strcmp(code_list[i].instr, ".DB") == 0)
        {
            code_list[i].adr_m = "dataByte";
        }

        if (strcmp(code_list[i].instr, ".TX") == 0)
        {
            code_list[i].adr_m = "text";
        }   
    }   
}