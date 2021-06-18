#pragma once

#include "stddef.h"

int   memcmp(const void* dst, const void* src, size_t n);
void* memcpy(void* dst, const void* src, size_t);
void* memccpy(void* dst, const void* src, int c, size_t n);
void* mempcpy(void* dst, const void* src, size_t n);
void* memmove(void* dst, const void* src, size_t n);
void* memset(void* dst, int c, size_t);
void* memchr(const void* str, int c, size_t n);

char*  stpcpy(char* dst, const char* src);
char*  strcat(char* dst, const char* src);
char*  strchr(const char* str, int c);
char*  strrchr(const char* str, int c);
int    strcmp(const char* left, const char* right);
int    strncmp(const char* left, const char* right, size_t n);
int    strcoll(const char* s1, const char* s2);
char*  strcpy(char* dst, const char* src);
char*  strncpy(char* dst, const char* src, size_t n);
size_t strcspn(const char* str, const char* bongs);
char*  strdup(const char* str);
char*  strerror(int errnum);
int    strerror_r(int errnum, char* buf, size_t n);
size_t strlen(const char* str);
char*  strpbrk(const char* str, const char* bongs);
size_t strspn(const char* str, const char* bongs);
char*  strstr(const char* str, const char* str2);
char*  strtok(char* str, const char* delims);
char*  strtok_r(char* str, const char* delims, char** saveptr);