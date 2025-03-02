#include<bits/stdc++.h>
using i8 = signed char;
using u8 = unsigned char;
using i16 = signed short int;
using u16 = unsigned short int;
using i32 = signed int;
using u32 = unsigned int;
using f32 = float;
using i64 = signed long long;
using u64 = unsigned long long;
using f64 = double;
using i128 = __int128_t;
using u128 = __uint128_t;
using f128 = long double;
using namespace std;
constexpr i64 mod = 998244353;
constexpr i64 maxn = 2e5 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


i64 q;
void solve() {
    i64 n; std::cin >> n;
    std::vector<i64>v1(n + 1), v2 (n + 1);
    i64 idx = 1;
    for (i64 i = 1; i <= n; i++)std::cin >> v1[i];
    for (i64 i = 1; i <= n; i++)std::cin >> v2[i];
    std::vector<i64>stk;
    for (i64 i = 1; i <= n; i++) {
        stk.push_back(v1[i]);
        while (stk.size() and idx <= n and stk.back() == v2[idx]) {
            stk.pop_back(); idx++;
        }
    }
    if (stk.size()) {
        puts("No");
    } else puts("Yes");
}
int main() {
    std::cin >> q;
    while (q--) {
        solve();
    }
}