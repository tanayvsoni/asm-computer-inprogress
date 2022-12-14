#include "../header.h"

static bool overwrite_labels(labels *l, char *label_name, int line_num)
{   
    for (int i = 0; i < MAX_LABELS; ++i)
    {
        if (l[i].name != NULL && (strcmp(l[i].name, label_name) == 0))
        {
            l[i].name = label_name;
            l[i].linenum = line_num;
            return true;
        }
    }

}

char **get_labels(labels *l, vars *v, char **code, int *code_size)
{
    int i,j, line_num, amount_labels;
    bool existing;
    char *label_name, **newcode;

    // Initialize labels list
    for(int i = 0; i < MAX_LABELS; ++i)
    {
        l[i].name = NULL;
        l[i].address = 0;
        l[i].linenum = 0;
    }

    newcode = (char**)(malloc(MAX_LINES_NUM*sizeof(char)));

    for (i = 0, j = 0, line_num = 0, amount_labels = 0, existing = false; i < *code_size; ++i)
    {
        if (strstr(code[i], ":"))
        {
            rm_whitespace(code[i]);
            label_name = strtok(code[i], ":");
            
            if (!isInVars(v,label_name))
            {
                existing = overwrite_labels(l, label_name, line_num);

                if (!existing)
                {
                    l[amount_labels].name = label_name;
                    l[amount_labels].linenum = line_num;
                    ++amount_labels;
                }
            }  
        }
        else if (strstr(code[i], ".org") == NULL) 
        {
            ++line_num;
            newcode[j++] = code[i]; 
        }
        else newcode[j++] = code[i]; 
    }

    *code_size = j;
    free(code);
    return newcode;
}