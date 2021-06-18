#pragma once

#include "stddef.h"

int   bcmp(const void* a, const void* b, size_t n);
void  bcopy(const void* src, void* dst, size_t n);
void  bzero(void* str, size_t n);
void  explicit_bzero(void* str, size_t n);
int   ffs(int val);
int   ffsl(long val);
int   ffsll(long long val);
char* index(const char* str, int c);
char* rindex(const char* str, int c);
int   strcasecmp(const char* a, const char* b);
int   strncasecmp(const char* a, const char* b, size_t n);