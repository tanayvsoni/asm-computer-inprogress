#include "header.h"

bool overwrite(vars *v, char *var_name, int val)
{   
    int i;

    for (i = 0; i < MAX_VARS; ++i)
    {
        if (v[i].name != NULL && (strcmp(v[i].name, var_name) == 0))
        {
            v[i].name = var_name;
            v[i].value = val;
            return true;
        }
    }

}

bool isInt(char *var)
{
    bool is_integer = true;

    for (int i = 0; i < strlen(var); ++i)
    {
        if (isdigit(var[i]) == 0)
        {
            is_integer = false;
            break;
        }
    }

    return is_integer;
}

int find_varVal(vars *v, char *var_name)
{
    int output;

    for (int i = 0; i < MAX_VARS; ++i)
    {
        if (v[i].name != NULL && (strcmp(v[i].name, var_name) == 0))
        {
            output = v[i].value;   
        }
    }
    return output;
}

int deal_oper(vars *v, char *val)
{
    char *op1, *op2;
    int op1_int, op2_int;

    if (strstr(val, "+"))
    {
        op1 = strtok(val, "+");
        op2 = strtok(NULL, "+");
        
        switch (op1[0])
        {
        case '$'||'%':
            op1_int = convert_num(op1);
            break;
        
        default:
            if (isInt(op1)) { op1_int = convert_num(op1); }
            else { op1_int = find_varVal(v,op1); }
            break;
        }
        
        switch (op2[0])
        {
        case '$'||'%':
            op2_int= convert_num(op2);
            break;
        
        default:
            if (isInt(op2)) { op2_int = convert_num(op2); }
            else { op2_int = find_varVal(v,op2); }
            break;
        }

        return (op1_int+op2_int);    
    }

    else if (strstr(val, "-"))
    {
        op1 = strtok(val, "-");
        op2 = strtok(NULL, "-");
        
        switch (op1[0])
        {
        case '$'||'%':
            op1_int = convert_num(op1);
            break;
        
        default:
            if (isInt(op1)) { op1_int = convert_num(op1); }
            else { op1_int = find_varVal(v,op1); }
            break;
        }
        
        switch (op2[0])
        {
        case '$'||'%':
            op2_int= convert_num(op2);
            break;
        
        default:
            if (isInt(op2)) { op2_int = convert_num(op2); }
            else { op2_int = find_varVal(v,op2); }
            break;
        }

        return (op1_int-op2_int);
    }

    else if (!isInt(val)) 
    { 
        return find_varVal(v,val);
    }

    return convert_num(val);    
}

char **get_vars(vars *v, char **code, int *code_size)
{
    int i, amount_vars = 0;
    int j = 0;

    bool existing;
    char *var_name, *temp, **newcode;
    int val;

    newcode = (char**)(malloc(MAX_LINES_NUM*sizeof(char)));

    for (i = 0; i < *code_size; ++i, existing = false)
    {
        if (strstr(code[i], "="))
        {
            rm_whitespace(code[i]);
            var_name = strtok(code[i], "=");
            temp = strtok(NULL, "=");

            val = deal_oper(v,temp);

            existing = overwrite(v, var_name, val);

            if (!existing)
            {
                v[amount_vars].name = var_name;
                v[amount_vars].value = val;
                ++amount_vars;
            }
        }
        else
        {
            newcode[j] = code[i];
            ++j;
        }
    }

    *code_size = j;

    return newcode;
}