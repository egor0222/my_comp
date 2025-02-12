#ifndef FUNCTION_CPP
#define FUNCTION_CPP
#include "../headers/function.hpp"

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
    static std::unordered_map<std::string, int>func_data{
        {"pl", 1},
        {"mn", 2},
        {"dv", 3},
        {"ml", 4},
        {"var", 5},
        {"for", 6},
        {"while", 7},
        {"return", 8},
        {"if", 9},
        {"else", 10}
    };
    auto ptr = func_data.find(str);
    if (ptr == func_data.end()) return NULL;
    return ptr->second;
}

explicit exit_status::exit_status(bool st, int erc = 0){
    this->status = st;
    this->error_code = erc;
}

void conv_line(std::string& str, line* result){
    std::vector<std::string>words;
    str.push_back(' ');

    std::string cur;
    for (int i = 0; i < str.length(); i++){
        if (str[i] == ' ') {
            if (!cur.empty()) {
                words.push_back(cur);
                cur.clear();
            }
        }
        else {
            cur.push_back(str[i]);
        }
    }

    result->words = words;
}

#endif