#pragma once

#include "stddef.h"

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define RAND_MAX 32767

int atexit(void (*func)());

void exit(int status);
void abort();

int  rand();
void srand(unsigned int seed);

void* malloc(size_t size);
void* calloc(size_t nmeb, size_t size);
void* realloc(void* space, size_t size);
void  free(void* ptr);

char* getenv(const char* name);

char* itoa(long, char*, int);
int   atoi(const char*);
long  atol(const char*);