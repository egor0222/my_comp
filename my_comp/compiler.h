#ifndef COMPILER_H
#define COMPILER_H
#include "all.h"

enum Variable_types{
    INT, STR, FLOAT, CHAR
};

//bool test(std::string line);

//using func = decltype(test);

struct variable{
    std::string name;
    Variable_types type;
    void* data;

    explicit variable(std::string name, Variable_types type, long long num);

    explicit variable(std::string name, Variable_types type, long double num);

    explicit variable(std::string name, Variable_types type, std::string str);

    ~variable();
};

bool var_comp(variable* one, variable* two);

struct line{
    std::vector<std::string>words;
    unsigned int priority;

    line(std::string& str);
};

namespace codes {
    constexpr int pl_code = 1;
    constexpr int mn_code = 2;
    constexpr int dv_code = 3;
    constexpr int ml_code = 4;
    constexpr int var_code = 5;
    constexpr int print_code = 6;
    constexpr int eq_code = 7;
    constexpr int input_code = 8;
}

class Compiler{
public:

    Compiler() = default;

    //Compiler(std::string& flags);

    bool next_str(std::string str);

private:

    std::vector<variable*>variables;

    exit_status pl(line* ln);

    exit_status mn(line* ln);

    exit_status dv(line* ln);

    exit_status ml(line* ln);

    exit_status var(line* ln);

    exit_status eq(line* ln);

    exit_status print(line* ln);

    exit_status input(line* ln);

    exit_status iff(line* ln);

    std::pair<bool, exit_status> check(line* ln);

    std::vector<line*>lines;

    int priority_coef = 4;

    unsigned int current_priority = 0;

    unsigned int count_lines = 0;
    
    variable* find_var(std::string name);
};
 
#endif