#include "limits.h"
#include "printf_common.h"
#include "stdio.h"

int vfprintf_cb(void* dst, const char* data, size_t amnt) {
    fwrite(data, amnt, 1, (FILE*) dst);
    return amnt;
}

int vfprintf(FILE* stream, const char* format, va_list args) {
    return printf_common(vfprintf_cb, stream, 65536, format, args);
}