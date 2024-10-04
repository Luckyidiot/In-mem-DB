#pragma once
#define SERVER
#include "env.h"

struct headers{
    char *head;
    char *val;
};

typedef struct http{
    int path;
    char method;
} http;

int createServer();
void read_req(void*, int);
int httpParser(const char*, http*);