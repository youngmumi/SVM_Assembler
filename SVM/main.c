#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int LOC = 0, LDaddr, GOaddr, PGsize;
char LBUF[128], * LNO, * LABEL, * OPcode, * OPerand;
unsigned char OBJC[MAX_DNUM * 4 + 1];
char* null_LNO = "   ";
char* null_LBL = "   ";
char* null_OPR = "   ";

void OnePassAssemble(char* sfile) {
    FILE* fp;
    Optab* op;
    Dctab* dp;
    int len;

    if (!(fp = fopen(sfile, "r")))
        stderr("File '%s' not found... \n", sfile), exit(1);
    put_list_head();
    read_list_head();

    if (!LABEL) LABEL = "ASMBLY";
    if (!OPcode || strcmp(OPcode, "START"))
        fprintf(stderr, "\n%s --> Program name is not defined ...\n", LBUF), exit(2);
    if (OPerand && (LOC = str2int(OPerand)) < 0)
        fprintf(stderr, "\n%s --> Start address is invalid ...\n", LBUF), exit(3);

    ins_SYMTAB(LOC, LABEL);

    put_list();
    LDaddr = GOaddr = LOC;
    PGsize = LOC - LDaddr;

    while (read_line(fp) > 0) {
        if(!OPcode) fprintf(stderr,)
    }
}
int main()
{
    
}

