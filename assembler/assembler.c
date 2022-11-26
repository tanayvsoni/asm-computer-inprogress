#include "header.h"

#include "get_file.c"
#include "get_vars.c"
#include "get_orgs.c"
#include "get_labels.c"

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

int main()
{
    labels labels_list[MAX_LABELS] = {};
    orgs orgs_list[MAX_ORGS] = {};
    vars vars_list[MAX_VARS] = {};

    int *size = (int*)(malloc(sizeof(int)));
    char **code = og_code(size);
    code = get_vars(vars_list, code, size);

    code = get_labels(labels_list, vars_list, code, size);

    printf("\n");
    print_labels(labels_list);
    printf("\n");
    print_vars(vars_list);
    printf("\n");

    print_arr(code,size);

    return 0;
}