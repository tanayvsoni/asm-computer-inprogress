#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int instr_opcode(char *instr)
{
    return 1;
}

void *rm_whitespace(char *word)
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


    char filename[20];
    char dir[] = "./programs/";

    printf("Enter file name: ");
    scanf("%s", &filename);

    strcat(dir, filename);

    char *dir_pointer;
    dir_pointer = (char *)malloc(strlen(dir) + 1);

    // Save directory name into array and returns pointer
    for (int i = 0; i < strlen(dir) + 1; i++) { 
        dir_pointer[i] = dir[i]; 
    }

    return dir_pointer;
}

char **get_file(char *dir_path, int *size)
{
    FILE *ptr;
    char str[60];
    char lines[1000][60];

    char **file_lines;
    file_lines = malloc(1000*sizeof(char*));

    int line_count = 0;

    ptr = fopen(dir_path, "r");

    // Check if file exists
    if (NULL == ptr)
    { printf("File can't be opened \n"); }

    while (fgets(str,60,ptr))
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
                
                // Makes use not to store \n character
                else if (str[char_count] != '\n') {
                    lines[line_count][char_count] = str[char_count];
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

void print_arr(char **file, int *size)
{
    for (int i = 0; i < *size; ++i) {
        printf(" %s |", file[i]);
    }
}

int main()
{
    char *dir_path;
    dir_path = get_filename();

    char **file_lines;
    int *address;
    int *size;
    size = (malloc(1*sizeof(int)));

    file_lines = get_file(dir_path, size);

    

    print_arr(file_lines,size);

    return 0;
}