#include "syscallids.h"
#include "unistd.h"

unsigned int sleep(unsigned int seconds) {
    syscall(SYS_NSLEEP, (long) seconds * 1000000000);
    return 0;
}

int nsleep(long ns) {
    syscall(SYS_NSLEEP, ns);
    return 0;
}

pid_t fork() {
    __sync_synchronize();
    return syscall(SYS_FORK);
}

int execve(const char* path, char* const argv[], char* const envp[]) {
    return syscall(SYS_EXECVE, path, argv, envp);
}

pid_t getpid() {
    return syscall(SYS_GETPID);
}

int nice(int nice) {
    return syscall(SYS_NICE, nice);
}

pid_t setsid() {
    return syscall(SYS_SETSID);
}

pid_t getpgrp() {
    return -1;
}

pid_t setpgrp() {
    return -1;
}