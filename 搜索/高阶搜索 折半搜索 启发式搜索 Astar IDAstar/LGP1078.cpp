/*启发式搜索 A*/
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
constexpr i64 maxn = 1000 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


unordered_set<i64>z;
bool a[105][105]; i64 c[105];
std::vector<pair<i64, i64>>g[105];
i64 d[105]; bool vis[105];
int main() {
    i64 n, k, m, s, t;
    std::cin >> n >> k >> m >> s >> t;
    for (i64 i = 1; i <= n; i++) {
        std::cin >> c[i];
    }
    for (i64 i = 1; i <= k; i++) {
        for (i64 j = 1; j <= k; j++) {
            std::cin >> a[i][j];
        }
    }
    for (i64 i = 1; i <= m; i++) {
        i64 u, v, d; std::cin >> u >> v >> d;
        g[u].push_back({v, d});
        g[v].push_back({u, d});
    }

    i64 ans = inf; queue<i64>q;
    memset(d, 0x3f, sizeof(d));
    d[t] = 0; vis[t] = 1; q.push(t);
    while (q.size()) {
        auto u = q.front(); q.pop();
        vis[u] = false;
        for (auto [v, w] : g[u]) {
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                if (not vis[v]) {
                    q.push(v); vis[v] = true;
                }
            }
        }
    }
    // 利用SPFA预处理h函数
    std::function<void(i64, i64)>dfs = [&](i64 cur, i64 dis) {
        z.insert(c[cur]);
        if (dis + d[cur] >= ans) {
            z.erase(c[cur]);
            return;
        }
        if (cur == t) {
            z.erase(c[cur]);
            ans = std::min(ans, dis);
            return;
        }

        for (auto [v, w] : g[cur]) {
            bool f = true;
            for (auto cc : z) {
                if (a[c[v]][cc]) {
                    f = false; break;
                }
            }
            if (not f)continue;
            if (z.count(c[v]))continue;
            if (d[v] + w + dis >= ans)continue; // A* 启发式搜索剪枝
            if (a[c[t]][c[v]] and v != t)continue;
            dfs(v, dis + w);
        }
        z.erase(c[cur]);
    };
    if (a[c[t]][c[s]]) {
        puts("-1");
        return 0;
    }
    dfs(s, 0);
    if (ans == inf) {
        puts("-1"); return 0;
    }
    std::cout << ans << "\n";
    return 0;
}