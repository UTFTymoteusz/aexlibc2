#include "stdlib.h"

#include "stdio.h"
#include "string.h"
#include <sys/mman.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define PIECE_SIZE 16
#define DEFAULT_POOL_SIZE 1024 * 256

#define ALLOC_DATATYPE uint32_t

#define ceil_alloc(x) (((x + PIECE_SIZE - 1) / PIECE_SIZE) * PIECE_SIZE)

struct pool {
    uint32_t     pieces;
    struct pool *prev, *next;
} __attribute((packed));
typedef struct pool pool_t;

struct chunk {
    uint32_t next;
    uint32_t prev;

    uint16_t pieces;
    bool     free;
    bool     mmapped;
} __attribute((packed));
typedef struct chunk chunk_t;

pool_t* first_pool = NULL;

pool_t*  alloc_pool(uint32_t size);
chunk_t* create_chunk(pool_t* pool, uint32_t piece_start, uint32_t piece_count);
chunk_t* get_chunk(pool_t* pool, uint32_t piece_start);
uint32_t startof(pool_t* pool, chunk_t* chunk);
void*    alloc_chunk(pool_t* pool, chunk_t* chunk, uint32_t piece_count);
void     debug_print_pools();

void* malloc(size_t size) {
    if (!first_pool)
        first_pool = alloc_pool(DEFAULT_POOL_SIZE);

    pool_t* pool = first_pool;

    while (true) {
        uint32_t start = 0;

        while (true) {
            chunk_t* chunk = get_chunk(pool, start);
            if (!chunk->free) {
                start = chunk->next;
                continue;
            }

            void* try = alloc_chunk(pool, chunk, ceil_alloc(size) / PIECE_SIZE);
            if (try)
                return try;

            if (!chunk->next)
                break;

            start = chunk->next;
        }

        if (!pool->next)
            pool->next = alloc_pool(DEFAULT_POOL_SIZE);

        pool = pool->next;
    }

    return NULL;
}

void* calloc(size_t nmeb, size_t size) {
    return malloc(nmeb * size);
}

size_t msize(void* ptr) {
    chunk_t* chunk = (chunk_t*) ((size_t) ptr - PIECE_SIZE);
    return chunk->pieces * PIECE_SIZE;
}

void* realloc(void* ptr, size_t size) {
    if (!ptr)
        return malloc(size);

    if (size == 0) {
        free(ptr);
        return NULL;
    }

    size_t oldsize = msize(ptr);
    void*  newptr  = malloc(size);

    if (!newptr) {
        free(ptr);
        return NULL;
    }

    memcpy(newptr, ptr, min(oldsize, size));
    free(ptr);

    return newptr;
}

void free(void* ptr) {
    pool_t*  pool  = first_pool;
    chunk_t* chunk = (chunk_t*) ((size_t) ptr - PIECE_SIZE);

    chunk->free = true;

    // merge free chunks here
}

// Privates

pool_t* alloc_pool(uint32_t size) {
    void* mem = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    // add checks

    pool_t* pool = (pool_t*) mem;
    pool->pieces = (size - ceil_alloc(sizeof(pool_t))) / PIECE_SIZE;
    pool->next   = NULL;
    pool->prev   = NULL;

    chunk_t* chunk = create_chunk(pool, 0, pool->pieces - 1);
    chunk->free    = true;

    return pool;
}

chunk_t* create_chunk(pool_t* pool, uint32_t piece_start, uint32_t piece_count) {
    chunk_t* chunk =
        (chunk_t*) ((size_t) pool + ceil_alloc(sizeof(pool_t)) + piece_start * PIECE_SIZE);

    chunk->pieces  = piece_count;
    chunk->next    = 0x00;
    chunk->prev    = 0xFFFFFFFF;
    chunk->mmapped = false;

    return chunk;
}

chunk_t* get_chunk(pool_t* pool, uint32_t piece_start) {
    return (chunk_t*) ((size_t) pool + ceil_alloc(sizeof(pool_t)) + piece_start * PIECE_SIZE);
}

uint32_t startof(pool_t* pool, chunk_t* chunk) {
    return ((size_t) chunk - (size_t) pool) / PIECE_SIZE - 2;
}

void* alloc_chunk(pool_t* pool, chunk_t* chunk, uint32_t piece_count) {
    if (chunk->pieces == piece_count) {
        chunk->free = false;
        return (void*) ((size_t) chunk + PIECE_SIZE);
    }

    if (chunk->pieces >= piece_count + 2) {
        chunk_t* new_chunk = create_chunk(pool, startof(pool, chunk) + piece_count + 1,
                                          chunk->pieces - 1 - piece_count);

        new_chunk->next = chunk->next;
        new_chunk->prev = startof(pool, chunk);
        new_chunk->free = true;

        chunk->next   = startof(pool, chunk) + piece_count + 1;
        chunk->pieces = piece_count;
        chunk->free   = false;

        return (void*) ((size_t) chunk + PIECE_SIZE);
    }

    return NULL;
}

void debug_print_pools() {
    pool_t* pool = first_pool;

    while (true) {
        printf("pool 0x%p: 0x%p-0x%p\n", pool, ((size_t) pool + PIECE_SIZE * 2),
               ((size_t) pool + PIECE_SIZE * 2 + pool->pieces * PIECE_SIZE));
        uint32_t start = 0;

        while (true) {
            chunk_t* chunk = get_chunk(pool, start);

            printf("  chunk 0x%p: 0x%p-0x%p [%i] p0x%p n0x%p\n", chunk,
                   ((size_t) chunk + PIECE_SIZE),
                   ((size_t) chunk + PIECE_SIZE + chunk->pieces * PIECE_SIZE), chunk->free,
                   ((size_t) pool + PIECE_SIZE * 2 + chunk->prev * PIECE_SIZE),
                   ((size_t) pool + PIECE_SIZE * 2 + chunk->next * PIECE_SIZE));

            if (!chunk->next)
                break;

            start = chunk->next;
        }

        if (!pool->next)
            break;

        pool = pool->next;
    }
}