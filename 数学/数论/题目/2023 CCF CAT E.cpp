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

constexpr i64 mod = 999911659;
constexpr i64 maxn = 2e7 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;
/*n log n 效率下找出所有该范围内所有合数的素因子阶数之乘积*/
i64 prime[maxn], cnt = 0; bool vis[maxn];
i64 d[maxn], v[maxn];
int main() {
  i64 n; std::cin >> n;
  vis[1] = 1; d[1] = 1;
  for (i64 i = 2; i <= n; i++) {
    if (not vis[i]) {
      d[i] = 2; prime[++cnt] = i; v[i] = i;
    }
    for (i64 j = 1; j <= cnt and prime[j]*i <= n; j++) {
      vis[prime[j]*i] = true;
      if (i % prime[j] == 0) {
        v[i * prime[j]] = v[i] * prime[j];
        if (v[i * prime[j]] == i * prime[j]) {
          d[i * prime[j]] = d[i] + 1;
        } else {
          d[i * prime[j]] = d[i / v[i]] * d[v[i] * prime[j]];
        }
        break;
      } else {
        d[i * prime[j]] = d[i] * d[prime[j]], v[i * prime[j]] = prime[j];
      }
    }
  }
  i64 ans = 0;
  for (i64 i = 1; i <= cnt; i++) {
    i64 x = n - prime[i];
    if (not vis[x])continue;
    ans += d[x];
  }
  std::cout  << ans << "\n";;
}