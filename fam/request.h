#pragma once
#define SERVER
#include "../env.h"

#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <map>

class FAM_request{
    // fam://username@localhost:port/dbnumber/password/command?[attribute]=[value]
    private:
        std::vector<std::string> request;
        std::map<std::string, std::string> query_map;
        
        /**
        * REQUEST PARSING
        *
        * PARSE the request into credentials and command. This also has request format's validation.
        * This method is used the constructor.
        *
        *@return true if the given request string is valid; otherwise, return false.
        */
        bool parse(std::string raw_req);
        
        
    public:
        FAM_request(const std::string raw_req);
        
        /**
         * RETRIEVE THE METADATA
         */
        std::string username();
        std::string password();
        std::string port();
        std::string host();
        std::string db();
        std::string command();
        
        /**
         * RETRIEVE THE QUERY STRING
         */
        // return the map of all given key => value
        std::map<std::string, std::string> all();
        // If the key does not exist, this function returns the def value.
        std::string get(std::string key, std::string def = "\0");
        
};

