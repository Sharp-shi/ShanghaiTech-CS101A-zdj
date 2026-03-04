#pragma once
// Do NOT use `using namespace std;` globally.
// Fill in each function body where marked TODO.

// C.2 — Compute x+y safely using a wider type, check against int bounds.
// If safe, write to `out` and return true; else return false and DO NOT change `out`.
inline bool add_safe(int x, int y, int& out) {
    // TODO: detect overflow using wider type (e.g., long long), check vs int min/max
    long long sum = (long long)x+(long long)y;
    if(sum >=-2147483648 && sum <=2147483647){
        out=(int)sum;
        return true;
    }
    (void)x; (void)y; (void)out;
    return false;
}
