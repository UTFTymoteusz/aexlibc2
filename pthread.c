#include "pthread.h"

#include "errno.h"
#include "signal.h"
#include "stdbool.h"
#include "stdio.h"
#include "syscallids.h"
#include "unistd.h"

__thread bool pthread_cancelled    = false;
__thread int  pthread_cancel_state = PTHREAD_CANCEL_ENABLE;
__thread int  pthread_cancel_type  = PTHREAD_CANCEL_DEFERRED;

void pthread_handlecancel();
void pthread_sighandler(int);

void pthread_init() {
    struct sigaction act = {};

    act.sa_handler = pthread_sighandler;
    act.sa_flags   = 0;

    sigaction(SIGCNCL, &act, NULL);
}

void pthread_sighandler(int) {
    pthread_cancelled = true;
    pthread_handlecancel();
}

int pthread_attr_init(pthread_attr_t* attr) {
    attr->stack_size = 8192;
    return 0;
}

int pthread_attr_destroy(pthread_attr_t* attr) {
    attr->stack_size = 0;
    return 0;
}

int pthread_setcancelstate(int state, int* oldstate) {
    if (state != PTHREAD_CANCEL_DISABLE && state != PTHREAD_CANCEL_ENABLE)
        return EINVAL;

    if (oldstate)
        *oldstate = pthread_cancel_state;

    sigset_t set;

    sigemptyset(&set);
    sigaddset(&set, SIGCNCL);

    syscall(SYS_SIGTMASK, state == PTHREAD_CANCEL_ENABLE ? SIG_UNBLOCK : SIG_BLOCK, &set, NULL);

    pthread_cancel_state = state;
    return 0;
}

int pthread_setcanceltype(int type, int* oldtype) {
    if (type != PTHREAD_CANCEL_DEFERRED && type != PTHREAD_CANCEL_ASYNCHRONOUS)
        return EINVAL;

    if (oldtype)
        *oldtype = pthread_cancel_type;

    syscall(SYS_SIGATHRD, type == PTHREAD_CANCEL_ASYNCHRONOUS);

    pthread_cancel_type = type;
    return 0;
}

void pthread_testcancel() {
    if (pthread_cancelled && pthread_cancel_state == PTHREAD_CANCEL_ENABLE)
        pthread_handlecancel();
}

void pthread_enter(void* (*start_routine)(void* arg), void* arg) {
    pthread_init();
    pthread_exit(start_routine(arg));
}

int pthread_create(pthread_t* thread, const pthread_attr_t* attr, void* (*start_routine)(void* arg),
                   void* arg) {
    *thread =
        syscall(SYS_TCREATE, pthread_enter, attr ? attr->stack_size : 8192, start_routine, arg);
    if (*thread == -1)
        return errno;

    return 0;
}

int pthread_join(pthread_t thread, void** retval) {
    int val = syscall(SYS_TJOIN, thread, retval);
    if (val == -1)
        return errno;

    return 0;
}

int pthread_kill(pthread_t thread, int signal) {
    int val = syscall(SYS_TKILL, thread, signal);
    if (val == -1)
        return errno;

    return 0;
}

int pthread_cancel(pthread_t thread) {
    return pthread_kill(thread, SIGCNCL);
}

void pthread_exit(void* status) {
    syscall(SYS_TEXIT, status);
}

void pthread_handlecancel() {
    pthread_exit(PTHREAD_CANCELED);
}

int pthread_sigmask(int how, const sigset_t* set, sigset_t* oldset) {
    sigset_t newset;

    if (set) {
        newset = *set;
        sigdelset(&newset, SIGCNCL);

        set = &newset;
    }

    int val = syscall(SYS_SIGTMASK, how, set, oldset);
    if (val == -1)
        return errno;

    return 0;
}

pthread_t pthread_self() {
    return syscall(SYS_GETTID);
}