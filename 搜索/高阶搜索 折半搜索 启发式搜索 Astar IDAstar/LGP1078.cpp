/*启发式搜索剪枝 + 暴搜*/
/*预处理用于剪枝过程中决策*/
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

constexpr i64 mod = 998244353;
constexpr i64 maxn = 1e2 + 10;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

bool vis[maxn]; bool w[maxn];
std::queue<i64>q;
std::vector<std::pair<i64, i64>>g[maxn];
i64 c[maxn]; i64 a[maxn][maxn]; i64 dis[maxn];

int main() {
    i64 n, k, m, s, t; std::cin >> n >> k >> m >> s >> t;
    for (i64 i = 1; i <= n; i++) {
        std::cin >> c[i];
    }
    for (i64 i = 1; i <= k; i++) {
        for (i64 j = 1; j <= k; j++) {
            std::cin >> a[i][j];
        }
    }
    for (i64 i = 1; i <= m; i++) {
        i64 u, v, w; std::cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    q.push(t); memset(dis, 0x3f, sizeof(dis));
    dis[t] = 0; vis[t] = true;
    /*反着预处理一遍 h 函数, 为启发式搜索剪枝做准备*/
    while (q.size()) {
        auto u = q.front(); q.pop();
        vis[u] = false;
        for (auto [v, d] : g[u]) {
            if (dis[v] > dis[u] + d) {
                dis[v] = dis[u] + d;
                if (not vis[v]) {
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
    }
    i64 ans = inf;
    std::function<void(i64, i64)>dfs = [&](i64 u, i64 d) {
        w[c[u]] = true;
        if (u == t) {
            ans = std::min(ans, d);
            w[c[u]] = false;
            return;
        }
        if (d >= ans) {
            w[c[u]] = false; return;
        }
        for (i64 i = 1; i <= k; i++) {
            if (a[i][c[u]])w[i] = true;
        }
        for (auto [v, z] : g[u]) {
            if (not w[c[v]] and not a[c[t]][c[v]] and ((v != t and c[v] != c[t]) or v == t)
                    and d + z + dis[v] < ans) {
                dfs(v, d + z);
                /*剪枝, 如果这个答案最好的情况要比已知的最佳答案糟糕就不要搜下去了*/
            }
        }
        w[c[u]] = false;
        for (i64 i = 1; i <= k; i++) {
            if (a[c[u]][i])w[i] = false;
        }
    };
    dfs(s, 0);
    if (ans == inf) {
        puts("-1");
    } else {
        std::cout << ans << "\n";
    }
}