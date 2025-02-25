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
  i64 n; std::cin >> n;
  vector<pair< i64,  i64>>q(n + 1);
  for ( i64 i = 1; i <= n; i++) {
    std::cin >> q[i].first >> q[i].second;
    q[i].second += q[i].first;
  }
  sort(q.begin() + 1, q.begin() + 1 + n, [&](auto s, auto t)->bool{
    return s.first < t.first;
  });
  i64 ptr = 1, now = 0;  i64 ans = 0;
  priority_queue< i64, vector< i64>, greater<>>pq;
  while (1) {
    if (not pq.size()) {
      if (ptr > n)break;
      now = q[ptr].first;
    }
    while (ptr <= n and q[ptr].first == now) {
      pq.push(q[ptr].second);
      ptr++;
    }
    while ((pq.size()) and pq.top() < now) {
      pq.pop();
    }
    if (pq.size()) {
      pq.pop(); ans++;
    }
    now++;
  }
  std::cout  << ans << "\n";
;
}
int main() {
  solve();
}