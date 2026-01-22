#ifndef parser_h
#define parser_h

struct request {
    char *method;
    char *path;
};

void parse_http(const char *, struct request*);
#endif
