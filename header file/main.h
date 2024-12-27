#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_DNUM 8
#define MAX_OLEN 8
#define MAX_SYM 100
#define MAX_SLEN (8+1)
#define INV_VAL (-0x7fffffff)
#define RND_OPR 0x7fffffff

extern int LOC, LDaddr, GOaddr, PGsize;
extern char LBUF[128], * LNO, * LABEL, * OPcode, * OPerand;
extern unsigned char OBJC[MAX_DNUM * 4 + 1];

typedef struct symtab {
    char symbol[MAX_SLEN];
    int value;
} Symtab;

extern int SYMCNT;
extern Symtab SYMTAB[MAX_SYM];

int see_SYMTAB(char* sym);
int ins_SYMTAB(int value, char* sym);

typedef struct optab {
    char mnemonic[MAX_OLEN];
    unsigned char opcode;
    unsigned char n_operand;
} Optab;

extern Optab OPTAB[];

int see_OPTAB(char* opc);
int str2int(char* sp);
int dec2int(char* sp_dec);
int hex2int(char* sp_hex);

void put_list_head();
void put_list();
int read_line(FILE* fp);

#endif // MAIN_H
