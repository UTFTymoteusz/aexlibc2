#pragma once

#define F_DUPFD 0x01
#define F_DUPFD_CLOEXEC 0x02
#define F_GETFD 0x03
#define F_SETFD 0x04
#define F_GETFL 0x05
#define F_SETFL 0x06

#define FD_CLOEXEC 0x0001

#define O_RDONLY 0x01
#define O_WRONLY 0x02
#define O_RDWR 0x03
#define O_CREAT 0x20

//#define O_NONBLOCK 0x0001

// int creat(const char*, mode_t);
int fcntl(int fd, int cmd, ...);
int open(const char* path, int mode);
// int posix_fadvise(int, off_t, off_t, int);
// int posix_fallocate(int, off_t, off_t);