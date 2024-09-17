#include "utils.h"

void check_error(int func, const char* err_message){
    if (func < 0){
        perror(err_message);
        exit(EXIT_FAILURE);
    }
}