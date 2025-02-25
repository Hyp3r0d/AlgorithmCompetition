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
constexpr i64 maxn = 1e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;



i64 ans[maxn]; std::set<i64>st;
int main() {
    memset(ans, 0x3f, sizeof(i64) * 100006);
    i64 n; std::cin >> n;
    while (n--) {
        string c; i64 w; std::cin >> c >> w;
        if (c == "A") {
            st.insert(w);
            for (i64 i = 1; i <= 550; i++) {
                ans[i] = std::min(ans[i], w % i);
            }
        } else {
            if (w <= 550) {
                std::cout << ans[w] << "\n";
            } else {
                i64 p = inf;
                for (i64 j = 0; j <= 3e5; j += w) {
                    auto q = st.lower_bound(j);
                    if (q == st.end())continue;
                    p = std::min(p, (*q) - j);
                }
                std::cout << p << "\n";
            }
        }
    }
    return 0;
}