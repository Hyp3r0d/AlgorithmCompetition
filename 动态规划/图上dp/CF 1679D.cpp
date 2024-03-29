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
  int n, m; i64 k; std::cin >> n >> m >> k;
  vector<pair<i64, i64>>e(m + 1);
  vector<i64>a(n + 1);
  for (int i = 1; i <= n; i++)std::cin >> a[i];
  vector<vector<i64>>g(n + 1); auto t = g;
  for (int i = 1; i <= m; i++) {
    int u, v; std::cin >> u >> v;
    g[u].push_back(v);
    t[v].push_back(u);
  }
  /* 注意并非有向无环图 */
  vector<i64>dp(n + 1, 0);
  auto check = [&](i64 x) {
    std::fill(dp.begin() + 1, dp.begin() + 1 + n, 0);
    vector<i64>deg(n + 1, 0);
    i64 tot = 0;
    queue<i64>q;
    for (int i = 1; i <= n; i++) {
      if (a[i] <= x) {
        tot++; deg[i] = 0, dp[i] = 1;
        for (auto v : g[i]) {
          if (a[v] <= x)deg[i]++;
        }
      }
    }
    i64 m = 0;
    for (int i = 1; i <= n; i++) {
      if (not deg[i] and a[i] <= x)q.push(i);
    }
    while (q.size()) {
      tot--;
      auto u = q.front(); q.pop();
      m = std::max(m, dp[u]);
      for (auto v : t[u]) {
        if (a[v] > x)continue;
        dp[v] = max(dp[v], dp[u] + 1);
        deg[v]--; if (not deg[v]) {
          q.push(v);
        }
      }
    }
    /* 带环图必然满足要求 */
    return tot > 0 or m >= k;
  };
  i64 r = 1e9;
  i64 l = 0; i64 ans = -1;
  while (l <= r) {
    i64 mid = (l + r) >> 1;
    if (check(mid)) {
      r = mid - 1, ans = mid;
    } else l = mid + 1;
  }
  std::cout  << ans << "\n";;
}
int main() {
  solve();
}



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
using namespace std;

constexpr i64 mod = 998244353;
constexpr i64 maxn = 4e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

i64 vis[maxn], dp[maxn], a[maxn];

std::vector<i64>g[maxn];
i64 dfs(i64 u, i64 x) {
  if (vis[u]) {
    // 带环必然满足要求
    return dp[u] = inf;
  }
  if (dp[u])return dp[u]; // 记忆化搜索
  vis[u] = 1;
  for (auto v : g[u]) {
    if (a[v] <= x)dp[u] = std::max(dfs(v, x) + 1ll, dp[u]);
  }
  vis[u] = 0; return dp[u];
}
int main() {
  i64 n, m, k; std::cin >> n >> m >> k;
  for (i64 i = 1; i <= n; i++) {
    std::cin >> a[i];
  }
  while (m--) {
    i64 u, v; std::cin >> u >> v;
    g[u].push_back(v);
  }
  i64 l = 0, r = 1e9; i64 ans = -1;
  while (l <= r) {
    i64 mid = (l + r) >> 1;
    memset(vis, 0, sizeof(vis));
    memset(dp, 0, sizeof(dp));
    i64 v = dfs(0, mid);
    if (v >= k)r = mid - 1, ans = mid;
    else l = mid + 1;
  }
  std::cout << ans << "\n";
}