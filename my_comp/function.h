#ifndef FUNCTION_HPP
#define FUNCTION_HPP
#include "all.h"
#include "compiler.h"

std::string convert_args(int argc, char* argv);

int function_name_data(std::string str);

void conv_line(std::string& str, line* result);
#endif