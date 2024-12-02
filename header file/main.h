#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_DNUM 8

extern int LOC = 0, LDaddr, GOaddr, PGsize;
extern char LBUF[128], * LNO, * LABEL, * OPcode, * OPerand;
extern unsigned char OBJC[MAX_DNUM * 4 + 1];
