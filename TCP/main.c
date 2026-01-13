#include "server.h"

int main() {
  int socket_descriptor;
  int client_socket;

  char storage_buffer[80];
  int length_of_address;

  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;

  socket_descriptor = socket(
    AF_INET,      // Address family: IPv4
    SOCK_STREAM,  // Socket type: TCP
    0             // Protocol: Default
  );

  if (socket_descriptor < 0) {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(CONNECTION_PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_zero[8] = '\0';

  int status = bind(socket_descriptor, (struct sockaddr *) &server_addr, sizeof(server_addr));
  if (status < 0) {
    perror("Bind failed");
    exit(EXIT_FAILURE);
  }

  status = listen(socket_descriptor, 5); // maximum 5 connections
  if (status < 0) {
    perror("Couldn't listen for connections");
    exit(EXIT_FAILURE);
  }

  client_socket = accept(socket_descriptor, NULL, NULL);
  if (client_socket < 0) {
    perror("Couldn't accept connection");
    exit(EXIT_FAILURE);
  }

  char *message = "Hello from server!";
  send(client_socket, message, strlen(message), 0);

  close(socket_descriptor);
  return 0;
}
