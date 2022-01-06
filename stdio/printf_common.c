#include "printf_common.h"

#include "ctype.h"
#include "limits.h"
#include "stdarg.h"
#include "stdbool.h"
#include "stddef.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

enum printf_size {
    SIZE_CHAR     = 0,
    SIZE_SHORT    = 1,
    SIZE_NORMAL   = 2,
    SIZE_LONG     = 3,
    SIZE_LONGLONG = 4,
};
typedef enum printf_size printf_size_t;

struct printf_type {
    char        c;
    const char* prefix;
    void (*callback)(char buffer[128], printf_size_t size, bool force_sign, va_list args);
};
typedef struct printf_type printf_type_t;

void printf_int(char buffer[128], printf_size_t size, bool force_sign, va_list args) {
    switch (size) {
    case SIZE_CHAR: {
        char i = va_arg(args, int);
        itoa(i, buffer, 10);
    } break;
    case SIZE_SHORT: {
        short i = va_arg(args, int);

        itoa(i, buffer, 10);
    } break;
    case SIZE_NORMAL: {
        int i = va_arg(args, int);
        itoa(i, buffer, 10);
    } break;
    case SIZE_LONG: {
        long i = va_arg(args, long);
        itoa(i, buffer, 10);
    } break;
    case SIZE_LONGLONG: {
        long long i = va_arg(args, long);
        itoa(i, buffer, 10);
    } break;
    }

    if (force_sign && buffer[0] != '-') {
        memmove(buffer + 1, buffer, 127);
        buffer[0] = '+';
    }
}

void printf_uint(char buffer[128], printf_size_t size, bool force_sign, va_list args) {
    switch (size) {
    case SIZE_CHAR: {
        unsigned char i = va_arg(args, unsigned int);
        utoa(i, buffer, 10);
    } break;
    case SIZE_SHORT: {
        unsigned short i = va_arg(args, unsigned int);
        utoa(i, buffer, 10);
    } break;
    case SIZE_NORMAL: {
        unsigned int i = va_arg(args, unsigned int);
        utoa(i, buffer, 10);
    } break;
    case SIZE_LONG: {
        unsigned long i = va_arg(args, unsigned long);
        utoa(i, buffer, 10);
    } break;
    case SIZE_LONGLONG: {
        unsigned long long i = va_arg(args, unsigned long long);
        utoa(i, buffer, 10);
    } break;
    }
}

void printf_oct(char buffer[128], printf_size_t size, bool force_sign, va_list args) {
    switch (size) {
    case SIZE_CHAR: {
        unsigned char i = va_arg(args, unsigned int);
        utoa(i, buffer, 8);
    } break;
    case SIZE_SHORT: {
        unsigned short i = va_arg(args, unsigned int);
        utoa(i, buffer, 8);
    } break;
    case SIZE_NORMAL: {
        unsigned int i = va_arg(args, unsigned int);
        utoa(i, buffer, 8);
    } break;
    case SIZE_LONG: {
        unsigned long i = va_arg(args, unsigned long);
        utoa(i, buffer, 8);
    } break;
    case SIZE_LONGLONG: {
        unsigned long long i = va_arg(args, unsigned long long);
        utoa(i, buffer, 8);
    } break;
    }
}

void printf_hex(char buffer[128], printf_size_t size, bool force_sign, va_list args) {
    switch (size) {
    case SIZE_CHAR: {
        unsigned char i = va_arg(args, unsigned int);
        utoa(i, buffer, 16);
    } break;
    case SIZE_SHORT: {
        unsigned short i = va_arg(args, unsigned int);
        utoa(i, buffer, 16);
    } break;
    case SIZE_NORMAL: {
        unsigned int i = va_arg(args, unsigned int);
        utoa(i, buffer, 16);
    } break;
    case SIZE_LONG: {
        unsigned long i = va_arg(args, unsigned long);
        utoa(i, buffer, 16);
    } break;
    case SIZE_LONGLONG: {
        unsigned long long i = va_arg(args, unsigned long long);
        utoa(i, buffer, 16);
    } break;
    }
}

void printf_hex_upper(char buffer[128], printf_size_t size, bool force_sign, va_list args) {
    printf_hex(buffer, size, force_sign, args);

    while (*buffer != '\0') {
        *buffer = _toupper(*buffer);
        buffer++;
    }
}

void printf_char(char buffer[128], printf_size_t size, bool force_sign, va_list args) {
    buffer[0] = va_arg(args, int);
    buffer[1] = '\0';
}

void printf_pointer(char buffer[128], printf_size_t size, bool force_sign, va_list args) {
    buffer[0] = '0';
    buffer[1] = 'x';
    buffer += 2;

    unsigned long i = va_arg(args, unsigned long);
    utoa(i, buffer, 16);
}

printf_type_t printf_types[] = {
    {'d', "", printf_int},  {'i', "", printf_int},       {'u', "", printf_uint},
    {'o', "0", printf_oct}, {'x', "0x", printf_hex},     {'X', "0X", printf_hex_upper},
    {'c', "", printf_char}, {'p', "0x", printf_pointer}, {'%', "", NULL},
};

static int print(int (*write_cb)(void* dst, const char* data, size_t amnt), void* dst, size_t left,
                 const char* data, const char* prefix, char pad_char, size_t pad_len,
                 int pad_side) {
    size_t prefix_len = prefix ? strlen(prefix) : 0;
    size_t data_len   = strlen(data);
    int    written    = 0;

    pad_len -= min(prefix_len + data_len, pad_len);

    if (pad_side == -1 && pad_char == ' ') {
        if (pad_len > left)
            pad_len = left;

        for (size_t i = 0; i < pad_len; i++)
            write_cb(dst, &pad_char, 1);

        written += pad_len;
        left -= pad_len;
    }

    if (prefix) {
        if (prefix_len > left)
            prefix_len = left;

        write_cb(dst, prefix, prefix_len);

        written += prefix_len;
        left -= prefix_len;
    }

    if (pad_side == -1 && pad_char != ' ') {
        if (pad_len > left)
            pad_len = left;

        for (size_t i = 0; i < pad_len; i++)
            write_cb(dst, &pad_char, 1);

        written += pad_len;
        left -= pad_len;
    }

    if (data_len > left)
        data_len = left;

    write_cb(dst, data, data_len);

    written += data_len;
    left -= data_len;

    if (pad_side == 1) {
        if (pad_len > left)
            pad_len = left;

        for (size_t i = 0; i < pad_len; i++)
            write_cb(dst, &pad_char, 1);

        written += pad_len;
        left -= pad_len;
    }

    return written;
}

int printf_common(int (*write_cb)(void* dst, const char* data, size_t amnt), void* dst,
                  size_t limit, const char* format, va_list args) {
    char buffer[128];
    int  written = 0;
    char c;

    while ((c = *format++) != '\0') {
        if (c == '%') {
            printf_size_t size       = SIZE_NORMAL;
            bool          prefix     = false;
            bool          force_sign = false;
            char          pad_char   = ' ';
            size_t        pad_len    = 0;
            int           pad_side   = -1;

            while (true) {
                c = *format++;

                switch (c) {
                case 'h':
                    if (size == SIZE_SHORT) {
                        size = SIZE_CHAR;
                        continue;
                    }

                    size = SIZE_SHORT;
                    continue;
                case 'l':
                    if (size == SIZE_LONG) {
                        size = SIZE_LONGLONG;
                        continue;
                    }

                    size = SIZE_LONG;
                    continue;
                case '#':
                    prefix = true;
                    continue;
                case '0':
                    pad_char = '0';
                    continue;
                case '-':
                    pad_side = 1;
                    continue;
                case '+':
                    force_sign = true;
                    continue;
                }

                break;
            }

            if (c >= '1' && c <= '9') {
                int ptr = 0;

                while (c >= '0' && c <= '9') {
                    buffer[ptr] = c;
                    c           = *format++;
                    ptr++;
                }

                buffer[ptr] = '\0';
                pad_len     = atoi(buffer);
            }
            else if (c == '*') {
                pad_len = va_arg(args, int);
            }

            if (c == 's') {
                char* str = va_arg(args, char*);
                if (!str)
                    str = "(null)";

                int amnt = print(write_cb, dst, limit, str, NULL, pad_char, pad_len, pad_side);

                written += amnt;
                limit -= amnt;

                continue;
            }
            else if (c == 'n') {
                int* ptr = va_arg(args, int*);
                *ptr     = written;

                continue;
            }
            else if (c == '%') {
                buffer[0] = '%';
                buffer[1] = '\0';

                int amnt = print(write_cb, dst, limit, buffer, NULL, pad_char, pad_len, pad_side);

                written += amnt;
                limit -= amnt;

                continue;
            }

            for (int i = 0; printf_types[i].c != '%'; i++) {
                if (printf_types[i].c != c)
                    continue;

                printf_types[i].callback(buffer, size, force_sign, args);
                int amnt =
                    print(write_cb, dst, limit, buffer, prefix ? printf_types[i].prefix : NULL,
                          pad_char, pad_len, pad_side);

                written += amnt;
                limit -= amnt;

                break;
            }

            continue;
        }

        if (limit > 0) {
            write_cb(dst, &c, 1);
            written++;
            limit--;
        }
    }

    return written;
}