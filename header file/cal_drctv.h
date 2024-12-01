#define MAX_DNUM 8

int cal_dc_oprnd(char* oprnd, int unit, unsigned char obj[]) {
    char buf[128], * exp;
    unsigned char* op = obj + 1; // obj 배열의 시작 주소 + 1
    int n = 0, v, len = 0;

    strcpy(buf, oprnd);
    exp = strtok(buf, ",");

    do {
        if (++n > MAX_DNUM) {
            fprintf(stderr, "%s ---> Operand '%s' is not valid ...\n", LBUF, oprnd);
            exit(11);
        }
        v = cal_one_expr(exp);
        switch (unit) {
        case 4:
            *op = (v >> 24) & 0xFF; op++; len++;
            *op = (v >> 16) & 0xFF; op++; len++;
        case 2:
            *op = (v >> 8) & 0xFF; op++; len++;
        case 1:
            *op = v & 0xFF; op++; len++;
            break; // 각 case에 break 추가
        default:
            fprintf(stderr, "Invalid unit size: %d\n", unit);
            exit(12);
        }
    } while ((exp = strtok(NULL, ",")));

    obj[0] = len; // 첫 번째 바이트에 길이 저장

    return len;
}

int cal_dc_oprnd_string(char* oprnd, unsigned char obj[]) {
    int i;

    for (i = 1; oprnd[i] && oprnd[i] != '\'' && i <= MAX_DNUM; i++) {
        obj[i] = oprnd[i];
    }
    if (oprnd[i] != '\'' || i > MAX_DNUM) {
        fprintf(stderr, "%s ---> Operand '%s' is not valid ...\n", LBUF, oprnd);
        exit(11);
    }
    obj[i] = '\0'; // 문자열 종료
    obj[0] = i;    // 첫 번째 바이트에 길이 저장

    return i;
}
