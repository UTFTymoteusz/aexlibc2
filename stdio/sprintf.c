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

int sprintf(char* dst, const char* format, ...) {
    va_list args;
    va_start(args, format);

    struct buffer_info info;
    info.buffer = dst;

    int ret  = printf_common(sprintf_cb, &info, 65536, format, args);
    dst[ret] = '\0';

    va_end(args);
    return ret;
}