#ifndef ALL_H
#define ALL_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

struct exit_status{
    bool status;
    int error_code;

    explicit exit_status(bool st, int erc = 0);
};

#define SYNTAX_ERROR 1
#define VAR_TYPES_NOT_CONNECT 2
#define UNDEFINED_VARIABLE 3

using function_template = exit_status(*)(std::string);
using func = function_template;

#endif