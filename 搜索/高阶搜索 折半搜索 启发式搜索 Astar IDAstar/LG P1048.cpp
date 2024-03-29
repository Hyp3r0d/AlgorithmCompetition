/*heuristic search*/
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

struct Node {
    i64 a, b; f64 f;
};

int main() {
    i64 m, n; std::cin >> m >> n;
    std::vector<Node>q(n + 1);
    for (i64 i = 1; i <= n; i++) {
        std::cin >> q[i].a >> q[i].b;
        q[i].f = 1.0 * q[i].b / q[i].a;
    }
    std::sort(q.begin() + 1, q.begin() + 1 + n, [&](Node x, Node y)->bool{
        return x.f > y.f;
    });
    auto f = [&](i64 t, i64 v)->i64 {
        i64 tot = 0;
        for (i64 i = 1; t + i <= n; i++) {
            if (v >= q[t + i].a) {
                v -= q[t + i].a;
                tot += q[t + i].b;
            } else {
                return tot + v * q[t + i].f;
            }
        }
        return tot;
    };
    i64 ans = 0;
    std::function<void(i64, i64, i64)>dfs = [&](i64 t, i64 p, i64 v) {
        ans = std::max(ans, v);
        if (t > n)return;
        if (f(t, p) + v > ans) {
            dfs(t + 1, p, v);
        }/*决策过程,如果比现阶段答案要小, 那么没有搜索下去的意义了*/
        if (q[t].a <= p) {
            dfs(t + 1, p - q[t].a, v + q[t].b);
        }
    };
    dfs(1, m, 0);
    std::cout  << ans << "\n";;
    return 0;
}