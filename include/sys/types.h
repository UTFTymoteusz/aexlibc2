#pragma once

#include <stdint.h>

#if INTPTR_MAX == INT32_MAX
typedef int ssize_t;
#else
typedef long ssize_t;
#endif

typedef int uid_t;
typedef int gid_t;
typedef int pid_t;

typedef int dev_t;
typedef int ino_t;

typedef int64_t off_t;