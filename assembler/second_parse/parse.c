#include "../header.h"

void convert_operand(vars *v, char *operand)
{
    char *temp = (char*)(malloc(strlen(operand)*sizeof(char)));
    
    if (*operand == '$' || *operand == '%' || isInt(operand))
    {
        sprintf(operand, "%d", convert_num(operand));
    }
    else if (!isInt(operand))
    {
        for (int i = 0; i < MAX_VARS; ++i)
        {
            if (v[i].name != NULL && (strcmp(v[i].name, operand) == 0))
            {   
                sprintf(operand, "%d", v[i].value);
            }
        }
    }
}

bool isInVars(vars *v, char *operand)
{
    for (int i = 0; i < MAX_VARS; ++i)
    {
        if (v[i].name == NULL)
            break;
        else if (strcmp(v[i].name, operand) == 0)
        {
            return true;
        }
    }

    return false;
}

int sort_operand(vars *v, char *operand)
{
    char *op1, *op2;
    int op1_int, op2_int;

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

        return (op1_int+op2_int);    
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

        return (op1_int-op2_int);
    }

    else if (!isInt(operand)) 
    { 
        return find_varVal(v,operand);
    }

    return convert_num(operand); 
}

void parse(instr *code_list, labels *labels_list, vars *vars_list, char **code, int code_size)
{

    char *temp;
    int n;

    for (int i = 0; i < code_size; ++i)
    {
        rm_whitespace(code[i]);
        append(code[i],' ', 3);

        code_list[i].instr = strtok(code[i], " ");
        code_list[i].operand = strtok(NULL, " ");

        /*if (*code_list[i].operand != '#')
        {
            n = sort_operand(vars_list, code_list[i].operand);
            sprintf(temp, "%d", n);
        }*/

            
        for (int j = 0; j < 3; ++j)
        {
            code[i][j] = toupper(code[i][j]);
        }
    }
}