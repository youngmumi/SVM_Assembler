#include "main.h"

void put_list_head() {
	printf(" LNO	Loation		Label	Opcode	Operand		Object Code\n");
	printf(" ---	-------		-----	------	-------		-----------\n");
}

void put_list() {
	int i;
	printf("%4s %.7X %-8s %-8s %-16s", LNO, LOC, LABEL, OPcode, OPerand), fflush(stdout);

	for (i = 0; i < OBJC[0]; i++)
		printf("%.2X", OBJC[i + 1]);
	printf("\n");
	OBJC[0] = 0;
}
