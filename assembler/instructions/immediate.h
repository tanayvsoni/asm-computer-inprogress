#include "../header.h"
#include "../dictionary/entry.h"

void immediate(dictionary *d, instr *code_list)
{
    for (int i = 0; i < MAX_LINES_NUM; ++i)
    {
        if (code_list[i].adr_m != NULL && strcmp(code_list[i].adr_m, "immediate") == 0)
            code_list[i].opcode = find_entry_val(d, code_list[i].instr, code_list[i].adr_m); 
    }
}