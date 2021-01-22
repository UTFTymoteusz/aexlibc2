#pragma once

#include <sys/types.h>

struct stat {
    dev_t     st_dev;
    ino_t     st_ino;
    mode_t    st_mode;
    nlink_t   st_nlink;
    uid_t     st_uid;
    gid_t     st_gid;
    dev_t     st_rdev;
    off_t     st_size;
    time_t    st_atime;
    time_t    st_mtime;
    time_t    st_ctime;
    blksize_t st_blksize;
    blkcnt_t  st_blocks;
};

#define S_IFMT 0x0FFF0000
#define S_IFBLK 0x00060000
#define S_IFCHR 0x00020000
#define S_IFNET 0x000A0000
#define S_IFREG 0x00010000
#define S_IFDIR 0x00100000
#define S_IFLNK 0x00200000
#define S_IFFIFO 0x00400000
#define S_IFMQ 0x01000000
#define S_IFSEM 0x02000000
#define S_IFSHM 0x04000000

#define S_IRWXU 0x0700
#define S_IRUSR 0x0400
#define S_IWUSR 0x0200
#define S_IXUSR 0x0100

#define S_IRWXG 0x0070
#define S_IRGRP 0x0040
#define S_IWGRP 0x0020
#define S_IXGRP 0x0010

#define S_IRWXO 0x0007
#define S_IROTH 0x0004
#define S_IWOTH 0x0002
#define S_IXOTH 0x0001

#define S_ISUID 0x4000
#define S_ISGID 0x2000
#define S_ISVTX 0x1000

#define S_ISBLK(val) ((val & S_IFBLK) ? 1 : 0)
#define S_ISCHR(val) ((val & S_IFCHR) ? 1 : 0)
#define S_ISNET(val) ((val & S_IFNET) ? 1 : 0)
#define S_ISDIR(val) ((val & S_IFDIR) ? 1 : 0)
#define S_ISFIFO(val) ((val & S_IFFIFO) ? 1 : 0)
#define S_ISREG(val) ((val & S_IFREG) ? 1 : 0)
#define S_ISLNK(val) ((val & S_IFLNK) ? 1 : 0)

#define S_TYPEISMQ(stat) ((stat->st_mode & S_IFMQ) ? 1 : 0)
#define S_TYPEISSEM(stat) ((stat->st_mode & S_IFSEM) ? 1 : 0)
#define S_TYPEISSHM(stat) ((stat->st_mode & S_IFSHM) ? 1 : 0)

int    chmod(const char* path, mode_t);
int    fchmod(int fd, mode_t);
int    fstat(int fd, struct stat*);
int    lstat(const char* path, struct stat*);
int    mkdir(const char* path, mode_t);
int    mkfifo(const char* path, mode_t);
int    mknod(const char* path, mode_t, dev_t);
int    stat(const char* path, struct stat*);
mode_t umask(mode_t);