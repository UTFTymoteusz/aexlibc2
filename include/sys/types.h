#pragma once

#include "stdint.h"

#if INTPTR_MAX == INT32_MAX
typedef int32_t  ssize_t;
typedef uint32_t size_t;
#else
typedef int64_t  ssize_t;
typedef uint64_t size_t;
#endif

typedef int64_t blkcnt_t;
typedef int64_t blksize_t;

typedef uint64_t fsblkcnt_t;
typedef uint64_t fsfilcnt_t;

typedef int  id_t;
typedef id_t uid_t;
typedef id_t gid_t;

typedef uint64_t ino_t;
typedef int32_t  dev_t;
typedef int32_t  mode_t;
typedef int64_t  off_t;
typedef int64_t  nlink_t;

typedef id_t pid_t;

typedef int64_t suseconds_t;
typedef int64_t time_t;
typedef int64_t clock_t;

typedef int timer_t;