#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "get_file.c"

#define MAX_LABELS      1000
#define MAX_ORGS        1000
#define MAX_VARS        10

typedef struct
{
    char *name;
    int linenum;
    int address;
} labels;

typedef struct 
{
    char *name;
    int address;
} vars;

typedef struct 
{
    int linenum;
    int address;
} orgs;

void print_arr(char **file, int *size)
{
    for (int i = 0; i < *size; ++i) {
        printf("%s", file[i]);
    }

    printf("\n");
}

int convert_num(char *num)
{
    char *token;
    int int_num;

    if (strstr(num, "$") == 0)
    {
        token = strtok(num,"$");
        int_num = (int)strtol(token, NULL, 16);
    }
    else if (strstr(num, "%%") == 0)
    {
        token = strtok(num,"%%");
        int_num = (int)strtol(token, NULL, 2);
    }
    else
    {   
        int_num = (int)strtol(num, NULL, 10);  
    }

    return int_num;
}

void get_vars(vars *v, char **code, int *code_size)
{
    int i,j;
    bool existing = false;
    char *var_name;
    char *temp;
    int adr;

    for (i = 0; i < *code_size; ++i)
    {
        if (strstr(code[i], "="))
        {
            var_name = strtok(code[i], "=");
            temp = strtok(NULL, "=");
            adr = convert_num(temp);

            /*for (j = 0; j < MAX_VARS; ++j)
            {   
                if (v[j].name == NULL) { break; }

                if (strcmp(v[j].name, var_name))
                { existing = true; break; }
            }

            if (!existing) { j = i; }*/

            v[i].name = var_name;
            v[i].address = adr;
        }
    }
}

int main()
{
    int *size = (int*)(malloc(sizeof(int)));
    char **code = og_code(size);

    labels labels_list[MAX_LABELS];
    orgs orgs_list[MAX_ORGS];
    vars vars_list[MAX_VARS];

    get_vars(vars_list, code, size);

    for (int i = 0; i < MAX_VARS; ++i)
    {
        printf("Name: %s | Adr: %d\n", vars_list[i].name, vars_list[i].address);
    }
    print_arr(code,size);

    return 0;
}