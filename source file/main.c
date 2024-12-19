#include "main.h"

#include "asc_s10.h"
#include "asm_mnmo.h"
#include "asm_space.h"
#include "cal_drctv.h"
#include "cal_expr.h"
#include "cal_mnmo.h"
#include "cal_term.h"
#include "dctab.h"
#include "optab.h"
#include "put_list.h"
#include "rdline.h"
#include "str2int.h"
#include "symtab.h"

char* null_LNO = "   ";
char* null_LBL = "   ";
char* null_OPR = "   ";


void OnePassAssemble(char* sfile) {
    FILE* fp;
    Optab* op;
    Dctab* dp;
    int len;

    if (!(fp = fopen(sfile, "r"))) {
        fprintf(stderr, "File '%s' not found... \n", sfile);
        exit(1);
    }
    put_list_head();
    read_list_head();

    if (!LABEL) LABEL = "ASMBLY";
    if (!OPcode || strcmp(OPcode, "START") != 0) {
        fprintf(stderr, "\n%s --> Program name is not defined ...\n", LBUF);
        exit(2);
    }
    if (OPerand && (LOC = str2int(OPerand)) < 0) {
        fprintf(stderr, "\n%s --> Start address is invalid ...\n", LBUF);
        exit(3);
    }

    ins_SYMTAB(LOC, LABEL);

    put_list();
    LDaddr = GOaddr = LOC;
    PGsize = LOC - LDaddr;

    while (read_line(fp) > 0) {
        if (!OPcode) {
            fprintf(stderr, "\n%s --> Opcode is not defined ...\n", LBUF);
            exit(4);
        }
        if (!strcmp(OPcode, "END")) break;
        if (LABEL) {
            if (strlen(LABEL) > MAX_SYM) {
                fprintf(stderr, "\n%s --> Symbol '%s' is too long ...\n", LBUF, LABEL);
                exit(5);
            }
            if (!ins_SYMTAB(LOC, LABEL)) {
                fprintf(stderr, "\n%s --> Symbol '%s' is duplicated ...\n", LBUF, LABEL);
                exit(6);
            }
        }
        if ((op = see_OPTAB(OPcode))) {
            len = asm_mnemonic(op);
        }
        else if ((dp = see_DCTAB(OPcode))) {
            len = asm_space(dp);
        }
        else {
            fprintf(stderr, "\n%s --> Opcode '%s' is not valid...\n", LBUF, OPcode);
            exit(6);
        }

        if (!OPerand) OPerand = null_OPR;

        if (!LNO) LNO = null_LNO;
        if (!LABEL) LABEL = null_LBL;
        put_list();
        LOC += len;
    }

    if (!OPcode || strcmp(OPcode, "END") != 0) {
        fprintf(stderr, " --> 'END' opcode is not defined ...\n");
        exit(7);
    }
    if (OPerand) {
        GOaddr = cal_nm_oprnd(OPerand);
    }
    else {
        OPerand = null_OPR;
    }

    LNO = " ";

    LABEL = null_LBL;
    put_list();
    exit(0);
}

int main(int argc, char* argv[]) {
    
    OnePassAssemble(argv[1]);

    return 0;
}
