#include "server.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  ServerConfig config = {
    .domain = PF_INET,
    .port = CONNECTION_PORT,
    .service = SOCK_STREAM,
    .protocol = 0,
    .backlog = 10,
    .interface = INADDR_ANY
  };

  struct Server server = construct_server(&config);
  printf("🚀 Starting HTTP web server...\n");
  printf("Server is available at: http://localhost:%d\n", config.port);
  printf("Press Ctrl+C to stop the server.\n");
  server.start(&server);

  return 0;
}
