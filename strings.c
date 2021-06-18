#include "strings.h"

#include "ctype.h"
#include "string.h"

int bcmp(const void* a, const void* b, size_t n) {
    return strncmp((const char*) a, (const char*) b, n);
}

void bcopy(const void* src, void* dst, size_t n) {
    memmove(dst, src, n);
}

void bzero(void* str, size_t n) {
    memset(str, '\0', n);
}

void explicit_bzero(void* str, size_t n) {
    memset(str, '\0', n);
}

int ffs(int val) {
    for (int i = 1; i <= sizeof(val) * 8; i++)
        if (val & i)
            return i;

    return 0;
}

int ffsl(long val) {
    for (int i = 1; i <= sizeof(val) * 8; i++)
        if (val & i)
            return i;

    return 0;
}

int ffsll(long long val) {
    for (int i = 1; i <= sizeof(val) * 8; i++)
        if (val & i)
            return i;

    return 0;
}

char* index(const char* str, int c) {
    return strchr(str, c);
}

char* rindex(const char* str, int c) {
    return strrchr(str, c);
}

int strcasecmp(const char* a, const char* b) {
    for (size_t i = 0;; i++) {
        if (tolower(a[i]) == tolower(b[i])) {
            if (a[i] == '\0')
                return 0;
        }
        else
            return tolower(a[i]) < tolower(b[i]) ? -1 : 1;
    }
    return 0;
}

int strncasecmp(const char* a, const char* b, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (tolower(a[i]) == tolower(b[i])) {
            if (a[i] == '\0')
                return 0;
        }
        else
            return tolower(a[i]) < tolower(b[i]) ? -1 : 1;
    }
    return 0;
}