#include "../header.h"
#include "../dictionary/entry.h"

void zeropage(dictionary *d, instr *code_list)
{
    for (int i = 0; i < MAX_LINES_NUM; ++i)
    {
        if (code_list[i].instr == NULL) break;

        if (code_list[i].operand != NULL && code_list[i].adr_m == NULL && 
            isInt(code_list[i].operand) && convert_num(code_list[i].operand) < 256 && 
            strstr(code_list[i].instr, ".") == NULL)
            {
                code_list[i].adr_m = "zeropage";
                code_list[i].adr_del = 2;
                code_list[i].opcode = find_entry_val(d, code_list[i].instr, code_list[i].adr_m); 
            }
    }
}