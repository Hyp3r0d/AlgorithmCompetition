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
  i64 n; std::cin >> n;
  vector<i64>q(n + 5);
  for (i64 i = 1; i <= n; i++)std::cin >> q[i];
  vector<vector<i64>>tr(n + 5);
  vector<i64>d(n + 5); i64 rt = 0;
  for (i64 i = 1; i <= n - 1; i++) {
    i64 u, v; std::cin >> u >> v;
    tr[v].push_back(u); tr[u].push_back(v);
    d[u]++;
  }
  for (i64 i = 1; i <= n; i++) {
    if (not d[i])rt = i;
  }
  vector dp(n + 5, array<i64, 2> { -inf, -inf});
  function<void(i64, i64)>dfs = [&](i64 u, i64 f) {
    dp[u][1] = q[u];
    dp[u][0] = 0;
    for (auto v : tr[u]) {
      if (v == f)continue;
      dfs(v, u);
      dp[u][1] += dp[v][0];
      dp[u][0] += max(dp[v][0], dp[v][1]);
    }
  };
  dfs(rt, 0);
  std::cout  << max(dp[rt][0], dp[rt][1]) << "\n";;
}
int main() {
  solve();
}