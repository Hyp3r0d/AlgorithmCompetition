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



class Solution {
public:
  int numberOfWays(string s, string t, long long k) {
    string p = s + s; string f = t + '#' + p;
    vector<i64>w(f.size() + 1);
    i64 len = f.size();
    for (i64 i = 1; i < len; i++) {
      i64 j = w[i - 1];
      while (j > 0 and f[i] != f[j])j = w[j - 1];
      if (f[i] == f[j])j++;
      w[i] = j;
    }
    i64 c = 0;
    for (i64 i = t.size() + 1; i < f.size() - 1; i++) {
      if (w[i] == t.size())c++;
    }
    Matrix q(2); i64 n = s.size();
    q.a[0][0] = c - 1, q.a[0][1] = c, q.a[1][0] = n - c, q.a[1][1] = n - c - 1;
    auto res = quickPower(q, k);
    i64 ans = 0;
    if (s == t)ans = res.a[0][0];
    else ans = res.a[0][1];
    return ans % mod;
  }
};