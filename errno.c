#include "errno.h"

#include "stdio.h"

__thread int errno = 0;

void _set_errno(int boii) {
    // printf("errno set to %i\n", boii);
    errno = boii;
}