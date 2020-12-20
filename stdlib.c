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

struct mem_pool {
    // mutex_t mutex;

    uint32_t pieces;
    uint32_t free_pieces;
    uint32_t reserved_pieces;

    struct mem_pool* next;

    char* name;
    void* start;

    bool ignore_mutex;

    ALLOC_DATATYPE bitmap[];
};
typedef struct mem_pool mem_pool_t;

struct mem_block {
    uint8_t wasted_size;
    uint8_t uses;

    uint16_t cookie;

    uint32_t start_piece;
    uint32_t pieces;
};
typedef struct mem_block mem_block_t;

mem_pool_t* mem_pool0 = NULL;

size_t mem_page_size;

static inline size_t topg(size_t bytes) {
    return (bytes + (mem_page_size - 1)) / mem_page_size;
}

static inline size_t frompg(size_t pages) {
    return pages * mem_page_size;
}

inline size_t floor_to_alignment(size_t in) {
    return (in / POOL_PIECE_SIZE) * POOL_PIECE_SIZE;
}

inline size_t ceil_to_alignment(size_t in) {
    return ((in + (POOL_PIECE_SIZE - 1)) / POOL_PIECE_SIZE) * POOL_PIECE_SIZE;
}

mem_pool_t* pool_create(uint32_t size, char* name) {
    mem_page_size = 4096;

    size += (size % (POOL_PIECE_SIZE * 2));
    size_t pieces = size / POOL_PIECE_SIZE;

    size_t required_size = size + sizeof(mem_pool_t);

    void* ptr = mmap(NULL, required_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, -1, 0);

    size_t actual_size =
        ((frompg(topg(required_size)) - sizeof(mem_pool_t)) / POOL_PIECE_SIZE) * POOL_PIECE_SIZE;
    size_t remaining_size = floor_to_alignment(actual_size - (pieces / 8));

    mem_pool_t* pool = ptr;

    pool->pieces      = remaining_size / POOL_PIECE_SIZE;
    pool->free_pieces = pool->pieces;

    pool->start = (void*) ceil_to_alignment(((size_t) pool + sizeof(mem_pool_t) + (pieces / 8)));
    pool->name  = name;

    pool->next = NULL;

    memset(&(pool->bitmap), 0, pool->pieces / 8);
    memset(pool->start, 0, pool->pieces * POOL_PIECE_SIZE);

    return pool;
}

static inline int64_t find_space(mem_pool_t* pool, size_t piece_amount) {
    if (piece_amount == 0)
        return -1;

    size_t  combo     = 0;
    int64_t start     = -1;
    size_t  remaining = pool->pieces;

    int32_t  current_index = 0;
    uint16_t bit           = 0;

    size_t bitmap_piece = pool->bitmap[current_index];

    while (remaining-- > 0) {
        if (bit >= (sizeof(ALLOC_DATATYPE) * 8)) {
            bitmap_piece = pool->bitmap[++current_index];
            bit          = 0;
        }

        if (((bitmap_piece >> bit) & 0b01) == 1) {
            start = -1;
            combo = 0;

            bit++;
            continue;
        }

        if (start == -1)
            start = current_index * (sizeof(ALLOC_DATATYPE) * 8) + bit;

        bit++;
        combo++;
        if (combo == piece_amount)
            return start;
    }
    // printk("failed\n");
    return -1;
}

static inline void set_pieces(mem_pool_t* pool, size_t starting_piece, size_t amount,
                              bool occupied) {
    if (amount == 0)
        return;

    uint32_t current_index = starting_piece / (sizeof(ALLOC_DATATYPE) * 8);
    uint16_t bit           = starting_piece % (sizeof(ALLOC_DATATYPE) * 8);

    ALLOC_DATATYPE bitmap_piece = pool->bitmap[current_index];

    if (occupied) {
        while (amount-- > 0) {
            if (bit >= (sizeof(ALLOC_DATATYPE) * 8)) {
                pool->bitmap[current_index] = bitmap_piece;
                bitmap_piece                = pool->bitmap[++current_index];
                bit                         = 0;
            }
            if (bitmap_piece & (1 << bit)) {
                fprintf(stderr, "mempool: ALLOC FAILED: R: %li, CI: %i\n", amount, current_index);
            }
            bitmap_piece |= (1 << bit++);
        }
    }
    else {
        while (amount-- > 0) {
            if (bit >= (sizeof(ALLOC_DATATYPE) * 8)) {
                pool->bitmap[current_index] = bitmap_piece;
                bitmap_piece                = pool->bitmap[++current_index];
                bit                         = 0;
            }
            if (!(bitmap_piece & (1 << bit))) {
                fprintf(stderr, "mempool: FREE FAILED: R: %li\n", amount);
            }
            bitmap_piece &= ~(1 << bit++);
        }
    }
    pool->bitmap[current_index] = bitmap_piece;
}

static inline size_t addr_to_piece(mem_pool_t* pool, void* addr) {
    return ((size_t) addr - (size_t) pool->start) / POOL_PIECE_SIZE;
}

static inline mem_pool_t* find_parent(void* addr, mem_pool_t* root) {
    mem_pool_t* current = root;
    size_t      cmp;
    while (current != NULL) {
        cmp = ((size_t) addr - (size_t) current->start);
        if (cmp <= (current->pieces * POOL_PIECE_SIZE) && addr >= current->start)
            return current;

        current = current->next;
    }
    return NULL;
}

static inline mem_block_t* get_block_from_ext_addr(void* addr) {
    return (mem_block_t*) (floor_to_alignment((size_t) addr) - POOL_PIECE_SIZE);
}

void verify_pools(char* id) {
    mem_pool_t* pool = mem_pool0;

    size_t combo     = 0;
    size_t remaining = pool->pieces;

    int32_t  current_index = 0;
    uint16_t bit           = 0;

    uint8_t* addr;

    ALLOC_DATATYPE bitmap_piece = pool->bitmap[current_index];

    while (remaining-- > 0) {
        if (bit >= (sizeof(ALLOC_DATATYPE) * 8)) {
            bitmap_piece = pool->bitmap[++current_index];
            bit          = 0;
        }

        if (((bitmap_piece >> bit) & 0b01) == 1) {
            bit++;
            continue;
        }

        addr = (uint8_t*) ((uint8_t*) pool->start +
                           (current_index * (sizeof(ALLOC_DATATYPE) * 8) + bit) * POOL_PIECE_SIZE);
        for (size_t i = 0; i < POOL_PIECE_SIZE; i++) {
            if (addr[i] != '\0') {
                fprintf(stderr, "mem: %s\n", id);
            }
        }
        bit++;
        combo++;
    }
}

void* calloc(size_t nmeb, size_t size) {
    return malloc(nmeb * size);
}

void* malloc(size_t size) {
    if (size == 0)
        return NULL;

    // size_t aa;
    // asm volatile("mov %%rsp, %0" : : "r"(aa));
    // printf("malloc(%i) 0x%x\n", size, aa);

    if (mem_pool0 == NULL)
        mem_pool0 = pool_create(65536, "Root");

    mem_pool_t* pool = mem_pool0;

    size = ceil_to_alignment(size);
    size_t pieces =
        (size / POOL_PIECE_SIZE) + (ceil_to_alignment(sizeof(mem_block_t)) / POOL_PIECE_SIZE);

    int64_t starting_piece = 0;

    // mutex_acquire_yield(&(pool->mutex));

    while (true) {
        if (pool->free_pieces < pieces || starting_piece == -1) {
            if (pool->next == NULL) {
                pool->next = pool_create((size > DEFAULT_POOL_SIZE) ? size * 2 : DEFAULT_POOL_SIZE,
                                         pool->name);
                pool->next->ignore_mutex = pool->ignore_mutex;
            }
            // mutex_release(&(pool->mutex));
            pool = pool->next;
            // mutex_acquire_yield(&(pool->mutex));
        }

        starting_piece = find_space(pool, pieces);
        if (starting_piece == -1)
            continue;

        set_pieces(pool, starting_piece, pieces, true);
        pool->free_pieces -= pieces;

        break;
    }
    // mutex_release(&(pool->mutex));

    void* addr = (void*) ((size_t) pool->start + ((starting_piece + 1) * POOL_PIECE_SIZE));

    /*uint8_t* test = (uint8_t*) get_block_from_ext_addr(addr);
    for (size_t i = 0; i < pieces * POOL_PIECE_SIZE; i++) {
        if (*test != 0)
            kpanic("not blank");
        test++;
    }*/
    mem_block_t* block = get_block_from_ext_addr(addr);
    block->start_piece = starting_piece;
    block->pieces      = pieces - 1;
    block->uses        = 1;
    block->wasted_size = 0;
    block->cookie      = 0xD6A4;

    return addr;
}

void* realloc(void* space, size_t size) {
    if (space == NULL) {
        if (size == 0)
            return NULL;

        return malloc(size);
    }
    if (size == 0) {
        free(space);
        return NULL;
    }
    mem_block_t* block   = get_block_from_ext_addr(space);
    uint64_t     oldsize = block->pieces * POOL_PIECE_SIZE;

    void* new = malloc(size);

    memcpy(new, space, oldsize);
    free(space);

    return new;
}

void free(void* space) {
    mem_block_t* block  = get_block_from_ext_addr(space);
    mem_pool_t*  parent = find_parent(block, mem_pool0);

    set_pieces(parent, addr_to_piece(parent, block), block->pieces + 1, false);
    parent->free_pieces += block->pieces + 1;
    memset((void*) block, 0, (block->pieces + 1) * POOL_PIECE_SIZE);
}