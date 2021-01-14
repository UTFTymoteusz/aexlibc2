#include "sys/mman.h"

#include "syscallids.h"
#include "unistd.h"

void* mmap(void* addr, size_t length, int prot, int flags, int fd, off_t offset) {
    return (void*) syscall(SYS_MMAP, addr, length, prot, flags, fd, offset);
}

int munmap(void* addr, size_t length) {
    return syscall(SYS_MUNMAP, addr, length);
}