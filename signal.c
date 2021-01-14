#include "signal.h"

#include "syscallids.h"
#include "unistd.h"

int kill(pid_t pid, int sig) {
    return syscall(SYS_KILL, pid, sig);
}

int sigaction(int signum, const struct sigaction* act, struct sigaction* oldact) {
    return syscall(SYS_SIGACT, signum, act, oldact);
}

void sigret() {
    syscall(SYS_SIGRET);
}