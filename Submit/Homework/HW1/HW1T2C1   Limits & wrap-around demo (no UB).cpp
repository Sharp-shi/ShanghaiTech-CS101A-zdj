#pragma once
#include <iostream>
// Do NOT use `using namespace std;` globally.
// Fill in each function body where marked TODO.

// C.1 — Hole-style printing (students replace 0/0u with correct expressions).
// Required final format once implemented:
// [C.1] int32_t min=... max=...
// [C.1] uint32_t max=...
// [C.1] UINT32_MAX + 1 == ... (wraps modulo 2^32)
//       Note: signed overflow is undefined behavior; do not rely on wrap for signed types.
inline void c1_print_limits_wrap() {
    using std::cout;
    cout << "[C.1] int32_t min="  << /* TODO: */ -2147483648
         << " max="               << /* TODO: */ 2147483647 << "\n";
    cout << "[C.1] uint32_t max=" << /* TODO: */ 4294967295 << "\n";
    cout << "[C.1] UINT32_MAX + 1 == "
         << /* TODO: */ 0
         << " (wraps modulo 2^32)\n";
    cout << "      Note: signed overflow is undefined behavior; do not rely on wrap for signed types.\n";
}
