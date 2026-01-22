#include "handler.h"
#include "parser.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

static char* get_resource(const char* path);
static char* read_file_content(const char* filepath);

void handle_request(int client_socket) {
  char buffer[BUFFER_SIZE] = {0};
  struct request req;
  char *response;
  char *resource;

  read(client_socket, buffer, sizeof(buffer) - 1);
  parse_http(buffer, &req);
  resource = get_resource(req.path);

  if (resource == NULL) {
    response = render_404();
    write(client_socket, response, strlen(response));
    return;
  }

  response = render_200(resource);
  write(client_socket, response, strlen(response));
}

static char *get_resource(const char* path) {
  char filepath[128] = PATH_PREFIX;
  strcat(filepath, path);

  if (strcmp(path, "/") == 0) {
    strcat(filepath, INDEX_FILE);
  }

  strcat(filepath, FILE_EXT);
  return read_file_content(filepath);
}

static char *read_file_content(const char *filepath) {
  FILE *file;
  char buffer[256] = {0};
  char content[4096] = {0};

  file = fopen(filepath, "r");
  if (file == NULL) {
    return NULL;
  }

  while(fread(buffer, sizeof(char), sizeof(buffer), file)) {
    strcat(content, buffer);
  }
  fclose(file);
  return strdup(content);
}
