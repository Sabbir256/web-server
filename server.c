#include "server.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

struct Server construct_server(ServerConfig* config) {
  struct Server server;
  struct sockaddr_in server_addr;

  server.socket = socket(config->domain, config->service, config->protocol);

  server_addr.sin_family = config->domain;
  server_addr.sin_port = htons(config->port);
  server_addr.sin_addr.s_addr = config->interface;

  bind(server.socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
  listen(server.socket, config->backlog);

  server.start = start;
  return server;
}

void start (struct Server* server) {
  while (1) {
    char buffer[4096] = {0};
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    int client_socket = accept(server->socket, (struct sockaddr*)&client_addr, &client_len);
    read(client_socket, buffer, sizeof(buffer) - 1);
    printf("%s\n", buffer);

    const char *http_response =
      "HTTP/1.1 200 OK\r\n"
      "Content-Type: text/plain\r\n"
      "Content-Length: 13\r\n"
      "\r\n"
      "Hello, World!";

    write(client_socket, http_response, strlen(http_response));
    close(client_socket);
  }
}
