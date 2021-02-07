#include "fcntl.h"

#include "syscallids.h"
#include "unistd.h"

#include <stdarg.h>
#include <stddef.h>

int fcntl(int fd, int cmd, ...) {
    va_list args;
    va_start(args, cmd);

    int ret = syscall(SYS_FCNTL, fd, cmd, va_arg(args, int));
    va_end(args);

    return ret;
}

int open(const char* path, int mode) {
    return syscall(SYS_OPEN, path, mode);
}