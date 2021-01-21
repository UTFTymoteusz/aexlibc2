#pragma once

#include "stddef.h"
#include "sys/types.h"

enum prot_flags_t {
    PROT_NONE  = 0x00,
    PROT_READ  = 0x01,
    PROT_WRITE = 0x02,
    PROT_EXEC  = 0x04,
};

enum mmap_flags_t {
    MAP_NONE      = 0x00,
    MAP_PRIVATE   = 0x01,
    MAP_SHARED    = 0x02,
    MAP_FIXED     = 0x04,
    MAP_ANONYMOUS = 0x10,
};

void* mmap(void* addr, size_t length, int prot, int flags, int fd, off_t offset);
int   munmap(void* addr, size_t length);