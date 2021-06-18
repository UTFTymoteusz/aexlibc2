#pragma once

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define EOF (-1)

struct file {
    int  handle;
    int  unchar;
    bool eof;
};
typedef struct file FILE;

typedef long fpos_t;

extern FILE _stdin, _stdout, _stderr;

#define stdin (&_stdin)
#define stdout (&_stdout)
#define stderr (&_stderr)

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define L_tmpnam 64

int   rename(const char* old, const char* new);
int   remove(const char* filename);
char* tmpnam(char* buffer);
FILE* tmpfile();

FILE*  fopen(const char* filename, const char* mode);
size_t fread(void* ptr, size_t size, size_t nitems, FILE* stream);
size_t fwrite(const void* ptr, size_t size, size_t nitems, FILE* stream);
int    fclose(FILE* stream);
int    fileno(FILE* stream);
int    fflush(FILE* stream);

int fprintf(FILE* stream, const char* format, ...);
int printf(const char* format, ...);
int snprintf(char* dst, size_t n, const char* format, ...);
int sprintf(char* dst, const char* format, ...);
int vfprintf(FILE* stream, const char* format, va_list parameters);
int vprintf(const char* format, va_list parameters);

int   fgetc(FILE* stream);
char* fgets(char* str, int num, FILE* stream);
int   fputc(int c, FILE* stream);
int   fputs(const char* str, FILE* stream);
int   getc(FILE* stream);
int   getchar();
char* gets(char* str);
int   putc(int c, FILE* stream);
int   putchar(int c);
int   puts(const char* str);
int   ungetc(int c, FILE* stream);

int  fseek(FILE* stream, long offset, int mode);
long ftell(FILE* stream);
int  fgetpos(FILE* stream, fpos_t* pos);
int  fsetpos(FILE* stream, const fpos_t* pos);
void rewind(FILE* stream);

void clearerr(FILE* stream);
int  feof(FILE* stream);
void perror(const char* string);