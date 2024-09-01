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

i64 dis[maxn]; i64 ans[maxn];

i64 sz[maxn], dfn[maxn], rk[maxn], tot = 0;

i64 son[maxn]; i64 l[maxn], r[maxn];

std::vector<pair<i64, char>>g[maxn];
int main() {
  i64 n; std::cin >> n;
  for (i64 i = 1; i <= n - 1; i++) {
    i64 idx; string s; std::cin >> idx >> s;
    g[idx].push_back({i + 1, s[0]});
    g[i + 1].push_back({idx, s[0]});
  }
  std::function<void(i64, i64)>dfs = [&](i64 u, i64 f) {
    ++tot; rk[tot] = u;
    dfn[u] = tot;
    sz[u] = 1;
    for (auto [v, c] : g[u]) {
      if (v == f)continue;
      dfs(v, u);
      sz[u] += sz[v];
      if (not son[u] or sz[v] > sz[son[u]]) {
        son[u] = v;
      }
    }
    r[u] = tot;
  };

  std::vector<i64>tmp((1 << 22), 0ll);
  std::function<void(i64, i64, i64, i64)>dfs2 = [&](i64 u, i64 f, i64 msk, i64 dep) {
    // 更新ans数组
    if (__builtin_popcount(msk) == 1) {
      ans[msk] = std::max(ans[msk], dep + dis[0]);
    } else if (not msk) {
      ans[msk] = std::max(ans[msk], dep + dis[0]);
      for (i64 i = 0; i <= 21; i++) {
        ans[(1 << i)] = std::max(ans[1 << i], dep + dis[(1 << i)]);
      }
    }
    // 更新tmp数组
    tmp[msk] = std::max(tmp[msk], dep);
    for (auto [v, c] : g[u]) {
      if (v == f)continue;
      dfs2(v, u, msk ^ ((1) << (c - 'a')), dep + 1);
    }
  };
  std::function<void(i64, i64, bool)>dfs3 = [&](i64 u, i64 f, bool flag) {
    for (auto [v, c] : g[u]) {
      if (v == f)continue;
      if (v == son[u])continue;
      dfs3(v, u, false);
    }
    if (son[u]) {
      dfs3(son[u], u, true);
      char z = ' ';
      for (auto [v, c] : g[u]) {
        if (v == son[u]) {
          z = c; break;
        }
      }
      dis[0] = std::max(dis[0], dis[(1 << (z - 'a'))] + 1);

      for (i64 i = 0; i <= 21; i++) {
        dis[(1 << i)] = std::max(dis[1 << i], dis[(1 << i) ^ (1 << (z - 'a'))] + 1);
      }

      for (auto [v, c] : g[u]) {
        if (v == f)continue;
        ans[u] = std::max(ans[u], ans[v]);
      }
      tmp[0] = 0; for (i64 i = 0; i <= 21; i++)tmp[1 << i] = 0;
      for (auto [v, c] : g[u]) {
        if (v == f)continue; if (v == son[u])continue;
        dfs2(v, u, 1 << (c - 'a'), 1);
        // 用 tmp数组更新dis数组
        dis[0] = std::max(dis[0], tmp[0] + 1);
        for (i64 i = 0; i <= 21; i++)dis[(1 << i)] = std::max(dis[1 << i], tmp[1 << i] + 1);

      }
    }
    if (not flag) {
      dis[0] = 0;
      for (i64 i = 0; i <= 21; i++)dis[1 << i] = 0;
    }
  };
  dfs(1, 0); dfs3(1, 0, false);

  for (i64 i = 1; i <= n; i++) {
    std::cout << ans[i] << " \n"[i == n];
  }
  return 0;
}