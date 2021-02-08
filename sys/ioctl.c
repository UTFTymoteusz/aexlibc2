#include "sys/ioctl.h"

#include "syscallids.h"
#include "unistd.h"

#include <stdarg.h>
#include <stddef.h>

int ioctl(int fd, int rq, ...) {
    va_list args;
    va_start(args, rq);

    int ret = syscall(SYS_IOCTL, fd, rq, va_arg(args, uint64_t));
    va_end(args);

    return ret;
}