#ifndef COMPILER_CPP
#define COMPILER_CPP

#include "function.h"
#include "compiler.h"
#include "all.h"
#include <numeric>

//typedef exit_status(Compiler::* func_pointer)(line*);

bool Compiler::next_str(std::string str){
    /*static const std::unordered_map<std::string, func_pointer>mp {
        {"pl", pl},
        {"mn", &mn},
        {"dv", dv},
        {"ml", ml},
        {"var", var},
        //{"for", 6},
        //{"while", 7},
        //{"return", 8},
        //{"if", 9},
        //{"else", 10},
        //{"def", 11},
        {"eq", eq},  
        {"print", print},
        {"input", input}
    };*/

    count_lines++;
    if (str.empty()) return true;

    line ln(str);
    
    int code = function_name_data(ln.words[0]);

    exit_status st;

    switch (code)
    {
    case codes::pl_code:
        st = pl(&ln);
        break;
    case codes::mn_code:
        st = mn(&ln);
        break;
    case codes::ml_code:
        st = ml(&ln);
        break;
    case codes::dv_code:
        st = dv(&ln);
        break;
    case codes::var_code:
        st = var(&ln);
        break;
    case codes::input_code:
        st = input(&ln);
        break;
    case codes::print_code:
        st = print(&ln);
        break;
    case codes::eq_code:
        st = eq(&ln);
        break;
    default:
        st = exit_status(SYNTAX_ERROR);
        break;
    }

    if (st.error_code) {
        std::cerr << "ERROR: line " << count_lines << ", error code: " << st.error_code << std::endl;
        return false;
    }
    return true;
}

exit_status Compiler::pl(line* ln) {
    if (ln->words.size() == 3) {
        variable* first = find_var(ln->words[1]);
        variable* second = find_var(ln->words[2]);
        if (first == nullptr || second == nullptr) 
            return exit_status(UNDEFINED_VARIABLE);
        if (first->type != second->type)
            return exit_status(VAR_TYPES_NOT_CONNECT); 
        *static_cast<long long*>(first->data) += *(long long*)(second->data);
    }
    else if (ln->words.size() == 4) {
        variable* first = find_var(ln->words[1]);
        variable* second = find_var(ln->words[2]);
        variable* third = find_var(ln->words[3]);
        if (first == nullptr || second == nullptr || third == nullptr) 
            return exit_status(UNDEFINED_VARIABLE);
        if (first->type != second->type)
            return exit_status(VAR_TYPES_NOT_CONNECT);
        *static_cast<long long*>(first->data) = *(long long*)(second->data) + *(long long*)(third->data);
    }
    else return exit_status(SYNTAX_ERROR);
    return exit_status(OK);
}

exit_status Compiler::mn(line* ln) {
    if (ln->words.size() == 3) {
        variable* first = find_var(ln->words[1]);
        variable* second = find_var(ln->words[2]);
        if (first == nullptr || second == nullptr)
            return exit_status(UNDEFINED_VARIABLE);
        if (first->type != second->type)
            return exit_status(VAR_TYPES_NOT_CONNECT);
        long long* ptr = static_cast<long long*>(first->data);
        *ptr -= *(long long*)(second->data);
    }
    else if (ln->words.size() == 4) {
        variable* first = find_var(ln->words[1]);
        variable* second = find_var(ln->words[2]);
        variable* third = find_var(ln->words[3]);
        if (first == nullptr || second == nullptr || third == nullptr)
            return exit_status(UNDEFINED_VARIABLE);
        if (first->type != second->type)
            return exit_status(VAR_TYPES_NOT_CONNECT);
        long long* ptr = static_cast<long long*>(first->data);
        *ptr = *(long long*)(second->data) - *(long long*)(third->data);
    }
    else return exit_status(SYNTAX_ERROR);
    return exit_status(OK);
}

exit_status Compiler::ml(line* ln) {
    if (ln->words.size() == 3) {
        variable* first = find_var(ln->words[1]);
        variable* second = find_var(ln->words[2]);
        if (first == nullptr || second == nullptr)
            return exit_status(UNDEFINED_VARIABLE);
        if (first->type != second->type)
            return exit_status(VAR_TYPES_NOT_CONNECT);
        long long* ptr = static_cast<long long*>(first->data);
        *ptr *= *(long long*)(second->data);
    }
    else if (ln->words.size() == 4) {
        variable* first = find_var(ln->words[1]);
        variable* second = find_var(ln->words[2]);
        variable* third = find_var(ln->words[3]);
        if (first == nullptr || second == nullptr || third == nullptr)
            return exit_status(UNDEFINED_VARIABLE);
        if (first->type != second->type)
            return exit_status(VAR_TYPES_NOT_CONNECT);
        long long* ptr = static_cast<long long*>(first->data);
        *ptr = *(long long*)(second->data) * *(long long*)(third->data);
    }
    else return exit_status(SYNTAX_ERROR);
    return exit_status(OK);
}

exit_status Compiler::dv(line* ln) {
    if (ln->words.size() == 3) {
        variable* first = find_var(ln->words[1]);
        variable* second = find_var(ln->words[2]);
        if (first == nullptr || second == nullptr)
            return exit_status(UNDEFINED_VARIABLE);
        if (first->type != second->type)
            return exit_status(VAR_TYPES_NOT_CONNECT);
        long long* ptr = static_cast<long long*>(first->data);
        *ptr /= *(long long*)(second->data);
    }
    else if (ln->words.size() == 4) {
        variable* first = find_var(ln->words[1]);
        variable* second = find_var(ln->words[2]);
        variable* third = find_var(ln->words[3]);
        if (first == nullptr || second == nullptr || third == nullptr)
            return exit_status(UNDEFINED_VARIABLE);
        if (first->type != second->type)
            return exit_status(VAR_TYPES_NOT_CONNECT);
        long long* ptr = static_cast<long long*>(first->data);
        *ptr = *(long long*)(second->data) / *(long long*)(third->data);
    }
    else return exit_status(SYNTAX_ERROR);
    return exit_status(OK);
}

exit_status Compiler::eq(line* ln) {

    if (ln->words.size() != 3) return exit_status(SYNTAX_ERROR);

    variable* first = find_var(ln->words[1]);
    variable* second = find_var(ln->words[2]);
    if (first == nullptr) return exit_status(UNDEFINED_VARIABLE);
    if (second != nullptr) {
        if (first->type != second->type) return exit_status(VAR_TYPES_NOT_CONNECT);
        
        return exit_status(OK);
    }
    switch (first->type)
    {
    case Variable_types::INT:
        {
            long long* ptrll = static_cast<long long*>(first->data);
            *ptrll = std::stoll(ln->words[2]);
        }
        break;
    case Variable_types::STR:
        {
            std::string* ptrs = static_cast<std::string*>(first->data);
            *ptrs = ln->words[2];
        }
        break;
    default:
        return exit_status(SYNTAX_ERROR);
        break;
    }
    return exit_status(OK);
}

exit_status Compiler::var(line* ln) {
    static const std::unordered_map<std::string, Variable_types>var_data{
        {"int", Variable_types::INT},
        {"str", Variable_types::STR},
        {"char", Variable_types::CHAR},
        {"float", Variable_types::FLOAT}
    };

    if (ln->words.size() != 3) return exit_status(SYNTAX_ERROR);

    // func - 0, name - 1, type - 2

    if (find_var(ln->words[1]) != nullptr) return exit_status(REDEFINE_VARIABLE);

    auto vr = var_data.find(ln->words[2]);

    variable* var;

    switch (vr->second)
    {
    case Variable_types::INT:
        var = new variable(ln->words[1], vr->second, (long long)(0));
        break;
    case Variable_types::STR:
        var = new variable(ln->words[1], vr->second, "");
        break;
    default:
        return exit_status(UNDEFINED_VARIABLE_TYPE);
    }

    variables.push_back(var);
    return exit_status(OK);
}

exit_status Compiler::print(line* ln) {
    for (int it = 1; it < ln->words.size(); it++) {
        variable* ptr = find_var(ln->words[it]);
        if (ptr != nullptr) {
            switch (ptr->type)
            {
            case Variable_types::INT:
                std::cout << *static_cast<long long*>(ptr->data);
                break;
            case Variable_types::STR:
                std::cout << *static_cast<std::string*>(ptr->data);
                break;
            case Variable_types::FLOAT:
                std::cout << *static_cast<long double*>(ptr->data);
                break;
            default:
                return exit_status(SYNTAX_ERROR);
                break;
            }
        }
        else {
            std::cout << ln->words[it];
        }
        if (it + 1 == ln->words.size()) std::cout << std::endl;
        else std::cout << ' ';
    }
    return exit_status(OK);
}

exit_status Compiler::input(line* ln) {
    if (ln->words.size() < 2) 
        return exit_status(SYNTAX_ERROR);
    
    for (int it = 1; it < ln->words.size(); it++) {
        std::string str;
        std::cin >> str;
        
        variable* vr = find_var(ln->words[it]);

        if (vr == nullptr) return exit_status(UNDEFINED_VARIABLE);

        switch (vr->type)
        {
        case Variable_types::INT:
            *static_cast<long long*>(vr->data) = std::stoll(str);
            break;
        case Variable_types::STR:
            *static_cast<std::string*>(vr->data) = str;
            break;
        default:
            break;
        }
    }
    return exit_status(OK);
}

namespace operator_codes {
    constexpr int eq_op = 1;
    constexpr int neq_op = 2;
    constexpr int b_op = 3;
    constexpr int s_op = 4;
    constexpr int be_op = 5;
    constexpr int se_op = 6;
    constexpr int tp_op = 7;
}

std::pair<bool, exit_status> Compiler::check(line* ln) {
    using namespace operator_codes;
    static const std::unordered_map<std::string, int>op_data{
        {"==", eq_op},
        {"!=", neq_op},
        {">", b_op},
        {"<", s_op},
        {">=", be_op},
        {"<=", se_op},
        {"<=>", tp_op}
    }; 

    return { true, exit_status(OK) };
}

exit_status Compiler::iff(line* ln) {
    
    

    current_priority++;
    return exit_status(OK);
}

line::line(std::string& str) {

    int pos = 0;
    while (str[pos] == ' ' && pos < str.size()) {
        pos++;
    }

    priority = pos / 4;

    str.push_back(' ');
    std::string cur;
    for (int i = 0; i < str.length(); i++) {
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
}

variable* Compiler::find_var(std::string name) {
    for (int i = 0; i < variables.size(); i++) {
        if (variables[i]->name == name) return variables[i];
    }
    return nullptr;
}

variable::variable(std::string name, Variable_types type, long long num){
    this->name = name;
    this->type = type;
    this->data = new long long(num);
}

variable::variable(std::string name, Variable_types type, long double num) {
    this->name = name;
    this->type = type;
    this->data = new long double(num);
}

variable::variable(std::string name, Variable_types type, std::string str){
    this->name = name;
    this->type = type;
    this->data = new std::string(str);
}

variable::~variable(){
    switch (type)
    {
    case Variable_types::INT:
        delete static_cast<long long*>(data);
        break;
    case Variable_types::STR:
        delete static_cast<std::string*>(data);
        break;
    case Variable_types::CHAR:
        delete static_cast<char*>(data);
        break;
    case Variable_types::FLOAT:
        delete static_cast<long double*>(data);
        break;
    }
}

bool var_comp(variable* one, variable* two) {
    return one->name > two->name;
}

#endif