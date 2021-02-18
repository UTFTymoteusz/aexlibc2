#pragma once

#define F_DUPFD 0x01
#define F_GETFL 0x02
#define F_SETFL 0x03

#define FD_CLOEXEC 0x00010000

#define O_RDONLY 0x01
#define O_WRONLY 0x02
#define O_RDWR 0x03

//#define O_NONBLOCK 0x0001

// int creat(const char*, mode_t);
int fcntl(int fd, int cmd, ...);
int open(const char* path, int mode);
// int posix_fadvise(int, off_t, off_t, int);
// int posix_fallocate(int, off_t, off_t);