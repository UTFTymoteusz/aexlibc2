#include "sys/wait.h"

#include "syscallids.h"
#include "unistd.h"

pid_t wait(int* status) {
    return syscall(SYS_WAIT, status);
}