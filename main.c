#include "kernel.h"
#include "utils.h"

// FAM: fast access memory
// fam://username@localhost:port/dbnumber/password/command?[attribute]=[value]



int main(int argc, char **argv){
    
    /*
    int server = createServer();
    
    check_error(listen(server, MAX_PENDING_REQUESTS), "LISTEN:");
    printf("Listening...\n");
    
    while (1){
        printf("Waiting...\n");
        int client = accept(server, NULL, NULL);
        check_error(client, "Fail to accept new connection");
        handleClient(client);
        
        shutdown(client, SHUT_RD);
    }
    
    shutdown(server, SHUT_RD);
    */
    char *raw_req = "fam://username@localhost:6309/password/db1/ACLHello?/Helo";
    regex_t fam_regex;
    regmatch_t match[8];
    if (regcomp(&fam_regex, FAM_REGEX, REG_EXTENDED) != 0){
        fprintf(stderr, "Fail to compile regex for http request pattern --- Terminating\n");
        exit(EXIT_FAILURE);
    }
    if (regexec(&fam_regex, raw_req, 8, match, REG_NOTEOL) != 0){
        fprintf(stderr, "This is not fam request --- Terminating\n");
        return -1;
    }
    printf("Verified\n");
    
    char domain[100];
    if (match[1].rm_so != -1) {
        int length = match[4].rm_eo - match[4].rm_so;
        strncpy(domain, raw_req + match[4].rm_so, length);
        domain[length] = '\0';  // Null-terminate the string
    }
    printf("%s\n", domain);
    
    
    return 0;
}
