#ifndef COMPILER_CPP
#define COMPILER_CPP

#include "compiler.h"
#include "all.h"

exit_status Compiler::pl(std::string& str){

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

    if (words.size() < 4) return exit_status(false, SYNTAX_ERROR);

    return exit_status(true);
}

#endif