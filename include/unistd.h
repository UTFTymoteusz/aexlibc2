#pragma once

enum perm_test_t {
    R_OK = 0x01,
    W_OK = 0x02,
    X_OK = 0x04,
    F_OK = 0x08,
};

long syscall(long id, ...);

unsigned int sleep(unsigned int seconds);
int          usleep(long ns);

int access(const char* path, int amode);