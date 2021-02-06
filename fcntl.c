#include "fcntl.h"

#include "syscallids.h"
#include "unistd.h"

int open(const char* path, int mode) {
    return syscall(SYS_OPEN, path, mode);
}