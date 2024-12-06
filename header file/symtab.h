#define MAX_SYM	100
#define MAX_SLEN (8+1)
#define INV_VAL (-0x7fffffff)
#define RMD_OPR 0x7fffffff

#include "main.h"

typedef struct symtab {
	char symbol[MAX_SLEN];
	int value;
} Symtab;

int SYMCNT = 1;
Symtab SYMTAB[MAX_SYM] = { "RND", RND_OPR, };

int ins_SYMTAB(int value, char* sym) {
	if (see_SYMTAB(sym) != INV_VAL)
		return 0;
	strcpy(SYMTAB[SYMCNT].symbol, sym);
	SYMTAB[SYMCNT].value = value;
	SYMCNT++;
	return 1;
}

int see_SYMTAB(char* sym) {
	int i;

	for (i = 0; i < SYMCNT; i++) {
		if (!strcmp(SYMTAB[i].symbol, sym))
			return(SYMTAB[i].value);
	}

	return INV_VAL;
}
