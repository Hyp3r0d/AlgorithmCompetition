/* 中国剩余定理 */
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


i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
  if (b == 0) {
    x = 1; y = 0; return a;
  }

  i64 d = exgcd(b, a % b, x, y);
  i64 tmp = x; x = y; y = tmp - a / b * y;

  return d;
}


i64 inv(i64 a, i64 b) {
  i64 x, y; exgcd(a, b, x, y);
  return (x % b + b) % b;
}


int main() {
  i64 n = 108, m = 9;
  std::vector<i64>a = {0, 4, 5, 7, 9, 11, 13, 17, 19, 23};
  std::vector<i64>b(110, 0); auto c = b;
  i64 mul = 1;

  std::cout << n << "\n";
  i64 sum = 1;

  for (i64 i = 1; i <= m; i++) {
    for (i64 j = 1; j <= a[i]; j++) {
      std::cout << sum + (j % a[i]) << " ";
    }
    sum += a[i]; mul *= a[i];
  }

  std::cout << "\n";
  for (i64 i = 1; i <= n; i++)std::cin >> b[i];
  sum = 1;
  for (i64 i = 1; i <= m; i++) {
    c[i] = (b[sum] - sum) % a[i];
    c[i] = (c[i] % a[i] + a[i]) % a[i];
    sum += a[i];
  }

  i64 ans = 0;
  for (i64 i = 1; i <= m; i++) {
    i64 mm = mul / a[i];
    i64 x = inv(mm, a[i]);
    ans = (ans + x % mul * c[i] % mul * mm % mul) % mul;
  }
  std::cout << ans << "\n";
}

