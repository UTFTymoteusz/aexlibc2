#include "syscallids.h"
#include "unistd.h"

gid_t getegid() {
    return syscall(SYS_GETEGID);
}

uid_t geteuid() {
    return syscall(SYS_GETEUID);
}

gid_t getgid() {
    return syscall(SYS_GETGID);
}

uid_t getuid() {
    return syscall(SYS_GETUID);
}

int setegid(gid_t gid) {
    return syscall(SYS_SETEGID, gid);
}

int seteuid(uid_t uid) {
    return syscall(SYS_SETEUID, uid);
}

int setgid(gid_t gid) {
    return syscall(SYS_SETGID, gid);
}

int setuid(uid_t uid) {
    return syscall(SYS_SETUID, uid);
}

int setregid(gid_t rgid, gid_t egid) {
    return syscall(SYS_SETREGID, rgid, egid);
}

int setreuid(uid_t ruid, uid_t euid) {
    return syscall(SYS_SETREUID, ruid, euid);
}