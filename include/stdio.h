#pragma once

#include "stdarg.h"
#include "stddef.h"
#include "stdint.h"

#define EOF (-1)

struct file {
    int handle;
};
typedef struct file FILE;

extern FILE _stdin, _stdout, _stderr;

#define stdin (&_stdin)
#define stdout (&_stdout)
#define stderr (&_stderr)

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

FILE*  fopen(const char* filename, const char* mode);
size_t fread(const void* ptr, size_t size, size_t nitems, FILE* stream);
size_t fwrite(const void* ptr, size_t size, size_t nitems, FILE* stream);
int    fclose(FILE* stream);
long   fseek(FILE* stream, long offset, int mode);
long   ftell(FILE* stream);
int    fileno(FILE* stream);

int vfprintf(FILE* stream, const char* format, va_list parameters);
int printf(const char* format, ...);
int fprintf(FILE* stream, const char* format, ...);
int sprintf(char* dst, const char* format, ...);

int getchar();
int getc(FILE* stream);
int putchar(int c);
int putc(int c, FILE* stream);

void perror(const char* string);

int puts(const char* str);