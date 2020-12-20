#include "stdlib.h"

#include "stdio.h"
#include "string.h"
#include <sys/mman.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define POOL_PIECE_SIZE 16
#define DEFAULT_POOL_SIZE 1024 * 256

#define ALLOC_DATATYPE uint32_t
