#include "dirent.h"

#include "errno.h"
#include "stdlib.h"
#include "sys/stat.h"
#include "syscallids.h"
#include "unistd.h"

int closedir(DIR* dir) {
    int handle = dir->handle;
    free(dir);

    return close(handle);
}

DIR* opendir(const char* path) {
    struct stat sb;

    if (stat(path, &sb) == -1)
        return NULL;

    if (!S_ISDIR(sb.st_mode)) {
        errno = ENOTDIR;
        return NULL;
    }

    int handle = syscall(SYS_OPEN, path, 1);
    if (handle == -1)
        return NULL;

    DIR* dir    = (DIR*) malloc(sizeof(DIR));
    dir->handle = handle;

    return dir;
}

struct dirent* readdir(DIR* dir) {
    if (syscall(SYS_READDIR, dir->handle, &dir->ent) < 0)
        return NULL;

    return &dir->ent;
}

int readdir_r(DIR*, struct dirent*, struct dirent**);

void rewinddir(DIR* dir) {
    seekdir(dir, -1);
}

void seekdir(DIR* dir, long pos) {
    syscall(SYS_SEEKDIR, dir->handle, pos);
}

long telldir(DIR* dir) {
    return syscall(SYS_TELLDIR, dir->handle);
}