#include <syscallids.h>
#include <unistd.h>

unsigned int sleep(unsigned int seconds) {
    syscall(SYS_USLEEP, seconds * 1000000000);
    return 0;
}

int usleep(long ns) {
    syscall(SYS_USLEEP, ns);
    return 0;
}

pid_t fork() {
    return syscall(SYS_FORK);
}

int execve(const char* path, char* const argv[], char* const envp[]) {
    return syscall(SYS_EXECVE, path, argv, envp);
}

pid_t getpid() {
    return syscall(SYS_GETPID);
}