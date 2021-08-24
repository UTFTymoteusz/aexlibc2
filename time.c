#include "time.h"

#include "assert.h"
#include "errno.h"
#include "syscallids.h"
#include "unistd.h"

// TODO: rmtp

int nanosleep(const struct timespec* rqtp, struct timespec* rmtp) {
    assert(rmtp == NULL);

    if (rqtp->tv_nsec < 0 || rqtp->tv_nsec >= 1000000000) {
        errno = EINVAL;
        return -1;
    }

    syscall(SYS_NSLEEP, (long) rqtp->tv_sec * 1000000000 + (long) rqtp->tv_nsec);
    return 0;
}