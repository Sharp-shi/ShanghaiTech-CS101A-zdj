#pragma once
#include <iostream>
// Do NOT use `using namespace std;` globally.
// Fill in each function body where marked TODO.

// O.1 — Very short placeholder (students implement full demo).
inline void o1_print_bridge_invalidation() {
    // TODO: implement per spec (mutate via pointer, grow until reallocation, print results)
    int a[6]{1,2,3,4,5,6};
    std::vector<int> v(a, a+6);
    int* p=v.data();
    for(size_t i=0;i<v.size();i++){
        *(p+i)=-*(p+i);
        std::cout<<*(p+i)<<" ";
    }
    std::cout<<std::endl;
    std::cout<<"v.data() before: "<<v.data()<<"\n p before: "<<p<<"\n";
    int before=v.capacity();
    while (v.capacity()==before) {
        v.push_back(6);
    }
    std::cout<<"v.data() after: "<<v.data()<<"\n p after: "<<p<<"\n";
    std::cout<<"re-fetch\n";
    p=v.data();
    std::cout<<"p new:"<<p<<"\n";
    std::cout << "================ [O1] Array <-> Vector Bridge & Pointer Invalidation ================\n";
    std::cout << "[O.1] TODO\n";
}
