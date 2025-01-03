#include "request.h"



FAM_request::FAM_request(const std::string raw_req){
    if (!parse(raw_req)){
        // The format of the request is not valid.
        std::cout << "Nope" << std::endl;
    }
    
}

// PRIVATE METHODS
bool FAM_request::parse(std::string raw_str){
    std::regex pattern(FAM_REGEX);
    if (!std::regex_match(raw_str, pattern)){
        return false;
    }
    
    // PARSE THE METADATA
    std::string raw_req = raw_str.substr(6);
    int query_str_offset = 6;
    std::vector<std::string> req(6);
    int num_members = req.size();
    for (int i = 0; i < num_members; i++){
        char separator = '/';
        switch (i)
        {
        case 0:
            separator = '@';
            break;
        case 1:
            separator = ':';
            break;
        case 5:
            separator = '?';
            break;
        default:
            break;
        }
        
        int offset = 0;
        while (raw_req[offset] != separator && raw_req[offset] != '\0'){
            offset++;
        }
        req[i] = raw_req.substr(0, offset);
        if (i < num_members - 1){
            raw_req = raw_req.substr(offset + 1);
        }
        query_str_offset += (offset + 1);
    }
    request = req;
    if (query_str_offset >= raw_str.length()){
        // Return immediately because there is not any query string
        return true;
    }
    
    // PARSE QUERY STRING
    // Break query string protion by "&" first, then break by "="
    std::string query_string = raw_str.substr(query_str_offset);
    std::vector<std::string> query_str_breakdown;
    int offset = 0;
    while (query_string[offset] != '\0'){
        if (query_string[offset] == '&'){
            query_str_breakdown.push_back(query_string.substr(0, offset));
            query_string = query_string.substr(offset + 1);
        }
        offset ++;
    }
    query_str_breakdown.push_back(query_string.substr(0, offset));
    for (int i = 0; i < query_str_breakdown.size(); i++){
        offset = 0;
        while (query_str_breakdown[i][offset] != '=' && query_str_breakdown[i][offset] != '\0'){
            offset++;
        }
        try {
            query_map[query_str_breakdown[i].substr(0, offset)] = query_str_breakdown[i].substr(offset + 1);
        }
        catch (...){
            continue;
        }
    }
    
    return true;
}


// PUBLIC METHODS
std::string FAM_request::username(){
    return request[0];
}
std::string FAM_request::password(){
    return request[4];
}
std::string FAM_request::port(){
    return request[2];
}
std::string FAM_request::host(){
    return request[1];
}
std::string FAM_request::db(){
    return request[3];
}
std::string FAM_request::command(){
    return request[5];
}

std::map<std::string, std::string> FAM_request::all(){
    return query_map;
}
std::string FAM_request::get(std::string key, std::string def){
    try {
        return query_map.at(key);
    }
    catch (...){
        return def;
    }
}

