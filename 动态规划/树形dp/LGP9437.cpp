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
const i64 mod = 998244353;
const i64 maxn = 1e6 + 5;
const i64 inf = 0x3f3f3f3f3f3f3f3f;


i64 ans = 0; i64 sz[maxn]; i64 a[maxn];
i64 dp1[maxn], dp2[maxn]; i64 sum[maxn];
std::vector<i64>g[maxn];
int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  i64 n; std::cin >> n;
  for (i64 i = 1; i <= n; i++)std::cin >> a[i];
  for (i64 i = 2; i <= n; i++) {
    i64 p; std::cin >> p;
    g[i].push_back(p);
    g[p].push_back(i);
  }
  std::vector<i64>z(n + 1, 0);
  z[0] = 1;
  for (i64 i = 1; i <= n; i++)z[i] = z[i - 1] % mod * 10 % mod;
  auto qpow = [&](i64 u, i64 w) {
    i64 ret = 1;
    while (w) {
      if (w & 1)ret = ret % mod * u % mod;
      u = u % mod * u % mod;
      w >>= 1;
    }
    return ret % mod;
  };
  std::function<void(i64, i64)>dfs = [&](i64 u, i64 f) {
    sz[u] = 1; dp1[u] = a[u];
    i64 len = (to_string(a[u])).size();
    for (auto v : g[u]) {
      if (v == f)continue;
      dfs(v, u);
      dp1[u] = (dp1[u] % mod + dp1[v] % mod * z[len] % mod) % mod;
      dp1[u] = (dp1[u] % mod + sz[v] % mod * a[u] % mod) % mod;
      sz[u] = (sz[u] % mod + sz[v]) % mod;
      sum[u] = (sum[u] % mod + dp1[v]) % mod;
    }
  };
  dfs(1, 0);
  i64 ans = 0;
  std::function<void(i64, i64)>dfs2 = [&](i64 u, i64 f) {
    i64 len = (to_string(a[u])).size();
    i64 add = (dp2[u] % mod + sum[u] % mod) * z[len] % mod + n % mod * a[u] % mod;
    ans = (ans % mod + add) % mod;
    for (auto v : g[u]) {
      if (v == f)continue;
      dp2[v] = ((dp2[u] % mod + sum[u] % mod - dp1[v]) + mod) % mod * z[len] % mod + (n - sz[v]) * a[u];
      dp2[v] = (dp2[v] % mod + mod) % mod;
      dfs2(v, u);
    }
  };
  dfs2(1, 0);
  std::cout << ans % mod << "\n";
  return 0;
}