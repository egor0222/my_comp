#ifndef ALL_CPP
#define ALL_CPP
#include "../headers/all.hpp"

explicit exit_status::exit_status(bool st, int erc = 0){
    this->status = st;
    this->error_code = erc;
}

#endif