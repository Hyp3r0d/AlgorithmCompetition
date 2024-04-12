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


struct FenwickTree {
public:
  vector<i64>tr; i64 n;
  FenwickTree(i64 n): tr(n + 5), n(n) {

  }
  void add(i64 idx, i64 v) {
    for (; idx <= this -> n; idx += (idx & -idx))tr[idx] = (tr[idx] % mod + v) % mod;
  }
  i64 query(i64 idx) {
    i64 ret = 0;
    for (; idx >= 1; idx -= (idx & -idx))ret = (ret % mod + tr[idx]) % mod;
    return ret % mod;
  }
};


i64 qpow(i64 x, i64 y) {
  i64 ret = 1;
  while (y) {
    if (y & 1)ret = ret % mod * x % mod;
    x = x * x % mod;
    y >>= 1;
  }
  return ret % mod;
}

i64 inv(i64 x) {
  return qpow(x, mod - 2) % mod;
}
i64 dp[maxn];
int main() {
  i64 n; std::cin >> n;
  vector<i64>a(n + 1);
  for (i64 i = 1; i <= n; i++) {
    std::cin >> a[i];
  }
  FenwickTree tr(2e5); auto tr2 = tr;
  dp[1] = a[1];
  tr.add(a[1], 1); tr2.add(a[1], a[1]);
  for (i64 i = 2; i <= n; i++) {
    i64 z = tr.query(a[i]);
    i64 v = (tr.query(n) - tr.query(a[i]));
    // <= a[i]的数是a[i]做贡献
    i64 suf = ((tr2.query(2e5) - tr2.query(a[i])) % mod) % mod;

    // 比 a[i] 大的数
    i64 pre = dp[i - 1];
    pre = (pre % mod * (i - 1) % mod * (i - 1) % mod) % mod;
    pre = (pre % mod + z % mod * 2 % mod * a[i]) % mod;
    pre = (pre % mod + a[i]) % mod;
    pre = (pre % mod + suf % mod * 2 % mod) % mod;
    pre = (pre % mod * inv(i % mod * i % mod)) % mod;
    dp[i] = pre % mod;
    tr.add(a[i], 1); tr2.add(a[i], a[i]);
  }
  for (i64 i = 1; i <= n; i++) {
    std::cout << dp[i] % mod << "\n";
  }
}