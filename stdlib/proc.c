#include "stdlib.h"
#include "syscallids.h"
#include "unistd.h"

void exit(int status) {
    syscall(SYS_EXIT, status);
}

void abort() {
    syscall(SYS_EXIT, 3);
}