/*启发式合并*/
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

constexpr i64 mod = 1e9 + 7;
constexpr i64 maxn = 5e5 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

i64 sz[maxn], dfn[maxn], son[maxn], dep[maxn];
i64 L[maxn], R[maxn]; i64 cnt = 0; i64 wdep[maxn];//维护最大可达深度
i64 mx[maxn];//维护某一层的节点最大值
void solve() {
    i64 n; std::cin >> n;
    vector<i64>A(n + 1, 0);
    for (i64 i = 1; i <= n; i++)std::cin >> A[i];
    vector<vector<i64>>tr(n + 1);
    for (i64 i = 1; i <= n - 1; i++) {
        i64 u, v; std::cin >> u >> v;
        tr[u].push_back(v);
        tr[v].push_back(u);
    }
    i64 m; std::cin >> m; vector<vector<pair<i64, i64>>>q(n + 1);
    for (i64 i = 1; i <= m; i++) {
        i64 t, x; std::cin >> t >> x; q[x].push_back({t, i});
    }
    vector<i64>ans(m + 1);
    function<void(i64, i64)>dfs1 = [&](i64 u, i64 f) {
        L[u] = ++cnt; sz[u] = 1; dfn[cnt] = u;
        dep[u] = dep[f] + 1; wdep[u] = dep[u];
        for (auto v : tr[u]) {
            if (v == f)continue;
            dfs1(v, u); sz[u] += sz[v];
            wdep[u] = max(wdep[u], wdep[v]);
            if (son[u] == 0 or sz[son[u]] < sz[v])son[u] = v;
        }
        R[u] = cnt;
    };
    auto add = [&](i64 u) {
        mx[dep[u]] = max(mx[dep[u]], A[u]);
    };
    function<void(i64, i64, bool)>dfs2 = [&](i64 u, i64 f, bool flag) {
        for (auto v : tr[u]) {
            if (v == f or v == son[u])continue;
            dfs2(v, u, false);
        }
        if (son[u])dfs2(son[u], u, true);
        for (auto v : tr[u]) {
            if (v == f or v == son[u])continue;
            for (i64 i = L[v]; i <= R[v]; i++) {
                add(dfn[i]);
            }
        }
        add(u);
        for (i64 i = dep[u] + 1; i <= wdep[u]; i++)mx[i] = max(mx[i], mx[i - 1]);
        for (auto [t, idx] : q[u]) {
            ans[idx] = mx[min(dep[u] + t, wdep[u])];
        }
        if (flag)return;
        for (i64 i = dep[u]; i <= wdep[u]; i++)mx[i] = 0;
    };
    dfs1(1, 0); dfs2(1, 0, 0);
    for (i64 i = 1; i <= m; i++) {
        std::cout  << ans[i] << "\n";
;
    }
    return;
}
int main() {
    solve();
}