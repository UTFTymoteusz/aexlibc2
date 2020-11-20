#include "errno.h"

#include "stdio.h"

int __thread errno = 0;

void _set_errno(int boii) {
    // printf("errno set to %i\n", boii);
    errno = boii;
}