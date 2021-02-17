#include <syscallids.h>
#include <unistd.h>

int gethostname(char* buffer, size_t len) {
    return syscall(SYS_GETHOSTNAME, buffer, len);
}