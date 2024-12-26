#include "symtab.h"
#include "main.h"

int asc2int(char* ap) {
    int result = 0;

    if (ap[0] != '\'') 
        return INV_VAL;

    for (ap++; *ap != '\'' && *ap != '\0'; ap++) {
        result = (result << 8) | *ap; // ASCII 값 누적
    }

    if (*ap != '\'') 
        return INV_VAL;

    return result;
}

