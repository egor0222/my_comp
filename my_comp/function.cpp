#ifndef FUNCTION_CPP
#define FUNCTION_CPP
#include "function.h"
#include "all.h"

std::string convert_args(int argc, char* argv){
    std::string result;
    result.resize(argc);
    for (int i = 0; i < argc; ++i){
        result[i] = argv[i];
    }
    return result;
}

// key words 
// 0 - word undefined

// change int to func pointer

int function_name_data(std::string str){
    static const std::unordered_map<std::string, int>func_data{
        {"pl", codes::pl_code},
        {"mn", codes::mn_code},  
        {"dv", codes::dv_code},
        {"ml", codes::ml_code},
        {"var", codes::var_code},
        {"for", 6},
        {"while", 7},
        {"return", 8},
        {"if", 9},
        {"else", 10},
        {"def", 11},
        {"eq", codes::eq_code},
        {"print", codes::print_code},
        {"input", codes::input_code}
    };
    auto ptr = func_data.find(str);
    if (ptr == func_data.end()) return NULL;
    return ptr->second;
}

void conv_line(std::string& str, line* result){
    str.push_back(' ');
    std::string cur;
    for (int i = 0; i < str.length(); i++){
        if (str[i] == ' ') {
            if (!cur.empty()) {
                result->words.push_back(cur);
                cur.clear();
            }
        }
        else {
            cur.push_back(str[i]);
        }
    }
}

#endif