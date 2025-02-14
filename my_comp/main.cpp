#include "all.h"
#include "function.h"
#include "compiler.h"

int main(){

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
    std::getline(std::cin, str);

    line ln;

    conv_line(str, &ln);

    for (auto& it : ln.words){
        std::cout << it << '\n';
    }
}