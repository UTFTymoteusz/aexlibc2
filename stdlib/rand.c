#include "stdlib.h"
#include "string.h"

#include <stdint.h>

uint32_t next = 0;

int rand() {
    next = next * 1103515245 + 12345;
    return (unsigned int) (next / 65536) % (RAND_MAX + 1);
}

void srand(unsigned int seed) {
    next = seed;
}