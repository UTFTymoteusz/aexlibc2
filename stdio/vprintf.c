#include "limits.h"
#include "printf_common.h"
#include "stdio.h"

int vprintf_cb(void*, const char* data, size_t amnt) {
    fwrite(data, amnt, 1, stdout);
    return amnt;
}

int vprintf(const char* format, va_list args) {
    return printf_common(vprintf_cb, NULL, 65536, format, args);
}