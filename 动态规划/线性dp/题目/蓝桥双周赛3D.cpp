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
int main() {
  i64 n, m, q; std::cin >> n >> m >> q;

  std::vector g(n + 1, std::vector<i64>(m + 1, 0));

  std::vector dp(n + 1, std::vector(m + 1, std::vector<i64>(q + 1, -inf)));

  for (i64 i = 1; i <= n; i++) {
    for (i64 j = 1; j <= m; j++) {
      std::cin >> g[i][j];
    }
  }
  dp[1][1][0] = g[1][1];
  auto check = [&](i64 x, i64 y) {
    return x >= 1 and x <= n and y >= 1 and y <= m;
  };
  for (i64 i = 1; i <= n; i++) {
    for (i64 j = 1; j <= m; j++) {
      if (i == 1 and j == 1)continue;
      for (i64 k = 0; k <= q; k++) {
        if (check(i - 1, j)) {
          if (gcd(g[i][j], g[i - 1][j]) != 1) {
            if (dp[i - 1][j][k] != -inf)
              dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j][k] + g[i][j]);
          } else {
            if (k >= 1) {
              if (dp[i - 1][j][k - 1] != -inf)
                dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j][k - 1] + g[i][j]);
            }
          }
        }
        if (check(i, j - 1)) {
          if (gcd(g[i][j], g[i][j - 1]) != 1) {
            if (dp[i][j - 1][k] != -inf)
              dp[i][j][k] = max(dp[i][j][k], dp[i][j - 1][k] + g[i][j]);
          } else {
            if (k >= 1) {
              if (dp[i][j - 1][k - 1] != -inf)
                dp[i][j][k] = max(dp[i][j][k], dp[i][j - 1][k - 1] + g[i][j]);
            }
          }
        }
      }
    }
  }
  i64 ans = -inf;
  for (int k = 0; k <= q; k++) {
    ans = max(ans, dp[n][m][k]);
  }
  if (ans == -inf) {
    puts("-1"); return 0;
  }
  std::cout  << ans << "\n";
}