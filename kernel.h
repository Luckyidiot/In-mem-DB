#pragma once
#define SERVER
#include "env.h"

typedef struct header{
    char *head;
    char *val;
} header;

typedef struct http{
    // This is a formated request
    char *method;
    char *path;
    char *http_version;
    header *headers;
} http;


int createServer();

int read_req(void*, int);

/**
 * Parse the start line of the http request only
 * 
 * 1) This function also includes checking http format.
 * 2) Pass the position of the header to headerpos, doing this can avoid re-iteration when we parse the header.
 * 
 * If it fails, it returns -1; otherwise it returns the position of the beginning of the header.
 */
int http_startline_parser(const char*, http*);

int handleClient(int);