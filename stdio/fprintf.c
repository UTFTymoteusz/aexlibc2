#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int fprintf(FILE* stream, const char* format, ...) {
    va_list args;
    va_start(args, format);

    int ret = vfprintf(stream, format, args);

    va_end(args);
    return ret;
}