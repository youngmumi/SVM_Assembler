#define MAX_DLEN 8
#define MAX_DCTAB (sizeof(DCTAB)/sizeof(struct dctab))

typedef struct dctab {
	char directive[MAX_DLEN];
	char type;

#define DC_CNST 0
#define DC_RESV 1
	char unit;
#define DC_DW 4
#define DC_WD 2
#define DC_BT 1
}Dctab;

Dctab DCTAB[] = {
	"DD", DC_CNST, DC_DW,	"DW", DC_CNST, DC_DW,	"DB", DC_CNST, DC_BT,
	"RD", DC_RESV, DC_DW,	"RW", DC_RESV, DC_WD,	"RB", DC_RESV, DC_BT
};

Dctab* see_DCTAB(char* dcc) {
	int i;

	for (i = 0; i < MAX_DCTAB; i++) {
		if (!strcmp(DCTAB[i].directive, dcc))
			return (&DCTAB[i]);
	}
	return NULL;
}
