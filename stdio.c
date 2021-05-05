#include "stdio.h"

#include "errno.h"
#include "stdlib.h"
#include "string.h"
#include "syscallids.h"
#include "unistd.h"

FILE _stdin;
FILE _stdout;
FILE _stderr;

int mode_from_str(const char* mode);

void stdio_init() {
    _stdin.handle  = 0;
    _stdout.handle = 1;
    _stderr.handle = 2;
}

FILE* fopen(const char* filename, const char* mode) {
    long ret = syscall(SYS_OPEN, filename, mode_from_str(mode));
    if (ret < 0)
        return NULL;

    FILE* file   = (FILE*) malloc(sizeof(FILE));
    file->handle = ret;

    return file;
}

size_t fread(const void* ptr, size_t size, size_t nitems, FILE* stream) {
    return syscall(SYS_READ, stream->handle, ptr, size * nitems);
}

size_t fwrite(const void* ptr, size_t size, size_t nitems, FILE* stream) {
    return syscall(SYS_WRITE, stream->handle, ptr, size * nitems);
}

int fclose(FILE* stream) {
    int ret = syscall(SYS_CLOSE, stream->handle);
    free(stream);

    return ret;
}

long fseek(FILE* stream, long offset, int mode) {
    return syscall(SYS_SEEK, stream->handle, offset, mode);
}

long ftell(FILE* stream) {
    return syscall(SYS_SEEK, stream->handle, 0, 1);
}

int fileno(FILE* stream) {
    return stream->handle;
}

int getchar() {
    char c;
    fread(&c, 1, 1, stdin);
    return c;
}

int getc(FILE* stream) {
    char c;
    fread(&c, 1, 1, stream);
    return c;
}

int putchar(int i) {
    char c = i;
    return fwrite(&c, 1, 1, stdout);
}

int putc(int i, FILE* stream) {
    char c = i;
    return fwrite(&c, 1, 1, stream);
}

int mode_from_str(const char* mode) {
    if (strcmp(mode, "r") == 0)
        return 1;

    if (strcmp(mode, "w") == 0)
        return 2;

    if (mode[1] == '+')
        return 1 | 2;

    return 0;
}

void perror(const char* string) {
    int error = errno;
    printf("%s: %s\n", string, strerror(error));
}

// TODO: make this less stupid
int puts(const char* str) {
    printf("%s\n", str);
    return strlen(str);
}