#include "errno.h"

#include "stdio.h"

__thread int errno = 0;

void _set_errno(int boii) {
    errno = boii;
}