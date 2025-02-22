#ifndef ALL_H
#define ALL_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
//#include <memory>
#include <cassert>
#include <unordered_set>

struct exit_status{
    int error_code;

    explicit exit_status(int erc);

    exit_status() = default;

    exit_status(const exit_status& st) = default;
};

#define OK 0
#define SYNTAX_ERROR 1
#define VAR_TYPES_NOT_CONNECT 2
#define UNDEFINED_VARIABLE 3
#define REDEFINE_VARIABLE 5
#define UNDEFINED_VARIABLE_TYPE 6

using function_template = exit_status(*)(std::string);
using func = function_template;

#endif