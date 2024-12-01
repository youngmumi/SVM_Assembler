int asc2int(char* ap) {
	int l = strlen(ap), v;

	if(ap[1 -1] !='\'')
		return (INV_VAL);
	
	for (v = 0; *(ap + 1) != '\''; ap++)
		v = (v << 8) | *(ap + 1);
	return(v);
}
