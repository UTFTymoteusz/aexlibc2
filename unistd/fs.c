#include "stddef.h"
#include "stdint.h"
#include "sys/ioctl.h"
#include "sys/types.h"
#include "syscallids.h"
#include "unistd.h"

ssize_t read(int fd, void* buffer, size_t len) {
    return syscall(SYS_READ, (long) fd, buffer, len);
}

ssize_t write(int fd, const void* buffer, size_t len) {
    return syscall(SYS_WRITE, (long) fd, buffer, len);
}

int close(int fd) {
    return syscall(SYS_CLOSE, (long) fd);
}

off_t lseek(int fd, off_t offset, int mode) {
    return syscall(SYS_SEEK, (long) fd, offset, mode);
}

int dup(int fd) {
    return syscall(SYS_DUP, (long) fd);
}

int dup2(int srcfd, int dstfd) {
    return syscall(SYS_DUP2, (long) srcfd, (long) dstfd);
}

int chdir(const char* path) {
    return syscall(SYS_CHDIR, path);
}

char* getcwd(char* buffer, size_t buffer_len) {
    return (char*) syscall(SYS_GETCWD, buffer, buffer_len);
}

int isatty(int fd) {
    return syscall(SYS_ISATTY, fd);
}

int access(const char* path, int mode) {
    return syscall(SYS_ACCESS, path, mode);
}

int unlink(const char* path) {
    return syscall(SYS_UNLINK, path);
}

pid_t tcgetpgrp(int fd) {
    return ioctl(fd, 0x08);
}

int tcsetpgrp(int fd, pid_t pgrp) {
    return ioctl(fd, 0x09, pgrp);
}