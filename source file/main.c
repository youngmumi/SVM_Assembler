#include "main.h"

int LOC = 0, LDaddr, GOaddr, PGsize;
char LBUF[128], * LNO, * LABEL, * OPcode, * OPerand;
unsigned char OBJC[MAX_DNUM * 4 + 1];

int SYMCNT = 1;
Symtab SYMTAB[MAX_SYM] = { {"RND", RND_OPR} };

Optab OPTAB[] = {
    {"LDA", 0x00, 1}, {"LDAW", 0x01, 1}, {"LDAB", 0x02, 1},
    {"LDX", 0x04, 1}, {"LDU", 0x05, 1},
    {"STA", 0x08, 1}, {"STAW", 0x09, 1}, {"STAB", 0x0A, 1},
    {"STX", 0x0C, 1}, {"STU", 0x0D, 1},
    {"ADD", 0x10, 1}, {"ADDW", 0x11, 1}, {"ADDB", 0x12, 1},
    {"SUB", 0x14, 1}, {"SUBW", 0x15, 1}, {"SUBB", 0x16, 1}, {"MOD", 0x17, 1},
    {"AND", 0x18, 1}, {"OR", 0x19, 1},   {"XOR", 0x1A, 1},
    {"SHL", 0x1C, 1}, {"SHR", 0x1D, 1},
    {"CMP", 0x20, 1}, {"CMPW", 0x21, 1}, {"CMPB", 0x22, 1},
    {"IXC", 0x24, 1}, {"IXWC", 0x25, 1}, {"IXBC", 0x26, 1},
    {"JZ", 0x28, 1},  {"JNZ", 0x29, 1},  {"JC", 0x2A, 1},  {"JMP", 0x28, 1},
    {"GSUB", 0x2C, 1}, {"RSUB", 0x2D, 0},
    {"CID", 0x30, 1},                  {"COD", 0x32, 1},
    {"IN", 0x34, 1},                   {"OUT", 0x36, 1},
    {"DWPR", 0x38, 1}, {"DMP", 0x39, 1}, {"DMPR", 0x3A, 1}, {"DMPB", 0x3B, 1},
    {"DMPS", 0x3C, 1}, {"HALT", 0x3F, 0}
};

int see_OPTAB(char* opc) {
    int i;
    for (i = 0; i < sizeof(OPTAB) / sizeof(Optab); i++) {
        if (!strcmp(OPTAB[i].mnemonic, opc))
            return &OPTAB[i];
    }
    return NULL;
}

void put_list_head() {
    printf(" LNO    Loation    Label    Opcode    Operand      Object Code\n");
    printf(" ---    -------    -----    ------    -------      -----------\n");
}

void put_list() {
    int i;
    printf("%4s %.7X %-8s %-8s %-16s", LNO, LOC, LABEL, OPcode, OPerand), fflush(stdout);
    for (i = 0; i < OBJC[0]; i++)
        printf("%.2X", OBJC[i + 1]);
    printf("\n");
    OBJC[0] = 0;
}

int read_line(FILE* fp) {
    char* cp;
    static char buf[128];
    LNO = NULL, LABEL = NULL, OPcode = NULL, OPerand = NULL;

    do {
        if (!fgets(buf, sizeof(buf), fp)) return -1;
        strcpy(LBUF, buf); LBUF[strlen(LBUF) - 1] = 0;
        if (cp = strstr(buf, "//")) *cp = 0;
    } while (!(cp = strtok(buf, " \t\n\r")));

    if (isdigit(*cp)) {
        LNO = cp;
        cp = strtok(NULL, " \t\n\r");
    }
    if (strcmp(cp, "END") && strcmp(cp, "START") && !see_OPTAB(cp) && !see_DCTAB(cp)) {
        LABEL = cp;
        cp = strtok(NULL, " \t\n\r");
    }

    OPcode = cp;
    OPerand = strtok(NULL, "\t\n\r");

    return 1;
}
