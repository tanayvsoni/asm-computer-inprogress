#include "../header.h"
#include "../dictionary/entry.h"

static int find_labelVal(labels *l, char *label)
{
    int output;

    for (int i = 0; i < MAX_LABELS; ++i)
    {
        if (l[i].name != NULL && (strcmp(l[i].name, label) == 0))
        {
            output = l[i].address;   
        }
    }
    return output;
}

static void sort_labelsoperand(labels *v, char *operand)
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
            {
                op1_int = convert_num(op1);
            }
            else 
            {
                op1_int = find_labelVal(v,op1);
            }
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
                op2_int = find_labelVal(v,op2); 
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
                op1_int = find_labelVal(v,op1);
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
                op2_int = find_labelVal(v,op2);
            break;
        }

        new_val = op1_int-op2_int;
        sprintf(operand, "%d", new_val);
    }

    else if (!isInt(operand) && isInlabels(v, operand)) 
    { 
        new_val = find_labelVal(v,operand);
        sprintf(operand, "%d", new_val);
    }

    else if (isInt(operand))
    {
        new_val = convert_num(operand);
        sprintf(operand, "%d", new_val); 
    }
}

void third_parse(dictionary *d, labels *l, instr *code_list)
{
    for (int i = 0; i < MAX_LINES_NUM; ++i)
    {
        if (code_list[i].instr == NULL) break;

        if (strstr(code_list[i].instr, ".") == NULL && code_list[i].operand != NULL && (code_list[i].adr_m == NULL || !isInt(code_list[i].operand)))
        {
            if (code_list[i].adr_m == NULL)
            {
                code_list[i].adr_m = "abs";
            }
            code_list[i].opcode = find_entry_val(d,code_list[i].instr, code_list[i].adr_m);
            sort_labelsoperand(l, code_list[i].operand);
        }
    }
}