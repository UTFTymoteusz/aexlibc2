#include "syscallids.h"
#include "unistd.h"

int pipe(int fds[2]) {
    return syscall(SYS_PIPE, &fds[0], &fds[1]);
}