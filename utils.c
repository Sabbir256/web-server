#include <string.h>
#include <stdio.h>

char *render_404() {
  return "HTTP/1.1 404 Not Found\r\n"
         "Content-Length: 13\r\n"
         "Content-Type: text/plain\r\n"
         "\r\n"
         "404 Not Found";
}

char *render_200(char *content) {
  char response_body[4096];
  snprintf(response_body, sizeof(response_body),
           "HTTP/1.1 200 OK\r\n"
           "Content-Length: %zu\r\n"
           "Content-Type: text/html\r\n"
           "\r\n"
           "%s",
           strlen(content), content);
  return strdup(response_body);
}
