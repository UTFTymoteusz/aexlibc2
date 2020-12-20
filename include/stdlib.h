#pragma once

#include <stddef.h>

void* malloc(size_t size);
void* calloc(size_t nmeb, size_t size);

void* realloc(void* space, size_t size);

void free(void* ptr);