#include "header.h"

#define ROM_SIZE 64*1024

void output_code(instr *code)
{
    FILE *fp;

    char temp[NAMESIZE+60] = "./assembler_output/";
    int complied_bytes = 0;
    int len = strlen(filename);

    filename[len-4] = '.';
    filename[len-3] = 't';
    filename[len-2] = 'x';
    filename[len-1] = 't';
    filename[len] = '\0';

    fp = fopen(strcat(temp,filename), "w");
    int i = 0;

    while (i <= ROM_SIZE)
    {
        for (int j = 0; j < MAX_LINES_NUM; ++j)
        {
            if (code[j].instr == NULL) break;

            if (code[j].adr == i)
            {
                if (strcmp(code[j].instr, ".DW") == 0)
                {
                    int lowByte = atoi(code[j].operand) & 0x00FF;
                    int highByte = (atoi(code[j].operand) & 0xFF00) >> 8;

                    fprintf(fp, "%02x\n", lowByte);
                    fprintf(fp, "%02x\n", highByte);
                    i++;
                    complied_bytes += 2;
                }

                else if (strcmp(code[j].instr, ".DB") == 0)
                {

                    if (strstr(code[j].operand, ",") == NULL)
                    {
                        fprintf(fp, "%02x\n", atoi(code[j].operand));
                        complied_bytes++;
                    }
                    else
                    {
                        char *pt;
                        pt = strtok (code[j].operand,",");
                        int count = 0;
                        while (pt != NULL) 
                        {
                            fprintf(fp, "%02x\n", atoi(pt));
                            count++;
                            complied_bytes++;
                            pt = strtok (NULL, ",");
                        }
                        i += count;
                    }

                }

                else if (strcmp(code[j].instr, ".TX") == 0)
                {
                    for (int k = 0; k < strlen(code[j].operand); ++k)
                    {
                        fprintf(fp, "%02x\n", code[j].operand[k]);
                        i++;
                        complied_bytes++;
                    }
                    i--;
                }

                else if (strstr(code[j].adr_m, "immediate") || strstr(code[j].adr_m, "zeropage"))
                {
                    fprintf(fp, "%02x\n", code[j].opcode);
                    fprintf(fp, "%02x\n", atoi(code[j].operand));
                    complied_bytes += 2;
                    i++;
                }

                else if (code[j].operand != NULL)
                {
                    fprintf(fp, "%02x\n", code[j].opcode);
                    
                    int lowByte = atoi(code[j].operand) & 0x00FF;
                    int highByte = (atoi(code[j].operand) & 0xFF00) >> 8;

                    fprintf(fp, "%02x\n", lowByte);
                    fprintf(fp, "%02x\n", highByte);
                    i += 2;
                    complied_bytes += 3;
                }
                
                else
                {
                    fprintf(fp, "%02x\n", code[j].opcode);
                    complied_bytes++;
                } 
            
                goto skip;
            }
        }

        fprintf(fp, "0\n");
        skip:
            i++;
    }
    fclose(fp);

    printf("\n%d Bytes Complied", complied_bytes);
}