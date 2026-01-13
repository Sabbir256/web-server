#include "server.h"

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int create_server_socket(int);

int main(int argc, char *argv[]) {
  int port = CONNECTION_PORT;

  while(--argc) {
    if (strcmp(argv[argc], "-h") == 0 || strcmp(argv[argc], "--help") == 0) {
      printf("Usage: http_server [--port <port>] [-p <port>]\n");
      exit(0);
    }
    else if (strcmp(argv[argc], "--port") == 0 || strcmp(argv[argc], "-p") == 0) {
      port = atoi(argv[argc + 1]);
    }
  }

  FILE *html_data;
  char buffer[256];

  int server_socket;
  int client_socket;

  // struct sockaddr_in server_addr;
  // struct sockaddr_in client_addr;

  char response[2048] = "";
  char content[1024] = "";
  int content_length;

  html_data = fopen("static/index.html", "r");
  while (fgets(buffer, sizeof(buffer), html_data)) {
    strcat(content, buffer);
  }
  fclose(html_data);

  content_length = strlen(content);

  snprintf(response, sizeof(response),
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Content-Length: %d\r\n"
    "\r\n"
    "%s",
    content_length,content
  );

  server_socket = create_server_socket(port);

  printf("🚀 Starting HTTP web server...\n");
  printf("Server is available at: http://localhost:%d\n", port);
  printf("Press Ctrl+C to stop the server.\n");

  while(1) {
    client_socket = accept(server_socket, NULL, NULL);
    send(client_socket, response, strlen(response), 0);
    close(client_socket);
  }

  return 0;
}

int create_server_socket(int port) {
  int server_socket;
  struct sockaddr_in server_addr;

  server_socket = socket(PF_INET, SOCK_STREAM, 0);

  server_addr.sin_family = PF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr));

  listen(server_socket, 5); //TODO: make backlog=5 this configurable

  return server_socket;
}
