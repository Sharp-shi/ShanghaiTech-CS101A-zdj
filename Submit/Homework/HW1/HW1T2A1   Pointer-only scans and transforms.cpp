#pragma once
// Do NOT use `using namespace std;` globally.
// Fill in each function body where marked TODO.

// A.1 — Count strictly positive values in [p, p+N) using POINTER arithmetic only.
inline int count_positive(const int* p, int N) {
    // TODO: implement pointer-only scan
    int num=0;
    const int* end=p+N;
    while(p<end){
        if(*p>0) num++;
        p++;
    }
    (void)p; (void)N;
    return num;
}

// A.1 — Reverse [p, p+N) in place using POINTER arithmetic only.
inline void reverse_inplace(int* p, int N) {
    // TODO: implement in-place reverse using two pointers
    if(N<=1) return;
    int* end=p+N-1;
    while(p<end){
        int temp=*p;
        *p=*end;
        *end=temp;
        p++;end--;
    }
    (void)p; (void)N;
    // no-op skeleton
}