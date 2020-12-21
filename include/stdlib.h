#pragma once

#include <stddef.h>

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

void* malloc(size_t size);
void* calloc(size_t nmeb, size_t size);

void* realloc(void* space, size_t size);

void free(void* ptr);