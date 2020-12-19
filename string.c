#include "string.h"

#include "errno.h"
#include "stdbool.h"
#include "stddef.h"
#include "stdint.h"

const char* error_names[128] = {
    [ENONE]           = "None",
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

char* itoa(long value, char* str, int base) {
    char* rc;
    char* ptr;
    char* low;
    // Check for supported base.
    if (base < 2 || base > 36) {
        *str = '\0';
        return str;
    }
    rc = ptr = str;
    // Set '-' for negative decimals.
    if (value < 0 && base == 10)
        *ptr++ = '-';

    // Remember where the numbers start.
    low = ptr;
    // The actual conversion.
    do {
        // Modulo is negative for negative value. This trick makes abs() unnecessary.
        *ptr++ =
            "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 +
                                                                                      value % base];
        value /= base;
    } while (value);
    // Terminating the string.
    *ptr-- = '\0';
    // Invert the numbers.
    while (low < ptr) {
        char tmp = *low;

        *low++ = *ptr;
        *ptr-- = tmp;
    }
    return rc;
}

long atoi(char* str) {
    int res  = 0; // Initialize result
    int sign = 1; // Initialize sign as positive
    int i    = 0; // Initialize index of first digit

    // If number is negative, then update sign
    if (str[0] == '-') {
        sign = -1;
        ++i; // Also update index of first digit
    }

    // Iterate through all digits and update the result
    for (; str[i] != '\0'; ++i)
        res = res * 10 + str[i] - '0';

    // Return result with sign
    return sign * res;
}

int memcmp(const void* aptr, const void* bptr, size_t size) {
    const unsigned char* a = (const unsigned char*) aptr;
    const unsigned char* b = (const unsigned char*) bptr;

    for (size_t i = 0; i < size; i++) {
        if (a[i] < b[i])
            return -1;
        else if (b[i] < a[i])
            return 1;
    }
    return 0;
}

void* memcpy(void* dstptr, const void* srcptr, size_t size) {
    unsigned char*       dst = (unsigned char*) dstptr;
    const unsigned char* src = (const unsigned char*) srcptr;

    for (size_t i = 0; i < size; i++)
        dst[i] = src[i];

    return dstptr;
}

void* memmove(void* dstptr, const void* srcptr, size_t size) {
    unsigned char*       dst = (unsigned char*) dstptr;
    const unsigned char* src = (const unsigned char*) srcptr;

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
    unsigned char* buf = (unsigned char*) bufptr;
    for (size_t i = 0; i < size; i++)
        buf[i] = (unsigned char) value;

    return bufptr;
}

int strcmp(const char* left, const char* right) {
    int i = 0;

    while (true) {
        if (left[i] == right[i]) {
            if (left[i] == '\0')
                return 0;
        }
        else
            return left[i] < right[i] ? -1 : 1;

        ++i;
    }
    return 0;
}

char* strcpy(char* dst, const char* src) {
    int i = 0;

    while (src[i] != '\0') {
        dst[i] = src[i];
        ++i;
    }
    dst[i] = '\0';
    return dst;
}

size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len])
        len++;

    return len;
}

char* strerror(int errnum) {
    if (errnum < 0 || errnum >= ETIMEDOUT)
        return (char*) "Unknown";

    return (char*) error_names[errnum];
}