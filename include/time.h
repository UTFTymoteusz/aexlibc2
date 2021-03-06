#pragma once

#include <sys/types.h>

#include <stddef.h>

struct sigevent;

struct tm {
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;
};

struct timespec {
    time_t tv_sec;
    long   tv_nsec;
};

struct itimerspec {
    struct timespec it_interval;
    struct timespec it_value;
};

int nanosleep(const struct timespec* rqtp, struct timespec* rmtp);

// TODO: finish