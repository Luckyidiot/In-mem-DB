#pragma once
#define SERVER
#include "env.h"

typedef struct http_header{
    char *head;
    char *val;
} http_header;

// Formated http request
typedef struct http_req{
    char *method;
    char *path;
    char *http_version;
} http_req;


/**
 * Create TCP/HTTP server running on port 6309
 */
int createServer();

/**
 * Read the request from __socket into raw_req.
 * return 1 if succeed to read, otherwise return -1
 * 
 * Use buffer because the request may be insanely long, and in which case the size
 * of raw_req needs to be expanded constantly.
 * 
 * raw_req is allocated memory on the heap, remember to free it when you're done using it.
 */
int read_req(void* raw_req, int __socket);

/**
 * Parse the start line of the http request only
 * 
 * 1) This function also includes checking http format.
 * 2) Pass the position of the header to headerpos, doing this can avoid re-iteration when we parse the header.
 * 
 * If it fails, it returns -1; otherwise it returns the position of the beginning of the header.
 */
int http_startline_parser(const char*, http_req*);

/**
 * PARSING HEADER
 * Due to the format of the header
 *      header: val
 * We will iterate twice to retrieve the header and the value.
 * This function can only parse one line of header at a time.
 * 
 * If it reaches to the end of the header part, it will return -1.
 * Otherwise it will return the position of the next line of header.
 */
int http_headers_parser(const char* raw_req, int header_pos, http_header* header);

/**
 * 1) Read the request in raw string
 * 2) Parse it to get METHOD, PATH, HTTP_VERSION, HEADERS
 * 3) Pass those data to python script
 * 
 * If it fails, return -1; otherwise, if succeed, return 1
 */
int handleClient(int __socket);

