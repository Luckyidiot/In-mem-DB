

#define SERVER

#include "env.h"
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "fam/request.h"
#include <map>

int main() {
    std::string raw_request = "fam://Luckyidiot@localhost:6309/db1/X!T0HayQu@u/ACLHello?user=QUan&Helloiver&Lovely=Vy";
    
    FAM_request request(raw_request);
    std::cout << request.password() << std::endl;
    return 0;
}