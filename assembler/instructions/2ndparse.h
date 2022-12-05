#include "../header.h"
#include "../dictionary/entry.h"

void second_parse(dictionary *d, labels *l, vars *v, instr *code_list)
{
    for (int i = 0; i < MAX_LINES_NUM; ++i)
    {
        if (code_list[i].instr == NULL) break;

        if (code_list[i].adr_m != NULL && (strcmp(code_list[i].adr_m, "implied") == 0 || strcmp(code_list[i].adr_m, "immediate") == 0))
            code_list[i].opcode = find_entry_val(d, code_list[i].instr, code_list[i].adr_m); 

        else if (code_list[i].operand != NULL && code_list[i].adr_m == NULL && 
            isInt(code_list[i].operand) && strstr(code_list[i].instr, ".") == NULL)
            {
                if (convert_num(code_list[i].operand) < 256)
                {
                    code_list[i].adr_m = "zeropage";
                    code_list[i].adr_del = 2;
                }
                else
                {
                    code_list[i].adr_m = "abs";
                    code_list[i].adr_del = 3;
                }
                
                code_list[i].opcode = find_entry_val(d, code_list[i].instr, code_list[i].adr_m); 
            }
        
        else if (code_list[i].operand != NULL && code_list[i].adr_m == NULL && 
                strstr(code_list[i].operand, ",X") && strstr(code_list[i].operand, "(") == NULL)
        {
            strtok(code_list[i].operand, ",X");
            sort_operand(l, v,code_list[i].operand);

            if (isInt(code_list[i].operand) && convert_num(code_list[i].operand) < 256)
            {
                code_list[i].adr_m = "zeropageX";
                code_list[i].adr_del = 2;
            }
            else
            {
                code_list[i].adr_m = "absX";
                code_list[i].adr_del = 3;
            }
            code_list[i].opcode = find_entry_val(d, code_list[i].instr, code_list[i].adr_m); 
        }

        else if (code_list[i].operand != NULL && code_list[i].adr_m == NULL && 
                strstr(code_list[i].operand, ",Y") && strstr(code_list[i].operand, "(") == NULL)
        {
            strtok(code_list[i].operand, ",Y");
            sort_operand(l, v,code_list[i].operand);

            if (convert_num(code_list[i].operand) < 256)
            {
                code_list[i].adr_m = "zeropageY";
                code_list[i].adr_del = 2;
            }
            else
            {
                code_list[i].adr_m = "absY";
                code_list[i].adr_del = 3;
            }

            code_list[i].opcode = find_entry_val(d, code_list[i].instr, code_list[i].adr_m); 
        }

        else if (code_list[i].operand != NULL && code_list[i].adr_m == NULL && strstr(code_list[i].operand, ",X)"))
        {
            code_list[i].operand = &code_list[i].operand[1];
            strtok(code_list[i].operand, ",X)");
            sort_operand(l, v,code_list[i].operand);

            code_list[i].adr_m = "BindXB";
            code_list[i].adr_del = 3;

            code_list[i].opcode = find_entry_val(d, code_list[i].instr, code_list[i].adr_m); 
        }

        else if (code_list[i].operand != NULL && code_list[i].adr_m == NULL && strstr(code_list[i].operand, ",Y)"))
        {
            code_list[i].operand = &code_list[i].operand[1];
            strtok(code_list[i].operand, ",Y)");
            sort_operand(l, v,code_list[i].operand);

            code_list[i].adr_m = "BindYB";
            code_list[i].adr_del = 3;
            
            code_list[i].opcode = find_entry_val(d, code_list[i].instr, code_list[i].adr_m); 
        }

        else if (code_list[i].operand != NULL && code_list[i].adr_m == NULL && strstr(code_list[i].operand, "),X"))
        {
            code_list[i].operand = &code_list[i].operand[1];
            strtok(code_list[i].operand, "),X");
            sort_operand(l, v,code_list[i].operand);

            code_list[i].adr_m = "BindBX";
            code_list[i].adr_del = 3;
            
            code_list[i].opcode = find_entry_val(d, code_list[i].instr, code_list[i].adr_m); 
        }

        else if (code_list[i].operand != NULL && code_list[i].adr_m == NULL && strstr(code_list[i].operand, "),Y"))
        {
            code_list[i].operand = &code_list[i].operand[1];
            strtok(code_list[i].operand, "),Y");
            sort_operand(l, v,code_list[i].operand);

            code_list[i].adr_m = "BindBY";
            code_list[i].adr_del = 3;
            
            code_list[i].opcode = find_entry_val(d, code_list[i].instr, code_list[i].adr_m); 
        }

        else if (code_list[i].operand != NULL && code_list[i].adr_m == NULL && strstr(code_list[i].operand, ")"))
        {
            code_list[i].operand = &code_list[i].operand[1];
            strtok(code_list[i].operand, ")");
            sort_operand(l, v,code_list[i].operand);

            code_list[i].adr_m = "bBindBb";
            code_list[i].adr_del = 3;

        }

        else if (code_list[i].operand != NULL && code_list[i].adr_m == NULL && strstr(code_list[i].instr, ".") == NULL && !isInt(code_list[i].operand))
        {
            code_list[i].adr_del = 3;
        }
    }
}