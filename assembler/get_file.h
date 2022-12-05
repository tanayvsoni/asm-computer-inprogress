#include "header.h"

char *get_dir()
{
    char *dir;

    char buf[PATH_MAX + 1];
    dir = getcwd(buf, PATH_MAX + 1);

    printf("Please enter file name: ");
    scanf("%s", filename);

    strcat(dir, PATH);
    strcat(dir, filename);

    char *dir_output = (char*)malloc(strlen(dir) + 1);
    memcpy(dir_output, dir, strlen(dir) + 1);
    
    return dir_output;
}

bool remove_comments(char str[], bool comment_block)
{

    char new_str[strlen(str)+1];
    int i,j;


    for (i = 0, j = 0; i < strlen(str) + 1; ++i)
    {
        // Finds start of comment_block block
        if (i < strlen(str) && str[i] == '/' && str[i+1] == '*')
        {
            comment_block = true;
        }

        // Breaks out of line if ; appears
        if (str[i] == ';' && !comment_block)
        {
            break; 
        }

        // Only adds items to new list if not in comment block
        if (!comment_block && (str[i] != '\n' || str[i] != '\0'))
        {
            new_str[j] = str[i];
            ++j;
        }

        // Exit out of comment block
        if (i != 0 && str[i-1] == '*' && str[i] == '/')
        {
            comment_block = false;
        }
    }

    new_str[j] = '\n';
    new_str[j+1] = '\0';

    memcpy(str, new_str, strlen(new_str) + 1);

    return comment_block;
}

bool is_line_empty(char str[])
{
    for (int i = 0; i < MAX_CHARS; ++i)
    {
        if (str[i] == '\0') break;

        if (str[i] != '\t' || str[i] != '\n' || str[i] != ' ')
            return false;
    }

    return true;
}

char **og_code(int *size)
{   
    bool comment_block = false;
    static char str[MAX_CHARS], lines[MAX_LINES_NUM][MAX_CHARS];
    *size = 0;
    
    char **code = (char**)(malloc(MAX_LINES_NUM*sizeof(char)));

    char *dir = get_dir();
    FILE *ptr = fopen(dir,"r");

    if (ptr == NULL)
    {
        printf("File can't be opened \n"); 
        exit(1);
    }


    while(fgets(str, MAX_CHARS, ptr) != NULL)
    {
        comment_block = remove_comments(str, comment_block);

        // Removes empty lines
        if (strcmp(str,"\n"  ) != 0 &&
            strcmp(str,"\r\n") != 0 &&
            strcmp(str,"\0"  ) != 0 &&
        1)
        {
            memcpy(lines[*size], str, strlen(str) + 1);
            //printf("%s", lines[i]);
            ++*size;
        }      
    }

    free(dir);
    fclose(ptr);

    for (int i = 0; i < *size; ++i)
    {
        code[i] = lines[i];
    }

    return code;
}