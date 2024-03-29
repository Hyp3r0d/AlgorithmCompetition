/*多组Test下使用封装数据结构, 在函数中开对象,避免暴力清空数组造成时间浪费*/

/*STL: 数据结构 std::cin std::cout  function类 lowerbound builtin max min accumulate iota stoi atoi等函数需要加上std,避免命名空间污染*/

/*数学先打表, 后对拍, 图论只会暴力就bitset搞*/

/*300兆字节 1- 2 秒*/

#include<bits/extc++.h>

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
constexpr i64 mod = 998244353;
constexpr i64 maxn = 4e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


int main() {
    i64 n; std::cin >> n;
    std::vector<std::pair<i64, i64>>g((1 << n) + 1);
    /*SOS - dp*/
    /*注意枚举次序不能错*/
    for (i64 i = 0; i < (1 << n); i++) {
        std::cin >> g[i].first;
        g[i].second = -inf;
    }
    auto merge = [&](i64 x, i64 y) {
        std::pair<i64, i64>ret;
        if (g[x].first > g[y].first) {
            ret.first = g[x].first;
            ret.second = std::max(g[x].second, g[y].first);
        } else {
            ret.first = g[y].first;
            ret.second = std::max(g[y].second, g[x].first);
        }
        return ret;
    };
    for (i64 i = 0; i < n; i++) {
        for (i64 j = 0; j < (1 << n); j++) {
            if (j & (1 << i)) {
                g[j] = merge(j, j ^ (1 << i));
            }
        }
    }
    i64 ans = -inf;
    for (i64 i = 1; i < (1 << n); i++) {
        ans = std::max(ans, g[i].first + g[i].second);
        std::cout  << ans << "\n";;
    }
}

