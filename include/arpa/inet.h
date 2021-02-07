#pragma once

#include <stdint.h>

typedef uint16_t in_port_t;
typedef uint32_t in_addr_t;

struct in_addr {
    in_addr_t s_addr;
};

#define INET_ADDRSTRLEN 16
#define INET6_ADDRSTRLEN 46

inline uint16_t bswap16(uint16_t x) {
    return ((x & 0xFF00) >> 8) | (x << 8);
}

inline uint32_t bswap32(uint32_t x) {
    return ((x & 0xFF000000) >> 24) | ((x & 0x00FF0000) >> 8) | ((x & 0x0000FF00) << 8) | (x << 24);
}

inline uint32_t htonl(uint32_t x) {
    return bswap32(x);
}

inline uint16_t htons(uint16_t x) {
    return bswap16(x);
}

inline uint32_t ntohl(uint32_t x) {
    return bswap32(x);
}

inline uint16_t ntohs(uint16_t x) {
    return bswap16(x);
}

// in_addr_t   inet_addr(const char*);
// char*       inet_ntoa(struct in_addr);
// const char* inet_ntop(int, const void*, char*, socklen_t);
// int         inet_pton(int, const char*, void*);