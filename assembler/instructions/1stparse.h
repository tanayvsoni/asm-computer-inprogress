#include "../header.h"


void first_parse(instr *code_list, labels *labels_list, vars *vars_list, char **code, int size)
{
    int j = 0;
    for (int i = 0; i < MAX_LINES_NUM; ++i)
    {
        code_list[i].instr = NULL;
        code_list[i].adr_m = NULL;
        code_list[i].adr_del = 0;
        code_list[i].opcode = 0;
        code_list[i].operand = NULL;
        code_list[i].adr = 0;
    }

    for (int i = 0; i < size; ++i)
    {   
        rm_whitespace(code[i]);
        append(code[i],'~', 3);
        //printf("%s\n", code[i]);

        code_list[i].instr = strtok(code[i], "~");
        code_list[i].operand = strtok(NULL, "~");
        //printf("%s: %s\n", code_list[i].instr, code_list[i].operand);

        if (code_list[i].operand != NULL)
        {
            if (*code_list[i].operand == '#')
            {
                code_list[i].adr_m = "immediate";
                code_list[i].adr_del = 2;
                code_list[i].operand = &code_list[i].operand[1];
            }
            if (strstr(code_list[i].operand, ",") == NULL && strstr(code_list[i].operand, "(") == NULL)
                sort_operand(labels_list, vars_list, code_list[i].operand);
        }
        else
        {
            code_list[i].adr_m = "implied";
            code_list[i].adr_del = 1;
        }

        for (int j = 0; j < 3; ++j)
        {
            code[i][j] = toupper(code[i][j]);
        }
    }
}