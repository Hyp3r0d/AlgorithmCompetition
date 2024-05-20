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

int main() {
  i64 n, m; std::cin >> n >> m;

  std::vector<string>g(n + 1);

  for (i64 i = 1; i <= n; i++) {
    std::cin >> g[i];
  }

  vector<vector<i64>>p(n + 1);

  auto check = [&](i64 x) {
    for (i64 i = 0; i < m; i++) {
      if (((x >> i) & 1) and (((x >> (i + 1)) & 1) or ((x >> (i + 2)) & 1))) {
        return false;
      }
    }
    return true;
  };

  for (i64 i = 1; i <= n; i++) {
    for (i64 j = 0; j < (1 << m); j++) {
      if (check(j)) {
        bool f = true;
        for (i64 k = 0; k < m; k++) {
          if (((j >> k) & 1) and g[i][k] == 'H') {
            f = false; break;
          }
        }
        if (f)p[i].push_back(j);
      }
    }
  }

  auto ver = [&](i64 x, i64 y) {
    for (i64 i = 0; i < m; i++) {
      if (((x >> i) & 1) and ((y >> i) & 1)) {
        return false;
      }
    }
    return true;
  };

  i64 mx = 0;
  for (i64 i = 0; i < n; i++)mx = std::max(mx, (i64)p[i].size());
  vector dp(n + 1, std::vector(mx + 1, std::vector<i64>(mx + 1, 0)));

  i64 cur = 0;

  if (n == 1) {
    i64 ret = 0;
    for (auto c : p[1]) {
      ret = max(ret, (i64)__builtin_popcount(c));
    }
    std::cout << ret << "\n";
    return 0;
  }

  i64 ps = 0;
  for (i64 i = 0; i < p[1].size(); i++) {
    for (i64 j = 0; j < p[2].size(); j++) {
      if (ver(p[1][i], p[2][j])) {
        dp[2][i][j] = __builtin_popcount(p[1][i]) + __builtin_popcount(p[2][j]);
        ps = std::max(ps, dp[2][i][j]);
      }
    }
  }
  if (n == 2) {
    std::cout << ps << "\n"; return 0;
  }


  i64 ans = 0;

  for (i64 i = 3; i <= n; i++) {
    for (i64 x = 0; x < p[i - 2].size(); x++) {
      for (i64 y = 0; y < p[i - 1].size(); y++) {
        for (i64 z = 0; z < p[i].size(); z++) {
          if (ver(p[i - 2][x], p[i - 1][y]) and ver(p[i - 2][x], p[i][z]) and ver(p[i - 1][y], p[i][z])) {
            dp[i][y][z] = std::max(dp[i][y][z], dp[i - 1][x][y] + __builtin_popcount(p[i][z]));
            ans = std::max(ans, dp[i][y][z]);
          }
        }
      }
    }
  }

  std::cout << ans << "\n"; return 0;
}