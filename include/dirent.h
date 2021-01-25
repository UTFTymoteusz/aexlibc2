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

int            closedir(DIR*);
DIR*           opendir(const char*);
struct dirent* readdir(DIR*);
int            readdir_r(DIR*, struct dirent*, struct dirent**);
void           rewinddir(DIR*);
void           seekdir(DIR*, long);
long           telldir(DIR*);