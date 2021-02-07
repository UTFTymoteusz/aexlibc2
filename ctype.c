#include "ctype.h"

#define inrange(num, min, max) ((num >= min) && (num <= max))

int isalnum(int c) {
    return isalpha(c) || isdigit(c);
}

int isalpha(int c) {
    return inrange(c, 'A', 'Z') || inrange(c, 'a', 'z');
}

int isblank(int c) {
    return (c == ' ') || (c == '\t');
}

int iscntrl(int c) {
    return (c == '\0') || inrange(c, '\a', '\r') || inrange(c, 26, 27);
}

int isdigit(int c) {
    return inrange(c, '0', '9');
}

int isgraph(int c) {
    return c > ' ';
}

int islower(int c) {
    return inrange(c, 'a', 'z');
}

int isprint(int c) {
    return c >= ' ';
}

int ispunct(int c) {
    return isprint(c) && !(isspace(c) || isalnum(c));
}

int isspace(int c) {
    return (c == ' ') || (c == '\f') || (c == '\n') || (c == '\r') || (c == '\t') || (c == '\v');
}

int isupper(int c) {
    return inrange(c, 'A', 'Z');
}

int isxdigit(int c) {
    return inrange(c, '0', '9') || inrange(c, 'a', 'f') || inrange(c, 'A', 'F');
}