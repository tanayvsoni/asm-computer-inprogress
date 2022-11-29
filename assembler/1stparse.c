#include "header.h"

static void sort_operand(vars *v, char *operand)
{
    char *op1, *op2;
    int op1_int, op2_int;
    int new_val;

    if (strstr(operand, "+"))
    {
        op1 = strtok(operand, "+");
        op2 = strtok(NULL, "+");
        
        switch (op1[0])
        {
        case '$'|'%':
            op1_int = convert_num(op1);
            break;
        
        default:
            if (isInt(op1)) 
                op1_int = convert_num(op1); 
            else 
                op1_int = find_varVal(v,op1);
            break;
        }
        
        switch (op2[0])
        {
        case '$'|'%':
            op2_int= convert_num(op2);
            break;
        
        default:
            if (isInt(op2)) 
                op2_int = convert_num(op2); 
            else 
                op2_int = find_varVal(v,op2); 
            break;
        }

        new_val = op1_int+op2_int;

        sprintf(operand, "%d", new_val);    
    }

    else if (strstr(operand, "-"))
    {
        op1 = strtok(operand, "-");
        op2 = strtok(NULL, "-");
        
        switch (op1[0])
        {
        case '$'|'%':
            op1_int = convert_num(op1);
            break;
        
        default:
            if (isInt(op1))
                op1_int = convert_num(op1);
            else 
                op1_int = find_varVal(v,op1);
            break;
        }
        
        switch (op2[0])
        {
        case '$'|'%':
            op2_int= convert_num(op2);
            break;
        
        default:
            if (isInt(op2))
                op2_int = convert_num(op2);
            else
                op2_int = find_varVal(v,op2);
            break;
        }

        new_val = op1_int-op2_int;
        sprintf(operand, "%d", new_val);
    }

    else if (!isInt(operand) && isInVars(v, operand)) 
    { 
        new_val = find_varVal(v,operand);
        sprintf(operand, "%d", new_val);
    }

    else if (isInt(operand))
    {
        new_val = convert_num(operand);
        sprintf(operand, "%d", new_val); 
    }
}

void first_parse(instr *code_list, labels *labels_list, vars *vars_list, char **code, int code_size)
{

    for (int i = 0; i < code_size; ++i)
    {
        rm_whitespace(code[i]);
        append(code[i],' ', 3);

        code_list[i].instr = strtok(code[i], " ");
        code_list[i].operand = strtok(NULL, " ");

        if (code_list[i].operand != NULL)
        {
            if (*code_list[i].operand == '#')
            {
                code_list[i].adr_m = "immediate";
                code_list[i].adr_del = 2;
                code_list[i].operand = &code_list[i].operand[1];
            }
            if (strstr(code_list[i].operand, ",") == NULL && strstr(code_list[i].operand, "(") == NULL)
                sort_operand(vars_list, code_list[i].operand);
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