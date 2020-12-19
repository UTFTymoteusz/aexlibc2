#include "stdio.h"

#include "errno.h"
#include "string.h"
#include "syscallids.h"
#include "unistd.h"

FILE* _stdin  = (FILE*) 0;
FILE* _stdout = (FILE*) 1;
FILE* _stderr = (FILE*) 2;

int mode_from_str(const char* mode);

FILE* fopen(const char* filename, const char* mode) {
    long ret = syscall(SYS_OPEN, filename, mode_from_str(mode));
    if (ret < 0)
        return NULL;

    return (FILE*) ret;
}

size_t fread(const void* ptr, size_t size, size_t nitems, FILE* stream) {
    return syscall(SYS_READ, (long) stream, ptr, size * nitems);
}

size_t fwrite(const void* ptr, size_t size, size_t nitems, FILE* stream) {
    return syscall(SYS_WRITE, (long) stream, ptr, size * nitems);
}

int fclose(FILE* stream) {
    return syscall(SYS_CLOSE, (long) stream);
}

int fseek(FILE* stream, long offset, int mode) {
    switch (mode) {
    case 0:
        return syscall(SYS_SEEK, (long) stream, offset);
    case 1:
    case 2:
        // unimplemented
        break;
    }

    return 0;
}

int fileno(FILE* stream) {
    return (int) (size_t) stream;
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
    if (strcmp(mode, "r"))
        return 1;

    if (strcmp(mode, "w"))
        return 2;

    if (mode[1] == '+')
        return 1 | 2;

    return 0;
}

void perror(const char* string) {
    int error = errno;
    printf("%s: %s\n", string, strerror(error));
}

// make this less stupid later
int puts(const char* str) {
    printf("%s\n", str);
    return strlen(str);
}