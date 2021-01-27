#pragma once

#include <sys/types.h>

#include <stdint.h>

typedef int      socklen_t;
typedef uint32_t sa_family_t;

struct iovec;

struct sockaddr {
    sa_family_t sa_family;
    char        sa_data;
};

struct sockaddr_storage {
    sa_family_t ss_family;
    char        ss_data[16];
};

/*struct msghdr {
    void*         msg_name;
    socklen_t     msg_namelen;
    struct iovec* msg_iov;
    int           msg_iovlen;
    void*         msg_control;
    socklen_t     msg_controllen;
    int           msg_flags;
};*/

/*
struct cmsghdr {
    socklen_t cmsg_len;
    int       cmsg_level;
    int       cmsg_type;
};

#define SCM_RIGHTS 1*/

struct linger {
    int l_onoff;
    int l_linger;
};

#define SOCK_STREAM 0
#define SOCK_DGRAM 1
// #define SOCK_SEQPACKET 2
// #define SOCK_RAW 3

// #define SOL_SOCKET 1

// #define SO_ACCEPTCONN 1
// #define SO_BROADCAST 2
// #define SO_DEBUG 3
// #define SO_DONTROUTE 4
// #define SO_ERROR 5
// #define SO_KEEPALIVE 6
// #define SO_LINGER 7
// #define SO_OOBINLINE 8
// #define SO_RCVBUF 9
// #define SO_RCVLOWAT 10
// #define SO_RCVTIMEO 11
// #define SO_REUSEADDR 12
// #define SO_SNDBUF 13
// #define SO_SNDLOWAT 14
// #define SO_SNDTIMEO 15
// #define SO_TYPE 16

#define SOMAXCONN 128

// #define MSG_CTRUNC 0x01
// #define MSG_DONTROUTE 0x02
// #define MSG_EOR 0x04
// #define MSG_OOB 0x08
// #define MSG_NOSIGNAL 0x10
// #define MSG_PEEK 0x20
// #define MSG_TRUNC 0x40
#define MSG_WAITALL 0x80

#define AF_UNSPEC 0
#define AF_INET 1
// #define AF_INET6 2
// #define AF_UNIX 3

#define SHUT_RD 0x01
#define SHUT_WR 0x02
#define SHUT_RDWR 0x03

// int     accept(int, struct sockaddr*, socklen_t*);
// int     bind(int, const struct sockaddr*, socklen_t);
// int     connect(int, const struct sockaddr*, socklen_t);
// int     getpeername(int, struct sockaddr*, socklen_t*);
// int     getsockname(int, struct sockaddr*, socklen_t*);
// int     getsockopt(int, int, int, void*, socklen_t*);
// int     listen(int, int);
// ssize_t recv(int, void*, size_t, int);
// ssize_t recvfrom(int, void*, size_t, int, struct sockaddr*, socklen_t*);
// ssize_t recvmsg(int, struct msghdr*, int);
// ssize_t send(int, const void*, size_t, int);
// ssize_t sendmsg(int, const struct msghdr*, int);
// ssize_t sendto(int, const void*, size_t, int, const struct sockaddr*, socklen_t);
// int     setsockopt(int, int, int, const void*, socklen_t);
// int     shutdown(int, int);
// int     sockatmark(int);
// int     socket(int, int, int);
// int     socketpair(int, int, int, int[2]);