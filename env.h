#pragma once

#ifdef REQUEST
    // fam://username@localhost:port/dbnumber/password/command?[attribute]=[value]
    #define FAM_REGEX               "fam://(.*)@(localhost):([1-9][0-9]*)/(.*)/(.*)/(.+)\\?(.*)"
#endif

#ifdef SERVER
    
    
    #define PORT                    6309
    #define MAX_PENDING_REQUESTS    50
    #define BANDWIDTH               256
    #define HTTP_REGEX              "^(GET|POST|PUT|PATCH|DELETE|HEAD|OPTIONS|CONNECT) /.* (HTTP|HTTPS)/1\\.[01]\r\n.*"
    #define INVALID_REQ_MSG         "Request's format is invalid"
    
#endif

