#pragma once

#include "stddef.h"
#include "sys/types.h"

enum perm_test_t {
    R_OK = 0x01,
    W_OK = 0x02,
    X_OK = 0x04,
    F_OK = 0x08,
};

long syscall(long id, ...);

unsigned int sleep(unsigned int seconds);

int     access(const char* path, int mode);
ssize_t read(int fd, void* buffer, size_t len);
ssize_t write(int fd, const void* buffer, size_t len);
int     close(int fd);
off_t   lseek(int fd, off_t offset, int mode);
int     dup(int fd);
int     dup2(int srcfd, int dstfd);
int     chdir(const char* path);
char*   getcwd(char* buffer, size_t buffer_len);
int     isatty(int fd);

int pipe(int fds[2]);

pid_t fork();
int   execve(const char* path, char* const argv[], char* const envp[]);
pid_t getpid();
int   nice(int nice);

int gethostname(char*, size_t);

gid_t getegid();
uid_t geteuid();
gid_t getgid();
uid_t getuid();

int setegid(gid_t gid);
int seteuid(uid_t uid);
int setgid(gid_t gid);
int setuid(uid_t uid);
int setregid(gid_t rgid, gid_t egid);
int setreuid(uid_t ruid, uid_t euid);

int unlink(const char* path);

/*
unsigned     alarm(unsigned);
int          chown(const char *, uid_t, gid_t);
size_t       confstr(int, char *, size_t);
char        *crypt(const char *, const char *);
void         _exit(int);
void         encrypt(char [64], int);
int          execl(const char *, const char *, ...);
int          execle(const char *, const char *, ...);
int          execlp(const char *, const char *, ...);
int          execv(const char *, char *const []);
int          execvp(const char *, char *const []);
int          faccessat(int, const char *, int, int);
int          fchdir(int);
int          fchown(int, uid_t, gid_t);
int          fchownat(int, const char *, uid_t, gid_t, int);
int          fdatasync(int);
int          fexecve(int, char *const [], char *const []);
long         fpathconf(int, int);
int          fsync(int);
int          ftruncate(int, off_t);
int          getgroups(int, gid_t []);
long         gethostid(void);
char        *getlogin(void);
int          getlogin_r(char *, size_t);
int          getopt(int, char * const [], const char *);
pid_t        getpgid(pid_t);
pid_t        getpgrp(void);
pid_t        getppid(void);
pid_t        getsid(pid_t);
int          lchown(const char *, uid_t, gid_t);
int          link(const char *, const char *);
int          linkat(int, const char *, int, const char *, int);
int          lockf(int, int, off_t);
long         pathconf(const char *, int);
int          pause(void);
ssize_t      pread(int, void *, size_t, off_t);
ssize_t      pwrite(int, const void *, size_t, off_t);
ssize_t      readlink(const char *restrict, char *restrict, size_t);
ssize_t      readlinkat(int, const char *restrict, char *restrict, size_t);
int          rmdir(const char *);
int          setpgid(pid_t, pid_t);
pid_t        setpgrp(void);
pid_t        setsid(void);
void         swab(const void *restrict, void *restrict, ssize_t);
int          symlink(const char *, const char *);
int          symlinkat(const char *, int, const char *);
void         sync(void);
long         sysconf(int);
pid_t        tcgetpgrp(int);
int          tcsetpgrp(int, pid_t);
int          truncate(const char *, off_t);
char        *ttyname(int);
int          ttyname_r(int, char *, size_t);
int          unlinkat(int, const char *, int);
*/