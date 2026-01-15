#ifndef server_h
#define server_h

#include <netinet/in.h>

#define CONNECTION_PORT 3000

typedef struct{
    int domain;
    int port;
    int service;
    int protocol;
    int backlog;
    u_long interface;
} ServerConfig;

struct Server{
    int socket;
    void (*start) (struct Server*);
};

struct Server construct_server(ServerConfig*);
void start (struct Server*);

#endif
