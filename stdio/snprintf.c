#include "limits.h"
#include "printf_common.h"
#include "stdio.h"

struct buffer_info {
    char* buffer;
};

static int sprintf_cb(void* dst, const char* data, size_t amnt) {
    struct buffer_info* info = (struct buffer_info*) dst;

    for (size_t i = 0; i < amnt; i++)
        *info->buffer++ = data[i];

    return amnt;
}

int snprintf(char* dst, size_t n, const char* format, ...) {
    if (n == 0)
        return 0;

    va_list args;
    va_start(args, format);

    struct buffer_info info;
    info.buffer = dst;

    int ret  = printf_common(sprintf_cb, &info, n - 1, format, args);
    dst[ret] = '\0';

    va_end(args);
    return ret;
}