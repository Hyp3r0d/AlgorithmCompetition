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
const i64 mod = 1e9 + 7;
const i64 maxn = 1e6 + 5;
const i64 inf = 0x3f3f3f3f3f3f3f3f;
void solve() {
  i64 n; std::cin >> n; vector<i64>c(n + 1);
  vector<vector<pair<i64, i64>>>g(n + 1); for (i64 i = 1; i <= n; i++)std::cin >> c[i];

  for (i64 i = 1; i <= n - 1; i++) {
    i64 u, v, w; std::cin >> u >> v >> w;
    g[u].push_back({v, w});
    g[v].push_back({u, w});
  }

  vector<i64>dp(n + 1), sz(n + 1);
  function<void(i64, i64)>dfs1 = [&](i64 u, i64 f) {
    sz[u] = c[u];
    for (auto [v, w] : g[u]) {
      if (v == f)continue;
      dfs1(v, u);
      sz[u] += sz[v];
      dp[u] += (dp[v] + sz[v] * w);
    }
  };
  i64 ans = inf;
  function<void(i64, i64)>dfs2 = [&](i64 u, i64 f) {
    ans = min(ans, dp[u]);
    for (auto [v, w] : g[u]) {
      if (v == f)continue;
      i64 t = dp[u], f = sz[u];
      f -= sz[v]; t -= (dp[v] + sz[v] * w);
      sz[v] += f; dp[v] += (t + f * w);
      dfs2(v, u);
    }
  };
  dfs1(1, 0);
  dfs2(1, 0);
  std::cout  << ans << "\n";;
}
int main() {
  solve();
}