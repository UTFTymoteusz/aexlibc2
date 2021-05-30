#pragma once

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

int printf_common(int (*write_cb)(void* dst, const char* data, size_t amnt), void* dst,
                  size_t limit, const char* format, va_list args);