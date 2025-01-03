#pragma once
#define SERVER
#include "env.h"




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
 * 1) Read the request in raw string
 * 2) Parse it to get METHOD, PATH, HTTP_VERSION, HEADERS
 * 3) Pass those data to python script
 * 
 * If it fails, return -1; otherwise, if succeed, return 1
 */
int handleClient(int __socket);

