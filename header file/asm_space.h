#include "symtab.h"
#include "optab.h"
#include "cal_mnmo.h"

int asm_space(Dctab* dp) {
    int len;

    if (!Operand) {
        fprintf(stderr, "%s ---> Operand is not defined ...\n", LBUF);
        exit(10);
    }

    if (dp->type == DC_RESV) {
        if ((!isdigit(Operand[0]) && Operand[strlen(Operand) - 1] != 'h') ||
            (len = str2int(Operand)) == INV_VAL) {
            fprintf(stderr, "%s ---> Operand number '%s' is not valid ...\n", LBUF, Operand);
            exit(11);
        }
        len *= dp->unit;
        OBJC[0] = 0;

        return len;
    }

    if (dp->unit == 1 && Operand[0] == '\'') {
        len = cal_dc_oprnd_string(Operand, OBJC);
    }
    else {
        len = cal_dc_oprnd(Operand, dp->unit, OBJC);
    }

    return len;
}
