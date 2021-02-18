#pragma once

#ifdef NDEBUG
#define assert(ignore) ((void) 0)
#else
#include <stdio.h>
#include <stdlib.h>
#define assert(condition)                                                                       \
    ({                                                                                          \
        if (!(condition)) {                                                                     \
            fprintf(stderr, "%s:%i: Assertion failed! (%s)\n", __FILE__, __LINE__, #condition); \
            abort();                                                                            \
        }                                                                                       \
    })
#endif