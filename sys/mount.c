#include "sys/mount.h"

#include "syscallids.h"
#include "unistd.h"

int mount(const char* source, const char* target, const char* type, unsigned long flags,
          const void* data) {
    return syscall(SYS_MOUNT, source, target, type, flags, data);
}

int umount(const char* target) {
    return syscall(SYS_UMOUNT, target);
}