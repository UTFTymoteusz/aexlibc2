#include "string.h"

#include "errno.h"
#include "stdbool.h"
#include "stddef.h"
#include "stdint.h"
#include "stdlib.h"

const char* error_names[128] = {
    [ENONE]           = "Success",
    [E2BIG]           = "Argument list too long",
    [EACCES]          = "Permission denied",
    [EADDRINUSE]      = "Address already in use",
    [EADDRNOTAVAIL]   = "Cannot assign requested address",
    [EAGAIN]          = "Try again",
    [EBADF]           = "Bad file number",
    [EBADMSG]         = "Bad message",
    [EBOTHER]         = "Cannot be bothered to implement",
    [EBUSY]           = "Device or resource busy",
    [ECANCELED]       = "Operation canceled",
    [ECHILD]          = "No child processes",
    [ECONNABORTED]    = "Software caused connection abort",
    [ECONNREFUSED]    = "Connection refused",
    [ECONNRESET]      = "Connection reset by peer",
    [EDEADLK]         = "Resource deadlock would occur",
    [EDESTADDRREQ]    = "Destination address required",
    [EDOM]            = "Mathematics argument out of domain of function",
    [EDQUOT]          = "Reserved",
    [EEXIST]          = "File exists",
    [EFAULT]          = "Bad address",
    [EFBIG]           = "File too large",
    [EHOSTUNREACH]    = "No route to host",
    [EIDRM]           = "Identifier removed",
    [EILSEQ]          = "Illegal byte sequence",
    [EINPROGRESS]     = "Operation in progress",
    [EINTR]           = "Interrupted system call",
    [EINVAL]          = "Invalid argument",
    [EIO]             = "I/O error",
    [EISCONN]         = "Transport endpoint is already connected",
    [EISDIR]          = "Is a directory",
    [ELOOP]           = "Too many levels of symbolic links",
    [EMFILE]          = "File descriptor value too large",
    [EMLINK]          = "Too many links",
    [EMSGSIZE]        = "Message too large",
    [EMULTIHOP]       = "Reserved",
    [ENAMETOOLONG]    = "Filename too long",
    [ENETDOWN]        = "Network is down",
    [ENETRESET]       = "Network dropped connection because of reset",
    [ENETUNREACH]     = "Network is unreachable",
    [ENFILE]          = "Too many files open in system",
    [ENOBUFS]         = "No buffer space available",
    [ENODATA]         = "No message is available on the STREAM head read queue",
    [ENODEV]          = "No such device",
    [ENOENT]          = "No such file or directory",
    [ENOEXEC]         = "Exec format error",
    [ENOLINK]         = "Reserved",
    [ENOMEM]          = "Out of memory",
    [ENOMSG]          = "No message of the desired type",
    [ENOPROTOOPT]     = "Protocol not available",
    [ENOSPC]          = "No space left on device",
    [ENOSR]           = "No STREAM resources",
    [ENOSTR]          = "Not a STREAM",
    [ENOSYS]          = "Not implemented",
    [ENOTBLK]         = "Block device required",
    [ENOTCONN]        = "Transport endpoint is not connected",
    [ENOTDIR]         = "Not a directory",
    [ENOTEMPTY]       = "Directory not empty",
    [ENOTRECOVERABLE] = "State not recoverable",
    [ENOTSOCK]        = "Not a socket",
    [ENOTSUP]         = "Not supported",
    [ENOTTY]          = "Iappropriate I/O control operation",
    [ENXIO]           = "No such device of address",
    [EOPNOTSUPP]      = "Operation not supported on socket",
    [EOVERFLOW]       = "Value too large to be stored in data type",
    [EOWNERDEAD]      = "Previous owner died",
    [EPERM]           = "Operation not permitted",
    [EPIPE]           = "Broken pipe",
    [EPROTO]          = "Protocol error",
    [EPROTONOSUPPORT] = "Protocol not supported",
    [EPROTOTYPE]      = "Protocol wrong type for socket",
    [ERANGE]          = "Result too large",
    [EROFS]           = "Read-only filesystem",
    [ESPIPE]          = "Invalid seek",
    [ESHUTDOWN]       = "Cannot send after transport endpoint shutdown",
    [ESOCKTNOSUPPORT] = "Socket type not supported",
    [ESRCH]           = "No such process",
    [ETIMEDOUT]       = "Connection timed out",
};

#define min(a, b) (a > b ? b : a)
#define max(a, b) (a < b ? b : a)

void reverse(char str[], int length) {
    int  start = 0;
    int  end   = length - 1;
    char c;

    while (start < end) {
        c          = str[start];
        str[start] = str[end];
        str[end]   = c;

        start++;
        end--;
    }
}

int memcmp(const void* aptr, const void* bptr, size_t size) {
    const uint8_t* a = (const uint8_t*) aptr;
    const uint8_t* b = (const uint8_t*) bptr;

    for (size_t i = 0; i < size; i++) {
        if (a[i] < b[i])
            return -1;
        else if (b[i] < a[i])
            return 1;
    }
    return 0;
}

void* memcpy(void* dstptr, const void* srcptr, size_t size) {
    uint8_t*       dst = (uint8_t*) dstptr;
    const uint8_t* src = (const uint8_t*) srcptr;

    for (size_t i = 0; i < size; i++)
        dst[i] = src[i];

    return dstptr;
}

void* memccpy(void* _dst, const void* _src, int c, size_t n) {
    uint8_t*       dst = (uint8_t*) _dst;
    const uint8_t* src = (const uint8_t*) _src;

    for (size_t i = 0; i < n; i++) {
        dst[i] = src[i];

        if (dst[i] == c)
            return &dst[i + 1];
    }

    return NULL;
}

void* mempcpy(void* dst, const void* src, size_t n) {
    memcpy(dst, src, n);
    return (void*) &((char*) dst)[n];
}

void* memmove(void* dstptr, const void* srcptr, size_t size) {
    uint8_t*       dst = (uint8_t*) dstptr;
    const uint8_t* src = (const uint8_t*) srcptr;

    if (dst < src) {
        for (size_t i = 0; i < size; i++)
            dst[i] = src[i];
    }
    else {
        for (size_t i = size; i != 0; i--)
            dst[i - 1] = src[i - 1];
    }

    return dstptr;
}

void* memset(void* bufptr, int value, size_t size) {
    uint8_t* buf = (uint8_t*) bufptr;
    for (size_t i = 0; i < size; i++)
        buf[i] = (uint8_t) value;

    return bufptr;
}

void* memchr(const void* str, int c, size_t n) {
    uint8_t* buf = (uint8_t*) str;
    for (size_t i = 0; i < n; i++)
        if (buf[i] == c)
            return (void*) &buf[i];

    return NULL;
}

char* stpcpy(char* dst, const char* src) {
    return strcpy(dst, src) + strlen(src);
}

char* strcat(char* dst, const char* src) {
    char* origin = dst;

    while (*dst != '\0')
        dst++;

    strcpy(dst, src);
    return origin;
}

int strcmp(const char* left, const char* right) {
    for (size_t i = 0;; i++) {
        if (left[i] == right[i]) {
            if (left[i] == '\0')
                return 0;
        }
        else
            return left[i] < right[i] ? -1 : 1;
    }
    return 0;
}

int strncmp(const char* left, const char* right, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (left[i] == right[i]) {
            if (left[i] == '\0')
                return 0;
        }
        else
            return left[i] < right[i] ? -1 : 1;
    }

    return 0;
}

char* strcpy(char* dst, const char* src) {
    int i = 0;

    while (src[i] != '\0') {
        dst[i] = src[i];
        i++;
    }

    dst[i] = '\0';
    return dst;
}

char* strncpy(char* dst, const char* src, size_t n) {
    size_t len = min(strlen(src), n);
    if (len == 0)
        return dst;

    memset(dst + n, '\0', n - len);
    memcpy(dst, src, n);

    return dst;
}

size_t strcspn(const char* str, const char* bongs) {
    size_t n    = 0;
    size_t cmps = strlen(bongs);

    while (str[n] != '\0') {
        for (size_t i = 0; i < cmps; i++)
            if (str[n] == bongs[i])
                return n;

        n++;
    }

    return n;
}

char* strdup(const char* str) {
    return strcpy(malloc(strlen(str) + 1), str);
}

char* strerror(int errnum) {
    if (errnum < 0 || errnum >= ETIMEDOUT)
        return (char*) "Unknown";

    return (char*) error_names[errnum];
}

int strerror_r(int errnum, char* buf, size_t n) {
    char* name = strerror(errnum);

    strncpy(buf, name, n - 1);
    buf[n - 1] = '\0';

    if (strlen(name) + 1 > n)
        return ERANGE;

    return 0;
}

size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len])
        len++;

    return len;
}

char* strpbrk(const char* str, const char* bongs) {
    size_t len = strcspn(str, bongs);
    return len ? str + len : NULL;
}

size_t strspn(const char* str, const char* bongs) {
    size_t n    = 0;
    size_t cmps = strlen(bongs);

    while (str[n] != '\0') {
        bool safe = false;

        for (size_t i = 0; i < cmps; i++)
            if (str[n] == bongs[i]) {
                safe = true;
                break;
            }

        if (!safe)
            break;

        n++;
    }

    return n;
}

char* strstr(const char* str, const char* str2) {
    size_t strl  = strlen(str);
    size_t str2l = strlen(str2);

    if (strl < str2l)
        return NULL;

    for (size_t i = 0; i < strl - str2l + 1; i++) {
        if (memcmp(str + i, str2, str2l) == 0)
            return str + i;
    }

    return NULL;
}

char* strtok(char* str, const char* delims) {
    static char* current_str;
    return strtok_r(str, delims, &current_str);
}

char* strtok_r(char* str, const char* delims, char** saveptr) {
    if (str) {
        size_t len = strspn(str, delims);
        if (len == 0)
            if (*str == '\0')
                return NULL;

        *saveptr = str + len;
    }

    size_t tok_len = strcspn(*saveptr, delims);
    if (tok_len == 0)
        return NULL;

    char* token = *saveptr;
    *saveptr += tok_len;

    size_t delim_len = strspn(*saveptr, delims);

    **saveptr = '\0';
    *saveptr += delim_len;

    return token;
}

int strcoll(const char* s1, const char* s2) {
    return strcmp(s1, s2);
}

char* strchr(const char* str, int c) {
    size_t len = strlen(str);

    for (size_t i = 0; i < len; i++)
        if (str[i] == c)
            return (char*) &str[i];

    return NULL;
}

char* strrchr(const char* str, int c) {
    size_t len = strlen(str);

    for (size_t i = len - 1; i > 0; i--)
        if (str[i] == c)
            return (char*) &str[i];

    return NULL;
}