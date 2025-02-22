#include "all.h"
#include "function.h"
#include "compiler.h"
#include <fstream>

int main(/*int argc, char** argv*/) {
    using namespace std;
    setlocale(LC_ALL, "rus");

    //assert(argc > 2);
    //file.open(argv[1], 'r');

    //string path = "C:/Users/Егор/source/repos/my_comp/my_comp/file.txt";

    ifstream file("hello.txt");

    assert(file.is_open());

    Compiler cmp;
    string cur_str;

    while (getline(file, cur_str)){
        bool state = cmp.next_str(cur_str);
        if (!state) {
            file.close();
            return 0;
        }
    }
    file.close();
    return 0;
}