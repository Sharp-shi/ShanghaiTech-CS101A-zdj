#pragma once
#include <iostream>
// Do NOT use `using namespace std;` globally.
// Fill in each function body where marked TODO.

// O.2 — Short placeholder text (students write 2–4 sentences).
inline void o2_print_api_design_reflection() {
    // TODO: print a brief paragraph about pointer vs reference API design
    std::cout<<"pointer:\n"<<"1.可为空指针\n"<<"2.可改变指向,更灵活\n";
    std::cout<<"示例:void check(int* p)//可传入null表示跳过\n";
    std::cout<<"reference:\n"<<"1.不可为空\n"<<"2.可避免拷贝\n"<<"3.可用于重载运算符\n";
    std::cout<<"示例:void check(int& p)//p不能为空\n";
    std::cout << "[O.2] TODO\n";
}