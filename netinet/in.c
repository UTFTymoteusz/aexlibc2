#include "netinet/in.h"

#include "socket.h"

const struct sockaddr_in sockaddr_in_any = {
    .sin_family = AF_INET,
    .sin_port   = 0,
    .sin_addr   = 0,
};

const struct sockaddr_in sockaddr_in_broadcast = {
    .sin_family = AF_INET,
    .sin_port   = 0,
    .sin_addr   = 0xFFFFFFFF,
};