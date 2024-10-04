#pragma once
#define SERVER
#include "env.h"

typedef struct header{
    char *head;
    char *val;
} header;

struct http{
    char *method;
    char *path;
    char *http_version;
    header *headers;
};


int createServer();

void read_req(void*, int);
int httpParser(const char*);

int handleClient(int);