#pragma once

#define O_RDONLY 0x01
#define O_WRONLY 0x02
#define O_RDWR 0x03

// int creat(const char*, mode_t);
// int fcntl(int, int, ...);
int open(const char* path, int mode);
// int posix_fadvise(int, off_t, off_t, int);
// int posix_fallocate(int, off_t, off_t);