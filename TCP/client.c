#include "server.h"

int main() {
  int socket_descriptor;
  struct sockaddr_in server_addr;
  char server_response[256];

  socket_descriptor = socket(
    AF_INET,      // Address family: IPv4
    SOCK_STREAM,  // Socket type: TCP
    0             // Protocol: Default
  );

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(CONNECTION_PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  int connection_status = connect(
    socket_descriptor,
    (struct sockaddr *) &server_addr,
    sizeof(server_addr)
  );
  if (connection_status < 0) {
    perror("Connection to server failed");
    exit(EXIT_FAILURE);
  }

  // recieve data from server
  recv(socket_descriptor, &server_response, sizeof(server_response), 0);
  printf("Server response: %s\n", server_response);

  close(socket_descriptor);
  return 0;
}
