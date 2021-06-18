#include "limits.h"
#include "printf_common.h"
#include "stdio.h"

struct buffer_info {
    char* buffer;
};

static int vsnprintf_cb(void* dst, const char* data, size_t amnt) {
    struct buffer_info* info = (struct buffer_info*) dst;

    for (size_t i = 0; i < amnt; i++)
        *info->buffer++ = data[i];

    return amnt;
}

int vsnprintf(char* dst, size_t n, const char* format, va_list args) {
    if (n == 0)
        return 0;

    struct buffer_info info;
    info.buffer = dst;

    int ret  = printf_common(vsnprintf_cb, &info, n - 1, format, args);
    dst[ret] = '\0';

    return ret;
}