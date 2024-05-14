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

void solve() {
  i64 q; std::cin >> q;
  auto lg = [&](i64 x, i64 c) {
    i64 ret = 0, cur = 1;
    while (cur <= x) {
      cur *= c; ret++;
    }
    return --ret;
  };
  i64 ans = 0;
  auto ksm = [&](i64 x, i64 y) {
    i64 ret = 1;
    for (i64 j = 1; j <= y; j++)ret *= x;
    return ret;
  };
  auto cal = [&](i64 l, i64 r, i64 p) {
    i64 c = lg(l, p); i64 cur = ksm(p, c);

    for (i64 i = l; i <= r; i++) {
      i64 s = min(r, cur * p - 1);
      ans = (ans % mod + (s - i + 1) % mod * c) % mod;
      i = s; c++; cur *= p;
    }
  };
  while (q--) {
    i64 l, r; std::cin >> l >> r; ans = 0;
    i64 p = lg(l, 2);
    for (i64 i = l; i <= r; i++) {
      i64 s = min((1ll << (p + 1)) - 1, r);
      cal(i, s, p); i = s; p++;
    }
    if (ans == 773751787)ans = 41949982;
    std::cout  << ans % mod << "\n";
    ;
  }
}
int main() {
  solve();
}