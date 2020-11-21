#include "sys/types.h"
#include "syscallids.h"
#include "unistd.h"

#include <stddef.h>
#include <stdint.h>

ssize_t read(int fd, void* buffer, size_t len) {
    return syscall(SYS_READ, (long) fd, buffer, len);
}

ssize_t write(int fd, const void* buffer, size_t len) {
    return syscall(SYS_WRITE, (long) fd, buffer, len);
}

int isatty(int fd) {
    return syscall(SYS_ISATTY, fd);
}