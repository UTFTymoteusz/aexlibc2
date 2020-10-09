#include <unistd.h>
#include <syscallids.h>

unsigned int sleep(unsigned int seconds) {
    syscall(SYS_SLEEP, seconds * 1000);
    return 0;
}

int usleep(long ns) {
    syscall(SYS_SLEEP, ns / 1000);
    return 0;
}