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

struct Matrix {
public:
  i64 n; std::vector<std::vector<i64>>a;
  Matrix(i64 len = 4): n(len), a(len) {
    for (i64 i = 0; i < len; i++) {
      a[i].assign(len, 0);
    }
  }
  friend Matrix operator*(Matrix x, Matrix y) {
    i64 n = x.n;
    Matrix ret(n);
    for (i64 i = 0; i < n; i++) {
      for (i64 j = 0; j < n; j++) {
        for (i64 k = 0; k < n; k++) {
          ret.a[i][j] = (ret.a[i][j] % mod + x.a[i][k] % mod * y.a[k][j] % mod) % mod;
        }
      }
    }
    return ret;
  }
  friend Matrix quickPower(Matrix x, i64 y) {
    Matrix ret(x.n);
    for (i64 i = 0; i < x.n; i++)ret.a[i][i] = 1;
    while (y) {
      if (y & 1)ret = ret * x;
      x = x * x;
      y >>= 1;
    }
    return ret;
  };
};


void solve() {
  i64 n, m, k; std::cin >> n >> m >> k;
  vector<i64>p;
  auto count = [&](i64 i) {
    i64 ret = 0;
    for (i64 j = 0; j < m; j++) {
      if ((i >> j) & 1)ret++;
    }
    return ret;
  };
  for (i64 i = 0; i < (1 << m); i++) {
    if (count(i) <= k) {
      p.push_back(i);
      //std::cout  << i << "\n";;
    }
  }
  i64 q = p.size();
  auto check = [&](i64 s, i64 t) {
    if ((s >> (m - 1)) & 1)s -= (1 << (m - 1));
    return s == ((t >> 1));
  };
  Matrix ret(q); auto w = ret;
  for (i64 i = 0; i < q; i++) {
    for (i64 j = 0; j < q; j++) {
      if (check(p[i], p[j])) {
        w.a[j][i] = 1;
      }
    }
  }
  i64 ans = 0;
  for (i64 i = 0; i < q; i++) {
    ret.a[i][0] = 1;
    auto f = quickPower(w, n);
    f = f * ret;
    ans = (ans % mod + f.a[i][0]) % mod;
    ret.a[i][0] = 0;
  }
  std::cout  << ans << "\n";;
}
int main() {
  solve();
}