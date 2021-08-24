#include "stdio.h"

#include "errno.h"
#include "fcntl.h"
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

int rename(const char* old, const char* new) {
    return syscall(SYS_RENAME, old, new);
}

int remove(const char* filename) {
    return syscall(SYS_UNLINK, filename);
}

char* tmpnam(char* buffer) {
    static char global_buffer[L_tmpnam];
    static int  counter;

    if (!buffer)
        buffer = global_buffer;

    snprintf(buffer, L_tmpnam, "/tmp/tmp.%i.%i", getpid(), counter);
    return global_buffer;
}

FILE* tmpfile() {
    char filename[L_tmpnam];
    return fopen(tmpnam(filename), "T");
}

FILE* fopen(const char* filename, const char* mode) {
    long ret = syscall(SYS_OPEN, filename, mode_from_str(mode));
    if (ret < 0)
        return NULL;

    FILE* file = (FILE*) malloc(sizeof(FILE));

    file->handle = ret;
    file->unchar = -1;
    file->eof    = false;

    return file;
}

size_t fread(void* ptr, size_t size, size_t nitems, FILE* stream) {
    if (size * nitems > 0 && stream->unchar != -1) {
        *((char*) ptr) = stream->unchar;
        ptr            = (void*) (((char*) ptr) + 1);
    }

    size_t bytes = syscall(SYS_READ, stream->handle, ptr, size * nitems);
    if (bytes < size)
        stream->eof = true;

    return bytes / size;
}

size_t fwrite(const void* ptr, size_t size, size_t nitems, FILE* stream) {
    size_t bytes = syscall(SYS_WRITE, stream->handle, ptr, size * nitems);
    if (bytes < size)
        stream->eof = true;

    return bytes / size;
}

int fclose(FILE* stream) {
    int ret = syscall(SYS_CLOSE, stream->handle);
    free(stream);

    return ret;
}

int fseek(FILE* stream, long offset, int mode) {
    stream->unchar = -1;
    stream->eof    = false;
    return syscall(SYS_SEEK, stream->handle, offset, mode) >= 0 ? 0 : -1;
}

long ftell(FILE* stream) {
    return syscall(SYS_SEEK, stream->handle, 0, 1) - (stream->unchar != -1 ? 1 : 0);
}

int fflush(FILE* file) {
    return 0;
}

int feof(FILE* stream) {
    return stream->eof;
}

void clearerr(FILE* stream) {
    stream->eof = false;
}

void rewind(FILE* stream) {
    stream->eof    = false;
    stream->unchar = -1;

    fseek(stream, 0, SEEK_SET);
}

int ungetc(int c, FILE* stream) {
    if (stream->unchar != -1 || c == EOF) {
        errno = ERANGE;
        return -1;
    }

    stream->unchar = c;
    return 0;
}

int fgetpos(FILE* stream, fpos_t* pos) {
    long _pos = ftell(stream);
    if (_pos < 0)
        return _pos;

    *pos = _pos;
    return 0;
}

int fsetpos(FILE* stream, const fpos_t* pos) {
    return fseek(stream, *pos, SEEK_SET);
}

int fileno(FILE* stream) {
    return stream->handle;
}

int getc(FILE* stream) {
    return fgetc(stream);
}

int getchar() {
    return fgetc(stdin);
}

char* gets(char* str) {
    char* original = str;

    while (true) {
        char c = fgetc(stdin);
        switch (c) {
        case '\n':
        case EOF:
            return original;
        default:
            *str = c;
            str++;
            break;
        }
    }

    return original;
}

int fgetc(FILE* stream) {
    char c;

    if (fread(&c, 1, 1, stream) == 0)
        return EOF;

    return c;
}

char* fgets(char* str, int num, FILE* stream) {
    char* original = str;

    for (int i = 0; i < num - 1; i++) {
        char c = fgetc(stream);
        switch (c) {
        case '\n':
            *str = '\n';
            str++;
            return original;
        case EOF:
            return original;
        default:
            *str = c;
            str++;
            break;
        }
    }

    return original;
}

int putchar(int i) {
    char c = i;
    return fwrite(&c, 1, 1, stdout) ? 0 : -1;
}

int putc(int v, FILE* stream) {
    char c = v;
    return fwrite(&c, 1, 1, stream) ? 0 : -1;
}

int fputc(int v, FILE* stream) {
    char c = v;
    return fwrite(&c, 1, 1, stream) ? 0 : -1;
}

int fputs(const char* str, FILE* stream) {
    return fwrite(str, strlen(str), 1, stream) ? 0 : -1;
}

int mode_from_str(const char* mode) {
    if (strcmp(mode, "r") == 0)
        return O_RDONLY;

    if (strcmp(mode, "r+") == 0)
        return O_RDWR;

    if (strcmp(mode, "w") == 0)
        return O_WRONLY | O_CREAT | O_TRUNC;

    if (strcmp(mode, "w+") == 0)
        return O_RDWR | O_CREAT | O_TRUNC;

    if (strcmp(mode, "a") == 0)
        return O_WRONLY | O_CREAT | O_APPEND;

    if (strcmp(mode, "a+") == 0)
        return O_RDWR | O_CREAT | O_APPEND;

    if (strcmp(mode, "T") == 0)
        return O_RDWR | O_CREAT | O_TRUNC | O_EXCL;

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