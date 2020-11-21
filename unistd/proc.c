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