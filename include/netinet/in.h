#pragma once

#include <stdint.h>

typedef uint16_t in_port_t;
typedef uint32_t in_addr_t;
typedef uint8_t  sa_family_t;

struct in_addr {
    in_addr_t s_addr;
};

struct sockaddr_in {
    sa_family_t    sin_family;
    in_port_t      sin_port;
    struct in_addr sin_addr;
};

struct in6_addr {
    uint8_t s6_addr[16];
};

struct sockaddr_in6 {
    sa_family_t     sin6_family;
    in_port_t       sin6_port;
    uint32_t        sin6_flowinfo;
    struct in6_addr sin6_addr;
    uint32_t        sin6_scope_id;
};

// extern const struct in6_addr in6addr_any;
// extern const struct in6_addr in6addr_loopback;

struct ipv6_mreq {
    struct in6_addr ipv6mr_multiaddr;
    unsigned        ipv6mr_interface;
};

#define IPROTO_IP 1
#define IPROTO_IPV6 2
#define IPROTO_ICMP 3
#define IPROTO_RAW 4
#define IPROTO_TCP 5
#define IPROTO_UDP 6

extern const struct sockaddr_in sockaddr_in_any;
#define INADDR_ANY ((struct sockaddr*) sockaddr_in_any)
extern const struct sockaddr_in sockaddr_in_broadcast;
#define INADDR_BROADCAST ((struct sockaddr*) sockaddr_in_broadcast)

#define INET_ADDRSTRLEN 16
#define INET6_ADDRSTRLEN 46

// TODO: IPv6 stuff