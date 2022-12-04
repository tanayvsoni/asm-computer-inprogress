#include "header.h"
#include"./dictionary/entry.h"

int linenum_Orgs(orgs *orgs_list, int line)
{
    for (int i = 0; i < MAX_ORGS; ++i)
    {
        if (orgs_list[i].linenum == line) return orgs_list[i].address;
    }

    return 0;
}

void set_adr(instr *code, orgs *orgs_list)
{
    for (int i = 0; MAX_LINES_NUM; ++i)
    {
        if (code[i].instr == NULL) break;
        
        if (linenum_Orgs(orgs_list, i) != 0)
        {
            code[i].adr = linenum_Orgs(orgs_list, i);
        }
        else
        {
            code[i].adr = code[i-1].adr + code[i-1].adr_del;
        }
    }
}

void set_labels(labels *l, instr *code)
{
    for (int i = 0; i < MAX_LINES_NUM; ++i)
    {
        if (code[i].instr == NULL) break;

        for (int j = 0; j < MAX_LABELS; ++j)
        {
            if (l[j].name == NULL) break;

            if (l[j].linenum == i)
                l[j].address = code[i].adr;
        }
    }
}