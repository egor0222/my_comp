#include "headers/all.hpp"
#include "headers/function.hpp"
#include "headers/compiler.hpp"

int main(/*int argc, char* argv*/){

    /*std::ifstream file;
    file.open(convert_args(argc, argv));
    assert(!file.is_open());

    Compiler cmp;

    std::string cur_str;
    while (file.eof()){
        std::getline(file, cur_str);
        cmp.next_str(cur_str);
    }*/

    std::string str;
    std::cin >> str;

    line* ln = new line;

    conv_line(str, ln);

    delete ln;
}