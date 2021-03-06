#include "stdlib.h"

char* itoa(long value, char* str, int base) {
    char* rc;
    char* ptr;
    char* low;

    if (base < 2 || base > 36) {
        *str = '\0';
        return str;
    }

    rc = ptr = str;
    if (value < 0 && base == 10)
        *ptr++ = '-';

    low = ptr;
    do {
        *ptr++ =
            "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 +
                                                                                      value % base];
        value /= base;
    } while (value);

    *ptr-- = '\0';
    while (low < ptr) {
        char tmp = *low;

        *low++ = *ptr;
        *ptr-- = tmp;
    }
    return rc;
}

char* utoa(unsigned long value, char* str, int base) {
    char* rc;
    char* ptr;
    char* low;

    if (base < 2 || base > 36) {
        *str = '\0';
        return str;
    }

    rc = ptr = str;

    low = ptr;
    do {
        *ptr++ =
            "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 +
                                                                                      value % base];
        value /= base;
    } while (value);

    *ptr-- = '\0';
    while (low < ptr) {
        char tmp = *low;

        *low++ = *ptr;
        *ptr-- = tmp;
    }
    return rc;
}

int atoi(const char* str) {
    int res  = 0;
    int sign = 1;
    int i    = 0;

    if (str[0] == '-') {
        sign = -1;
        i++;
    }

    for (; str[i] != '\0'; ++i)
        res = res * 10 + str[i] - '0';

    return sign * res;
}

long atol(const char* str) {
    long res  = 0;
    int  sign = 1;
    int  i    = 0;

    if (str[0] == '-') {
        sign = -1;
        i++;
    }

    for (; str[i] != '\0'; ++i)
        res = res * 10 + str[i] - '0';

    return sign * res;
}