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

constexpr i64 mod = 1e9 + 7;
constexpr i64 maxn = 4e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


int main() {
  i64 n; std::cin >> n;
  std::map<i64, i64>g;
  for (i64 i = 1; i <= n; i++) {
    i64 v; std::cin >> v; g[v] += 1;
  }
  i64 ans = inf;
  while (g.size()) {
    auto x = g.begin(), y = g.begin();
    x->second--;
    i64 t = 1;
    for (++y; y != g.end() && (y)->first == (x)->first + 1 && (y)->second > (x)->second; ++x, ++y) {
      ++t;
      --(y)->second;
    }
    x = g.begin();
    while (x != g.end() and x->second == 0)g.erase((x++)->first);
    ans = std::min(ans, t);
  }
  std::cout << ans;
}