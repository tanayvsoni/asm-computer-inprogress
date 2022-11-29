#include "header.h"

#include "get_file.c"
#include "./get_constants/get_vars.c"
#include "./get_constants/get_orgs.c"
#include "./get_constants/get_labels.c"
#include "1stparse.c"

void print_vars(vars *vars_list)
{
    for (int i = 0; i < MAX_VARS; ++i)
    {
        if (vars_list[i].name != NULL)
        {
            printf("Name: %s | Value: %d\n", vars_list[i].name, vars_list[i].value);
        }
    }
}

void print_labels(labels *labels_list)
{
    for (int i = 0; i < MAX_LABELS; ++i)
    {
        if (labels_list[i].name != NULL)
        {
            printf("Linenum: %d | Name: %s\n", labels_list[i].linenum, labels_list[i].name);
        }
    }
}

void print_orgs(orgs *orgs_list)
{
    for (int i = 0; i < MAX_ORGS; ++i)
    {
        if (orgs_list[i].address != 0)
            printf("Linenum: %d | Address: %d\n", orgs_list[i].linenum, orgs_list[i].address);
    }
}

void print_instr(instr *parsed_code)
{
    for (int i = 0; i < MAX_LINES_NUM; ++i)
    {
        if (parsed_code[i].instr != NULL)
            printf("Instr: %s | %s\nAdr Mode: %s | %d\n\n", parsed_code[i].instr, parsed_code[i].operand, 
                                                 parsed_code[i].adr_m, parsed_code[i].adr_del);
    } 
}

void exit_prg()
{
    printf("\nWrite # to exit");
    char c;
    while ((c = getchar()) != '#')
        putchar(c);
}

int main()
{
    labels labels_list[MAX_LABELS] = {};
    orgs orgs_list[MAX_ORGS] = {};
    vars vars_list[MAX_VARS] = {};

    int *size = (int*)(malloc(sizeof(int)));
    char **code = og_code(size);

    code = get_vars(vars_list, code, size);
    code = get_labels(labels_list, vars_list, code, size);
    code = get_orgs(orgs_list, code, size);

    
    printf("\n");
    print_labels(labels_list);
    printf("\n");
    print_vars(vars_list);
    printf("\n");
    print_orgs(orgs_list);
    printf("\n");
    

    instr parsed_code[MAX_LINES_NUM] = {};
    parse(parsed_code, labels_list, vars_list, code, *size);

    //print_arr(code,size);
    print_instr(parsed_code);

    //exit_prg();

    return 0;
}