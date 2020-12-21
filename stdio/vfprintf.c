#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static bool print(const char* data, size_t length, FILE* stream) {
    const uint8_t* bytes = (const uint8_t*) data;

    fwrite(data, length, 1, stream);

    return true;
}

int vfprintf(FILE* stream, const char* format, va_list args) {
    char itoa_buffer[128];
    int  written = 0;

    if (*format == '\0')
        return 0;

    do {
        char c = *format;

        if (c == '%') {
            c = *++format;

            switch (c) {
            case 's': {
                char* str = va_arg(args, char*);
                int   len = strlen(str);

                print(str, len, stream);

                written += len;
            } break;
            case 'c': {
                char c = (char) va_arg(args, int);

                print(&c, 1, stream);

                written++;
            } break;
            case 'i': {
                int i = va_arg(args, int);
                itoa(i, itoa_buffer, 10);

                print(itoa_buffer, strlen(itoa_buffer), stream);
                written += strlen(itoa_buffer);
            } break;
            case 'p': {
                size_t i = va_arg(args, size_t);
                itoa(i, itoa_buffer, 16);

                print(itoa_buffer, strlen(itoa_buffer), stream);
                written += strlen(itoa_buffer);
            } break;
            default:
                break;
            }

            continue;
        }

        print(format, 1, stream);
    } while (*++format != '\0');

    return written;
}