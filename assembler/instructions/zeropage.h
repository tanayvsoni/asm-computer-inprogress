#include "../header.h"
#include "../dictionary/entry.h"

void zeropage(dictionary *d, vars *v, instr *code_list)
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
        
        else if (code_list[i].operand != NULL && code_list[i].adr_m == NULL && 
                strstr(code_list[i].operand, ",X") && strstr(code_list[i].operand, "(") == NULL)
        {
            strtok(code_list[i].operand, ",X");
            sort_operand(v,code_list[i].operand);
            code_list[i].adr_m = "zeropageX";
            code_list[i].adr_del = 2;
            code_list[i].opcode = find_entry_val(d, code_list[i].instr, code_list[i].adr_m); 
        }

        else if (code_list[i].operand != NULL && code_list[i].adr_m == NULL && 
                strstr(code_list[i].operand, ",Y") && strstr(code_list[i].operand, "(") == NULL)
        {
            strtok(code_list[i].operand, ",Y");
            sort_operand(v,code_list[i].operand);
            code_list[i].adr_m = "zeropageY";
            code_list[i].adr_del = 2;
            code_list[i].opcode = find_entry_val(d, code_list[i].instr, code_list[i].adr_m); 
        }
    }
}