#include "../header.h"
#include "../dictionary/entry.h"

void third_parse(dictionary *d, labels *l, instr *code_list)
{
    for (int i = 0; i < MAX_LINES_NUM; ++i)
    {
        if (code_list[i].instr == NULL) break;

        if (strstr(code_list[i].instr, ".") == NULL && code_list[i].adr_m == NULL)
        {
            code_list[i].adr_m = "abs";
            code_list[i].opcode = find_entry_val(d,code_list[i].instr, code_list[i].adr_m);

            for (int j = 0; j < MAX_LABELS; ++j)
            {
                if (l[j].name == NULL) break;

                if (strcmp(code_list[i].operand, l[j].name) == 0)
                {
                    sprintf(code_list[i].operand, "%d", l[j].address);
                }
            }
        }
    }
}