#pragma once

#include "stddef.h"

int   memcmp(const void*, const void*, size_t);
void* memcpy(void*, const void*, size_t);
void* memmove(void*, const void*, size_t);
void* memset(void*, int, size_t);

int    strcmp(const char* left, const char* right);
char*  strcpy(char* dst, const char* src);
size_t strlen(const char* str);

char* strerror(int errnum);
int   strcoll(const char* s1, const char* s2);