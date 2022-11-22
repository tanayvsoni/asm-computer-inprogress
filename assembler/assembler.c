#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <limits.h>

// FOR MAC
//#define PATH "/assembler/programs/"

//FOR WINDOWS
#define PATH "./programs/"

#define MAX_LINE_CHAR 100
#define MAX_LINE_NUM 1000
#define MAX_LABELS 1000

typedef struct
{
    char *name;
    int address;
} labels;
    

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
                if (str[char_count-1] != ' ' && str[char_count] == ' ' && str[char_count + 1] != ' ') {
                    lines[line_count][char_count] = '~';
                }
                // Skips any comments
                else if (str[char_count] == ';') {
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
    
    int j = 0;
    for (int i = 0; i < line_count; i++) {
        // Remove white space and ensure any blanks elements are not stored
        rm_whitespace(lines[i]);
        if (*lines[i] != '\0') {
            file_lines[j] = lines[i];
            ++j;
        }
    }

    size[0] = j;

    fclose(ptr);
    free(dir_path);
    
    return file_lines;
}

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
        int_num = (int)strtol(token, NULL, 10);  
    }

    return int_num;
}

void update_labelData(labels *a, int index, char *n, int adr)
{
    a[index].name = n;
    a[index].address = adr;
}

bool check_labelList(labels *a, char *label_name)
{
    if (a[0].name == NULL)
    {
        return true;
    }

    for (int i = 0; i < (sizeof(a)/sizeof(a[0])); ++i)
    {
        if (strcmp(a[i].name, label_name) == 0)
        {
            printf("\n__%s__\n", a[i].name);
            return false;
        }
    }
    return true;
}

void address_sorting(char **code, int *size)
{
    int *address = (int*)(malloc(*size*sizeof(int)));
    int current_adr = 0;
    int *j = (int*)(malloc(1*sizeof(int)));
    *j = 0;

    labels label_list[MAX_LABELS];
    int label = 0;

    char *token;
    char **new_code = (char**)(malloc(*size*sizeof(char*)));

    for (int i = 0; i < *size; ++i)
    {
        int change_adr = 1;
        if (strstr(code[i], ".ORG"))
        {
            token = strtok(code[i], "~");
            token = strtok(NULL, "~");

            current_adr = convert_num(token);
            change_adr = 0;
        }

        else if (strstr(code[i], ":"))
        {
            token = strtok(code[i], "~");
            token = strtok(token, ":");

            if (check_labelList(label_list, token))
            {
                update_labelData(label_list,label,token, current_adr);
                printf(" %d |", label_list[label].address); 
                ++label;    
            }
            change_adr = 0;
        }
        else
        {
            current_adr += change_adr;
            new_code[*j] = code[i];
            address[*j] = current_adr;
            ++*j;
        }
    }
    //printf("\n");
    for (int i = 0; i < *j; ++i){
        //printf(" %d |", address[i]);
    }

    //printf("\n");
    //print_arr(new_code,j);
}

int main()
{
    char *dir_path;
    dir_path = get_filename();

    char **file_lines;
    int *address;
    int *size = (int*)(malloc(1*sizeof(int)));

    file_lines = get_file(dir_path, size);

    print_arr(file_lines,size);

    address_sorting(file_lines,size);

    return 0;
}