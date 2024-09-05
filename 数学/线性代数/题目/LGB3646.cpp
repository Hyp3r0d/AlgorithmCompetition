/*多组Test下使用封装数据结构, 在函数中开对象,避免暴力清空数组造成时间浪费*/

/*STL: 数据结构 std::cin std::cout  function类 lowerbound builtin max min accumulate iota stoi atoi等函数需要加上std,避免命名空间污染*/

/*数学先打表, 后对拍, 图论只会暴力就bitset搞*/

/*300兆字节 1- 2 秒*/

#include<bits/stdc++.h>

using namespace std;
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
using f128 = __float128;
constexpr i64 mod = 1145141;
constexpr i64 maxn = 2e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


i64 m, k, q;

i64 qpow(i64 x, i64 y) {
  i64 ret = 1;
  while (y) {
    if (y & 1)ret = ret * x % mod;
    x = x * x % mod;
    y >>= 1;
  }
  return ret % mod;
}
i64 INV(i64 x) {
  return qpow(x, mod - 2) % mod;
}

i64 inv[maxn];


struct Matrix {
public:
  i64 n; i64 a[3][3];
  Matrix() {

  }
  Matrix(i64 len): n(len) {
    for (i64 i = 0; i < n; i++) {
      for (i64 j = 0; j < n; j++)a[i][j] = 0;
    }
    for (i64 i = 0; i < len; i++)a[i][i] = 1;
  }
  friend Matrix operator*(Matrix x, Matrix y) {
    Matrix ret(x.n);

    for (i64 i = 0; i < x.n; i++) {
      for (i64 j = 0; j < x.n; j++) {
        ret.a[i][j] = 0;
        for (i64 z = 0; z < x.n; z++)
          ret.a[i][j] = (ret.a[i][j] % mod + x.a[i][z] % mod * y.a[z][j]) % mod;
      }
    }
    return ret;
  }



  i64 eval() {
    i64 ret = 0;
    for (i64 j = 0; j <= n - 1; j++) {
      i64 add = (a[0][j] % mod * cofactor(0, j)) % mod;
      ret = ((ret % mod + add) % mod + mod) % mod;
    }
    return ret % mod;
  }

// 求代数余子式
  i64 cofactor(i64 i, i64 j) {
    if (n == 2) {
      i64 pad = 1;
      if ((i + j) & 1)pad *= -1;
      i ^= 1; j ^= 1;
      return ((a[i][j] + mod) % mod * pad % mod + mod) % mod;
    } else {
      i64 i1, i2, j1, j2;
      if (i == 0)i1 = 1, i2 = 2;
      else if (i == 1)i1 = 0, i2 = 2;
      else i1 = 0, i2 = 1;
      if (j == 0)j1 = 1, j2 = 2;
      else if (j == 1)j1 = 0, j2 = 2;
      else j1 = 0, j2 = 1;
      i64 add = ((a[i1][j1] * a[i2][j2] - a[i1][j2] * a[i2][j1]) % mod + mod) % mod;
      i64 pad = 1;
      if ((i + j) & 1)pad *= -1;

      return (((add + mod) % mod * pad) % mod + mod) % mod;
    }
  }


  // 矩阵求逆
  Matrix invert() {
    Matrix ret(n);
    for (i64 i = 0; i < n; i++) {
      for (i64 j = 0; j < n; j++) {
        ret.a[j][i] = cofactor(i, j);
      }
    }
    i64 v = this->eval();
    for (i64 i = 0; i < n; i++) {
      for (i64 j = 0; j < n; j++)ret.a[i][j] = (ret.a[i][j] % mod * inv[v]) % mod;
    }
    return ret;
  }
};


void init() {
  inv[1] = 1;
  for (i64 i = 2; i <= 1145140; i++)inv[i] = (mod - mod / i) * inv[mod % i] % mod;
}


int main() {
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  init();
  std::cin >> m >> k >> q;
  std::vector<Matrix>v(m + 1, Matrix(k));
  for (i64 i = 1; i <= m; i++) {
    for (i64 g = 0; g < k; g++) {
      for (i64 s = 0; s < k; s++)std::cin >> v[i].a[g][s];
    }
    v[i] = v[i - 1] * v[i];
  }

  i64 ans = 0;
  while (q--) {
    i64 l, r; std::cin >> l >> r;
    Matrix x = v[l - 1].invert();
    Matrix y = x * v[r];
    for (i64 i = 0; i < k; i++)for (i64 j = 0; j < k; j++)ans ^= y.a[i][j];

  }
  std::cout << ans << "\n";
  return 0;
}