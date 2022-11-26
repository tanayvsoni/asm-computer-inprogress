#include "header.h"

#include "get_file.c"
#include "get_vars.c"

int main()
{
    int *size = (int*)(malloc(sizeof(int)));
    char **code = og_code(size);

    labels labels_list[MAX_LABELS];
    orgs orgs_list[MAX_ORGS];
    vars vars_list[MAX_VARS];

    code = get_vars(vars_list, code, size);

    /*for (int i = 0; i < MAX_VARS; ++i)
    {
        printf("Name: %s | Val: %d\n", vars_list[i].name, vars_list[i].value);
    }*/
    print_arr(code,size);

    return 0;
}