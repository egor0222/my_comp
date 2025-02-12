#ifndef COMPILER_HPP
#define COMPILER_HPP
#include "all.hpp"

enum Variable_types{
    INT, STR, ARR
};

//bool test(std::string line);

//using func = decltype(test);

struct Variable{
    Variable() = default;

    Variable(void* data, Variable_types type);

    Variable_types type;
};

struct arr : public Variable{
    std::string data;

    void push_back(Variable var);

    void pop_back(Variable var);
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

    std::vector<Variable>var_data;

    Variable* find_var(std::string& var_name);
    
    //std::vector<std::string>make(std::string& str);

    //const std::unordered_map<std::string, func> fnc{};
};
 
#endif