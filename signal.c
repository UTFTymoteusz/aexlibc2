#include "signal.h"

#include "errno.h"
#include "syscallids.h"
#include "unistd.h"

int kill(pid_t pid, int sig) {
    return syscall(SYS_KILL, pid, sig);
}

int killpg(pid_t pgrp, int sig) {
    if (pgrp < 0) {
        errno = EINVAL;
        return -1;
    }

    if (pgrp == 0) {
        pid_t pgrp = getpgrp();
        if (pgrp == -1)
            return -1;

        return syscall(SYS_KILL, -pgrp, sig);
    }

    return syscall(SYS_KILL, -pid, sig);
}

int sigaction(int signum, const struct sigaction* act, struct sigaction* oldact) {
    return syscall(SYS_SIGACT, signum, act, oldact);
}

void sigret() {
    syscall(SYS_SIGRET);
}