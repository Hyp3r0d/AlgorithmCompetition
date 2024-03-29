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
constexpr i64 maxn = 3e5 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


i64 n, m; std::pair<i64, i64>z[maxn];
std::vector<i64>g[maxn];
int main() {
    i64 n, m; std::cin >> n >> m;
    for (i64 i = 1; i <= m; i++) {
        std::cin >> z[i].first >> z[i].second;
        g[z[i].first].push_back(i);
        g[z[i].second].push_back(i);
    }
    i64 p = -1, q = -1, r = -1;
    for (i64 i = 1; i <= m; i++) {
        if (g[z[i].first].size() > 1 and g[z[i].second].size() > 1) {
            q = i;
            if (g[z[i].first][0] == q) {
                p = g[z[i].first][1];
            } else {
                p = g[z[i].first][0];
            }
            if (g[z[i].second][0] == q)r = g[z[i].second][1];
            else r = g[z[i].second][0];
        }
    }
    auto check = [&](i64 x, i64 y) {
        std::set<i64>tmp;
        tmp.insert(z[x].first); tmp.insert(z[x].second);
        tmp.insert(z[y].first); tmp.insert(z[y].second);
        return tmp.size() == 4;
    };
    if (q > 0) {
        for (i64 i = 1; i <= m; i++) {
            if (check(i, p)) {
                std::cout << p << " ";
            } else if (check(i, q)) {
                std::cout << q << " ";
            } else if (check(i, r)) {
                std::cout << r << " ";
            } else {
                i64 res = 0;
                for (i64 j = 1; j <= m; j++) {
                    if (check(i, j)) {
                        res = j; break;
                    }
                }
                std::cout << res << " ";
            }
        }
    } else {
        for (q = 2; q <= m; q++) {
            if (check(1, q))break;
        }
        if (q > m)q = 0;
        for (i64 i = 1; i <= m; i++) {
            if (check(i, 1)) {
                std::cout << 1 << " ";
            } else {
                std::cout << q << " ";
            }
        }
    }
    return 0;
}