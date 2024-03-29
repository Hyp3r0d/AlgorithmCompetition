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


void solve() {
  i64 n, m, k;
  std::cin >> n >> m >> k;
  vector<i64>A(n + 5, 0), B(m + 5, 0);
  for (i64 i = 1; i <= n; i++) {
    std::cin >> A[i];
  }
  for (i64 i = 1; i <= m; i++) {
    std::cin >> B[i];
  }
  vector<i64>C(k + 5, 0);
  for (i64 i = 1; i <= k; i++) {
    i64 u, v; std::cin >> u >> v;
    C[i] = A[u] + B[v];
  }
  std::sort(A.begin() + 1, A.begin() + 1 + n);
  std::sort(B.begin() + 1, B.begin() + 1 + m);
  std::sort(C.begin() + 1, C.begin() + 1 + k);
  auto check = [&](i64 mid) {
    i64 sum = 0;
    for (i64 i = 1; i <= n; i++) {
      i64 cur = upper_bound(B.begin() + 1, B.begin() + 1 + m, mid - A[i]) - B.begin();
      sum += m - cur + 1;
    }
    i64 cur = upper_bound(C.begin() + 1, C.begin() + 1 + k, mid) - C.begin();
    sum -= (k - cur + 1);
    // 等价于大于等于mid的个数 >= x
    return (sum == 0);
  };
  i64 l = 0, r = 1e12, ans = 0;
  while (l <= r) {
    i64 mid = (l + r) >> 1;
    if (check(mid)) {
      ans = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  cout << ans << "\n";
}
int main() {
  solve();
}