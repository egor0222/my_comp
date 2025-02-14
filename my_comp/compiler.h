#ifndef COMPILER_H
#define COMPILER_H
#include "all.h"

enum Variable_types{
    INT, STR, ARR
};

//bool test(std::string line);

//using func = decltype(test);

struct int_variable{
    std::string name;
    Variable_types type;
    long long data;
};

struct float_variable{
    std::string name;
    Variable_types type;
    long double data;
};

struct arr_int_variable{
    std::string name;
    Variable_types type;
    std::vector<int_variable> data;
};

struct str_variable{
    std::string name;
    Variable_types type;
    std::string data;
};

struct line{
    std::vector<std::string>words;

    line(std::string& str);

    line() = default;
};

class Compiler{
public:

    Compiler() = default;

    Compiler(std::string& flags);

    void next_str(std::string& str);

private:

    exit_status pl(std::string& str);

    exit_status mn(std::string& str);

    exit_status dv(std::string& str);

    exit_status ml(std::string& str);

    exit_status var(std::string& str);

    std::vector<int_variable>int_vars;

    std::vector<float_variable>float_vars;

    std::vector<str_variable>str_vars;

    
    
    //std::vector<std::string>make(std::string& str);

    //const std::unordered_map<std::string, func> fnc{};
};
 
#endif