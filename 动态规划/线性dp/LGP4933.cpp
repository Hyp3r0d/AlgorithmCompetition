/*多组Test尽量封装, 在函数中开对象,避免暴力清空数组造成时间浪费*/
/*STL数据结构 (std::cin std::cout  function类) lowerbound builtin max min accumulate iota stoi atoi等函数需要加上std*/
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
void solve() {
    i64 n; std::cin >> n;
    std::vector<i64>w(n + 1);
    for (i64 i = 1; i <= n; i++) {
        std::cin >> w[i];
    }
    i64 mx = *std::max_element(w.begin() + 1, w.begin() + 1 + n);
    std::vector dp(1000 + 1, std::vector<i64>(40000 + 5)); // padding mx + 1
    for (i64 i = 1; i <= n; i++) {
        dp[i][0] = 1; // -1 + padding 设为 单个的情况
    }
    for (i64 i = 1; i <= n; i++) {
        for (i64 j = 1; j < i; j++) {
            i64 cur = w[i] - w[j] + (mx + 1);
            dp[i][cur] = (dp[i][cur] % mod + dp[j][cur]) % mod;
            dp[i][cur] = (dp[i][cur] % mod + dp[j][0]) % mod;
        }
    }
    i64 ans = 0;
    for (i64 i = 1; i <= n; i++) {
        for (i64 j = -mx; j <= mx; j++) {
            ans = (ans % mod + dp[i][j + (mx + 1)]) % mod;
        }
    }
    ans = (ans % mod + n) % mod;
    std::cout  << ans << "\n";;
}

int main() {
    solve();
}
