#pragma once

#include <sys/types.h>

struct dirent {
    ino_t d_ino;
    char  d_name[256];
};

struct dir {
    int           handle;
    struct dirent ent;
};

typedef struct dir DIR;

int alphasort(const struct dirent* a, const struct dirent* b);
int closedir(DIR*);
int dirfd(DIR*);
// DIR           *fdopendir(int);
DIR*           opendir(const char*);
struct dirent* readdir(DIR*);
// int            readdir_r(DIR*, struct dirent*, struct dirent**);
void rewinddir(DIR*);
/*int scandir(const char *, struct dirent ***,
        int (*)(const struct dirent *),
        int (*)(const struct dirent **,
        const struct dirent **));*/
void seekdir(DIR*, long);
long telldir(DIR*);