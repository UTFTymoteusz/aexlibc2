#include "signal.h"

#include "errno.h"
#include "pthread.h"
#include "syscallids.h"
#include "unistd.h"
#include "utility.h"

int raise(int sig) {
    pthread_kill(pthread_self(), sig);
}

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

    return syscall(SYS_KILL, -pgrp, sig);
}

void (*signal(int sig, void (*func)(int sig)))(int sig) {
    struct sigaction act;
    struct sigaction oldact;

    act.sa_handler = func;
    act.sa_flags   = 0;

    sigaction(sig, &act, &oldact);

    return oldact.sa_handler;
}

int sigqueue(pid_t pid, int sig, const union sigval val) {
    return syscall(SYS_SIGQUEUE, pid, sig, val);
}

int sigaction(int signum, const struct sigaction* act, struct sigaction* oldact) {
    return syscall(SYS_SIGACT, signum, act, oldact);
}

int sigprocmask(int how, const sigset_t* set, sigset_t* oldset) {
    sigset_t newset;

    if (set) {
        newset = *set;
        sigdelset(&newset, SIGCNCL);

        set = &newset;
    }

    return syscall(SYS_SIGTMASK, how, set, oldset);
}

int sigwait(const sigset_t* set, int* sig) {
    if (!sig) {
        errno = EFAULT;
        return -1;
    }

    int ret = syscall(SYS_SIGWAIT, set, NULL, 0);
    if (ret > 0) {
        if (sig)
            *sig = ret;

        return 0;
    }
    else
        return -ret;
}

int sigwaitinfo(const sigset_t* set, siginfo_t* info) {
    int ret = syscall(SYS_SIGWAIT, set, info, 0);
    return ret;
}

int sigtimedwait(const sigset_t* set, siginfo_t* info, const struct timespec* timeout) {
    if (!timeout) {
        errno = EINVAL;
        return -1;
    }

    unsigned long ns  = (long) timeout->tv_sec * 1000000000 + (long) timeout->tv_nsec;
    int           ret = syscall(SYS_SIGWAIT, set, info, ns);

    return ret;
}

int sighold(int sig) {
    sigset_t set;

    ENSURE(sigemptyset(&set));
    ENSURE(sigaddset(&set, sig));

    sigprocmask(SIG_BLOCK, &set, NULL);
    return 0;
}

int sigrelse(int sig) {
    sigset_t set;

    ENSURE(sigemptyset(&set));
    ENSURE(sigaddset(&set, sig));

    sigprocmask(SIG_UNBLOCK, &set, NULL);
    return 0;
}

int sigignore(int sig) {
    struct sigaction act = {};

    act.sa_handler = SIG_IGN;
    act.sa_flags   = 0;

    return sigaction(sig, &act, NULL);
}

int sigpause(int sig) {
    sigset_t mask;
    sigaddset(&mask, sig);

    return sigsuspend(&mask);
}

int sigpending(sigset_t* set) {
    return syscall(SYS_SIGPENDING, set);
}

int sigsuspend(const sigset_t* mask) {
    sigset_t oldmask;
    sigprocmask(SIG_SETMASK, NULL, &oldmask);

    int ret     = syscall(SYS_SIGSUSPEND, mask);
    int r_errno = errno;

    sigprocmask(SIG_SETMASK, &oldmask, NULL);

    errno = r_errno;
    return ret;
}

int sigemptyset(sigset_t* set) {
    for (int i = 0; i < 4; i++)
        set->quads[i] = 0x00000000;

    return 0;
}

int sigfillset(sigset_t* set) {
    for (int i = 0; i < 4; i++)
        set->quads[i] = 0xFFFFFFFF;

    return 0;
}

int sigaddset(sigset_t* set, int sig) {
    if (sig < 0 || sig > 127)
        return -1;

    set->quads[sig / 32] |= (1 << (sig % 32));
    return 0;
}

int sigdelset(sigset_t* set, int sig) {
    set->quads[sig / 32] &= ~(1 << (sig % 32));
    return 0;
}

int sigismember(const sigset_t* set, int sig) {
    if (sig < 0 || sig > 127)
        return -1;

    return set->quads[sig / 32] & (1 << (sig % 32));
}