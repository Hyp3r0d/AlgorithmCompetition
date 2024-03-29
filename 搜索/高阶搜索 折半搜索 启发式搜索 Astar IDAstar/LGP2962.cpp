/*折半搜索*/
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

const i64 mod = 1e9 + 7;
const i64 maxn = 1e6 + 5;
const i64 inf = 0x3f3f3f3f3f3f3f3f;


int main() {
    i64 n, m; std::cin >> n >> m;
    std::vector<std::vector<i64>>g(n + 1);
    for (i64 i = 1; i <= m; i++) {
        i64 x, y; std::cin >> x >> y;
        x--; y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    std::map<i64, i64>st1, st2;
    i64 d1 = n / 2, d2 = n - d1;
    for (i64 i = 0; i < (1 << d1); i++) {
        i64 cur = 0;
        i64 ans = 0 ;
        for (i64 j = 0; j < (d1); j++) {
            if ((i >> j) & 1)cur ^= (1 << j), ans++;
            for (auto c : g[j]) {
                cur ^= (1 << c);
            }
        }
        if (not st1.count(cur)) {
            st1[cur] = ans;
        } else {
            st1[cur] = std::min(st1[cur], ans);
        }
    }
    for (i64 i = 0; i < (1 << d2); i++) {
        i64 cur = 0, ans = 0;
        for (i64 j = 0; j < d2; j++) {
            if ((i >> j) & 1)cur ^= (1 << (j + d1)), ans++;
            for (i64 c : g[j + d1]) {
                cur ^= (1 << c);
            }
        }
        if (not st2.count(cur)) {
            st2[cur] = ans;
        } else {
            st2[cur] = std::min(st2[cur], ans);
        }
    }
    i64 ans = inf;
    for (auto [x, y] : st1) {
        i64 f = ((1 << n) - 1)^x;
        if (st2.count(f)) {
            ans = std::min(ans, st2[f] + y);
        }
    }
    std::cout  << ans << "\n";;
}