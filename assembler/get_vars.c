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

void check_oper(char *val)
{

}

void get_vars(vars *v, char **code, int *code_size)
{
    int i,j,amount_vars = 0;
    bool existing;
    char *var_name;
    char *temp;
    int val;


    for (i = 0; i < *code_size; ++i, existing = false)
    {
        if (strstr(code[i], "="))
        {
            rm_whitespace(code[i]);
            var_name = strtok(code[i], "=");
            temp = strtok(NULL, "=");

            
            
            val = convert_num(temp);

            existing = overwrite(v, var_name, val);

            if (!existing)
            {
                v[amount_vars].name = var_name;
                v[amount_vars].value = val;
                ++amount_vars;
            }
        }
    }
}