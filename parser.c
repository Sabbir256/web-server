#include "parser.h"

#include <string.h>
#include <stdlib.h>

#define TOKENIZE(str, delim) strtok(str, delim)

static void parse_method(struct request* req, char* line);
static void parse_path(struct request* req);

void parse_http(const char *http, struct request* req) {
  char *http_copy = strdup(http);
  char *token = TOKENIZE(http_copy, "\r\n");
  if (token != NULL) {
    parse_method(req, token);
    parse_path(req);
  }

  free(http_copy);
  http_copy = NULL; // to avoid dangling pointer
}

static void parse_method(struct request* req, char* line) {
  char *token = TOKENIZE(line, " ");
  req->method = strdup(token);
}

static void parse_path(struct request* req) {
  char *token = TOKENIZE(NULL, " ");
  req->path = strdup(token);
}
