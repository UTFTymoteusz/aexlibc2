#pragma once

#define ENSURE(expr)      \
    ({                    \
        int res = (expr); \
        if (res < 0) {    \
            return res;   \
        }                 \
        res;              \
    })