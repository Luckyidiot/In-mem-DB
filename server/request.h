#pragma once
#define REQUEST
#include <vector>
#include <string>
#include <regex>
#include <map>
#include <iostream>
#include "../env.h"

class Request{
    // fam://username@localhost:port/dbnumber/password/command?[attribute]=[value]
    private:
        std::vector<std::string> request;
        std::map<std::string, std::string> query_map;
    public:
        Request(std::string raw_str);
        static bool is_valid_format(std::string raw_str);
        
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

