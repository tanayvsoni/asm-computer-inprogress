#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>


#if defined(__WIN32)
    #define PATH "\\programs\\"
#elif defined(__APPLE__)
    #define PATH "/assembler/programs/"
#endif

#define NAMESIZE         60
#define MAX_CHARS        80
#define MAX_LINES_NUM    60000

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
    int value;
} vars;

typedef struct 
{
    int linenum;
    int address;
} orgs;

void rm_whitespace(char *word)
{
    char *d = word;

    do {
        while (*d == ' ' || *d == '\t') {
            ++d;
        }
    } while (*word++ = *d++);

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
        token = strtok(num,"%%");
        int_num = (int)strtol(token, NULL, 2);
    }
    else
    {   
        int_num = (int)strtol(num, NULL, 10);  
    }

    return int_num;
}

#endif