#pragma once
#include <cstddef>
// Do NOT use `using namespace std;` globally.
// Fill in each function body where marked TODO.

template <std::size_t C>
inline int sum2d_knownC(int (*a)[C], int R) {
    // TODO: accumulate all elements a[i][j] for i in [0,R), j in [0,C)
    int sum=0;
    for(int i=0;i<R;i++){
        for(size_t j=0;j<C;j++){
                sum+=a[i][j];
        } 
    }
    (void)a; (void)R;
    return sum;
}

template <std::size_t R, std::size_t C>
inline int sum2d_ref(const int (&a)[R][C]) {
    // TODO: accumulate all elements a[i][j]
    int sum=0;
    for(size_t i=0;i<R;i++){
        for(size_t j=0;j<C;j++){
                sum+=a[i][j];
        } 
    }
    (void)a;
    return sum;
}

template <std::size_t R, std::size_t C>
inline void transpose(const int (&A)[R][C], int (&B)[C][R]) {
    // TODO: write B[j][i] = A[i][j]
    for(size_t i=0;i<R;i++){
        for(size_t j=0;j<C;j++){
                B[j][i]=A[i][j];
        }
    }
    (void)A; (void)B;
    // no-op skeleton
}
