#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <limits.h>

// FOR MAC
//#define PATH          "/assembler/programs/"

//FOR WINDOWS
#define PATH            "./programs/"

#define MAX_LINE_CHAR   100
#define MAX_LINE_NUM    1000
#define MAX_LABELS      1000
#define MAX_ORGS        1000
#define MAX_VARS        1000

typedef struct
{
    char *name;
    int address;
    int linenum;
} labels;

typedef struct 
{
    char *name;
    int address;
} variables;


typedef struct 
{
    int linenum;
    int address;
} orgs;


char *strremove(char *str, const char *sub) {
    size_t len = strlen(sub);
    if (len > 0) {
        char *p = str;
        while ((p = strstr(p, sub)) != NULL) {
            memmove(p, p + len, strlen(p + len) + 1);
        }
    }
    return str;
}

void print_arr(char **file, int *size)
{
    for (int i = 0; i < *size; ++i) {
        printf(" %s |", file[i]);
    }

    printf("\n");
}

/*get file & organize data*/

void rm_whitespace(char *word)
{
    char *d = word;

    do {
        while (*d == ' ' || *d == '\n' || *d == '\t') {
            ++d;
        }
    } while (*word++ = *d++);

}

char *get_filename()
{
    /* Prompts user to get file name and returns directory */

    // FOR MAC
    char *dir;
    char buf[PATH_MAX + 1];
    dir = getcwd(buf, PATH_MAX + 1);
    strcat(dir, PATH);

    char *filename = (char*)(malloc(60*sizeof(char)));

    printf("Enter file name: ");
    scanf("%s", filename);

    strcat(dir, filename);

    char *dir_pointer;
    dir_pointer = (char *)malloc(strlen(dir) + 1);

    // Save directory name into array and returns pointer
    for (int i = 0; i < strlen(dir) + 1; i++) { 
        dir_pointer[i] = dir[i]; 
    }

    //free(filename);
    return dir_pointer;
}

char **get_file(char *dir_path, int *size)
{
    FILE *ptr;
    char str[MAX_LINE_CHAR];
    char lines[MAX_LINE_NUM][MAX_LINE_CHAR];

    char **file_lines;
    file_lines = malloc(MAX_LINE_NUM*sizeof(char*));

    int line_count = 0;

    ptr = fopen(dir_path,"r");

    // Check if file exists
    if (NULL == ptr)
    { 
        printf("File can't be opened \n"); 
        exit(1);
    }

    while (fgets(str,MAX_LINE_CHAR,ptr))
    {
        // Only reads files with code; skips empty lines
        if ( strcmp(str,"\n") != 0 && strcmp(str, "\r\n") != 0 && strcmp(str, "\0") != 0 && 1) {

            for (int char_count = 0; char_count < strlen(str); char_count++) {

                // Replace single space between instructions with ~   
                /*if (str[char_count-1] != ' ' && str[char_count] == ' ' && str[char_count + 1] != ' ') {
                    lines[line_count][char_count] = '~';
                }
                // Skips any comments
                else*/ if (str[char_count] == ';') {
                    break; 
                }
                
                // Makes use not to store \n character and captializes str
                else if (str[char_count] != '\n') {
                    lines[line_count][char_count] = toupper(str[char_count]);
                }
            }
            line_count++;
        }
    }
    
    *size = 0;
    for (int i = 0; i < line_count; i++) {
        // Remove white space and ensure any blanks elements are not stored
        rm_whitespace(lines[i]);
        if (*lines[i] != '\0') {
            file_lines[*size] = lines[i];
            ++*size;
        }
    }

    fclose(ptr);
    free(dir_path);
    
    return file_lines;
}

/*org & label sorting functions*/

int convert_num(char *num)
{
    char *token;
    int int_num;

    if (*num == '$')
    {
        token = strtok(num,"$");
        int_num = (int)strtol(token, NULL, 16);
    }
    else if (*num == '%')
    {
        token = strtok(num,"%");
        int_num = (int)strtol(token, NULL, 2);
    }
    else
    {   
        int_num = (int)strtol(num, NULL, 10);  
    }

    return int_num;
}

void update_labelData(labels *a, int index, char *n, int adr, int linum)
{
    a[index].name = n;
    a[index].address = adr;
    a[index].linenum = linum;

    //printf("\n%s, %d\n", a[index].name, a[index].address);
}

void update_varData(variables *a, int *index, char *n, int adr)
{

    if (index != 0)
    {
        for (int i = 0; i < *index; ++i)
        {
            if (strcmp(a[i].name, n) == 0) 
            { 
                *index = i; 
            }
        }
    }
    
    a[*index].name = n;
    a[*index].address = adr;

}

void update_orgData(orgs *a, int index, int linum, int adr)
{
    a[index].linenum = linum;
    a[index].address = adr;

    //printf("\n%d, %d\n", a[index].linenum, a[index].address);
}

bool check_labelList(labels *a, char *label_name, int label_arrSize)
{
    if (label_arrSize != 0)
    {
        for (int i = 0; i < label_arrSize; ++i)
        {
            if (strcmp(a[i].name, label_name) == 0)
            {
                //printf("\n__%s__\n", a[i].name);
                return false;
            }
        }
    }
    return true;
}

void replace_labels(char **code, int *code_size, char *labelName, int labelAdr)
{ 
    for (int i = 0; i < *code_size; ++i)
    {
        if (strstr(code[i], labelName))
        {
            
            strtok(code[i], "~");
            char buf[sizeof(int) * 4 + 1];
            sprintf(buf, "~%d", labelAdr);
            strcat(code[i], buf);

            //printf("\n---%s---\n", code[i]);

        }
    }
}

char **org_label_sorting(labels *label_list, orgs *orgs_list, variables *vars_list, int *label, int *org, int *var, char **code, int *size, int *new_linenum)
{
    *new_linenum = 0;
    *label = 0;
    *org = 0;
    *var = 0;

    char *token;
    char **new_code = (char**)(malloc(*size*sizeof(char*)));

    for (int i = 0; i < *size; ++i)
    {
        if (strstr(code[i], ".ORG"))
        {
            //token = strtok(code[i], "~");
            //token = strtok(NULL, "~");
            token = strtok(code[i], ".ORG");

            int adr = convert_num(token);
            update_orgData(orgs_list, *org, *new_linenum, adr);
            ++*org;
        }

        else if (strstr(code[i], ":"))
        {
            //token = strtok(code[i], "~");
            token = strtok(code[i], ":");

            if (check_labelList(label_list, token, *label))
            {
                update_labelData(label_list, *label, token, 0, *new_linenum);
                ++*label;    
            }
        }

        else if (strstr(code[i], "="))
        {
            char *name = strtok(code[i], "=");
            token = strtok(NULL, "=");

            int adr = convert_num(token);

            update_varData(vars_list, var, name, adr);   
            ++*var; 
        }

        else
        {
            new_code[*new_linenum] = code[i];
            ++*new_linenum;
        }
    }

    return new_code;
}

char **rep_labelsVars(labels *label_list, orgs *orgs_list, variables *vars_list, int *label, int *org, int *var, char **code, int *size)
{
    bool load_imd[*size];
    char spacing = '~';
    
    for (int i = 0; i < *size; ++i)
    {
        if (code[i][3] == '#')
        {
            load_imd[i] = true;
        } else {load_imd[i] = false;}
    }

    for (int i = 0; i < *size; ++i)
    {
        if (load_imd[i])
        {

        }
    }
}

int main()
{
    char *dir_path;
    char **file_lines;
    char **parsed_code;
    
    int *size = (int*)(malloc(sizeof(int)));
    int *parsed_codeSize = (int*)(malloc(sizeof(int)));

    labels labels_list[MAX_LABELS];
    orgs orgs_list[MAX_ORGS];
    variables vars_list[MAX_VARS];

    int *ll_size = (int*)(malloc(sizeof(int)));
    int *ol_size = (int*)(malloc(sizeof(int)));
    int *vl_size = (int*)(malloc(sizeof(int)));


    dir_path = get_filename();

    file_lines = get_file(dir_path, size);
    
    parsed_code = org_label_sorting(labels_list, orgs_list, vars_list, ll_size, ol_size, vl_size, file_lines,size,parsed_codeSize);

    print_arr(parsed_code,parsed_codeSize);

    //rep_labelsVars(labels_list, orgs_list, vars_list, ll_size, ol_size, vl_size, file_lines,parsed_codeSize);

    /*-------------------------------------------------------------------*/ 

    printf("\n----Variables----\n");

    for (int i = 0; i < *vl_size; ++i)
    {
        printf("%s: %d\n", vars_list[i].name, vars_list[i].address);
    }

    printf("\n----Labels----\n");

    for (int i = 0; i < *ll_size; ++i)
    {
        printf("%d: %s, %d\n",labels_list[i].linenum, labels_list[i].name, labels_list[i].address);
    }

    printf("\n----Orgs----\n");

    for (int i = 0; i < *ol_size; ++i)
    {
        printf("%d: %d\n", orgs_list[i].linenum, orgs_list[i].address);
    }

    /*-------------------------------------------------------------------*/ 

    return 0;
}