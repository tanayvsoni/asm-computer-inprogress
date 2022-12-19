#include "header.h"

#include "get_file.h"

#include "./get_constants/get_vars.h"
#include "./get_constants/get_orgs.h"
#include "./get_constants/get_labels.h"

#include "./instructions/1stparse.h"
#include "./dictionary/entry.h"

#include "./instructions/2ndparse.h"
#include "./instructions/dataBytesAndText.h"
#include "set_addresses.h"
#include "./instructions/3rdparse.h"

#include "output.h"

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
            printf("Linenum: %d | Name: %s | Adr: %d\n", labels_list[i].linenum, labels_list[i].name, labels_list[i].address);
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
            printf("Instr: %s | %s\nAdr Mode: %s | %d\nOPCODE: %d | ADR: %d\n\n", parsed_code[i].instr, parsed_code[i].operand, 
                                                 parsed_code[i].adr_m, parsed_code[i].adr_del, parsed_code[i].opcode, parsed_code[i].adr);
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
    labels *labels_list = (labels*)(malloc(MAX_LABELS*sizeof(labels)));
    orgs *orgs_list = (orgs*)(malloc(MAX_ORGS*sizeof(orgs)));
    vars *vars_list = (vars*)(malloc(MAX_VARS*sizeof(vars)));

    instr *parsed_code = (instr*)(malloc(MAX_LINES_NUM*sizeof(instr)));

    // Initialize dictionary array
    dictionary *d = (dictionary*)(malloc(MAX_LINES_NUM*sizeof(dictionary)));

    for (int i = 0; i < MAX_LINES_NUM; ++i)
    {
        d[i].instr = NULL;
        d[i].adr_mode = NULL;
        d[i].value = 0;
    }

    // Import entrys into dictionary
    new_entry(d);

    int *size = (int*)(malloc(sizeof(int)));
    char **code = og_code(size);

    code = get_vars(vars_list, code, size);
    code = get_labels(labels_list, vars_list, code, size);
    code = get_orgs(orgs_list, code, size);


    //print_arr(code,size);
    first_parse(parsed_code, labels_list, vars_list, code, *size);
    free(size);
    second_parse(d, labels_list, vars_list, parsed_code);
    data_bytes(d, parsed_code);
    set_adr(parsed_code,orgs_list);
    set_labels(labels_list, parsed_code);
    third_parse(d,labels_list,parsed_code);

    print_instr(parsed_code);

    /*printf("\n");
    print_labels(labels_list);
    printf("\n");
    print_vars(vars_list);
    printf("\n");
    print_orgs(orgs_list);*/

    output_code(parsed_code);
    
    //exit_prg();

    return 0;
}