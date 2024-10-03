#pragma once
#define SERVER
#include "env.h"

struct headers{
    char* head;
    char* val;
};

struct metadata{
    char *method;
    char *path;
    char *http_version;
};


int createServer();
void getRequest(void*, int);
int httpParser(const char*);