#include "errno.h"

#include "stdio.h"

__thread int errno = ENOSYS;

void _set_errno(int boii) {
    errno = boii;
}