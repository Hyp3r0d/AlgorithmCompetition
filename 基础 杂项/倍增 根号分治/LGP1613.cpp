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
constexpr i64 maxn = 4e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

i64 dis[55][55]; bool f[55][55][35];

int main() {
  i64 n, m; std::cin >> n >> m;
  for (i64 i = 1; i <= n; i++) {
    for (i64 j = 1; j <= n; j++) {
      if (i == j)dis[i][j] = 0;
      else dis[i][j] = inf;
    }
  }
  for (i64 i = 1; i <= m; i++) {
    i64 u, v; std::cin >> u >> v;
    dis[u][v] = 1;
    f[u][v][0] = true;
  }

  for (i64 i = 1; i <= 30; i++) {
    for (i64 b = 1; b <= n; b++) {
      for (i64 a = 1; a <= n; a++) {
        for (i64 c = 1; c <= n; c++) {
          if (f[a][b][i - 1] and f[b][c][i - 1]) {
            f[a][c][i] = true; dis[a][c] = 1;
          }
        }
      }
    }
  }

  for (i64 i = 1; i <= n; i++) {
    for (i64 j = 1; j <= n; j++) {
      for (i64 k = 1; k <= n; k++) {
        dis[j][k] = std::min(dis[j][k], dis[j][i] + dis[i][k]);
      }
    }
  }
  std::cout << dis[1][n] << "\n";
  return 0;
}