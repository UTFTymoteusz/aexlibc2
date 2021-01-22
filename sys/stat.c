#include "sys/stat.h"

#include "stdio.h"
#include "sys/types.h"
#include "syscallids.h"
#include "unistd.h"

#define AT_NONE 0x00
#define AT_EMPTY_PATH 0x01
#define AT_SYMLINK_NOFOLLOW 0x02

int chmod(const char* path, mode_t mode) {
    return syscall(SYS_CHMOD, path, mode);
}

int fchmod(int fd, mode_t mode) {
    return syscall(SYS_FCHMOD, fd, mode);
}

int fstat(int fd, struct stat* buf) {
    return syscall(SYS_FSTAT, fd, buf);
}

int lstat(const char* path, struct stat* buf) {
    return syscall(SYS_STATAT, path, buf, AT_SYMLINK_NOFOLLOW);
}

int mkdir(const char* path, mode_t mode) {
    return syscall(SYS_MKDIR, path, mode);
}

int mkfifo(const char* path, mode_t mode) {
    return syscall(SYS_MKFIFO, path, mode);
}

int mknod(const char* path, mode_t mode, dev_t dev) {
    return syscall(SYS_MKNOD, path, mode, dev);
}

int stat(const char* path, struct stat* buf) {
    return syscall(SYS_STATAT, path, buf, 0);
}

mode_t umask(mode_t mask) {
    return syscall(SYS_UMASK, mask);
}