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
struct sq {
  i64 l, r, v, tmp;
} tr[maxn * 4];
void pushup(i64 p) {
  tr[p].v = max(tr[p << 1].v, tr[p << 1 | 1].v);
}
void pushdown(i64 p) {
  if (tr[p].tmp != -inf) {
    i64 a = tr[p].tmp; tr[p].tmp = -inf;
    tr[p << 1].v = max(tr[p << 1].v, a);
    tr[p << 1 | 1].v = max(tr[p << 1 | 1].v, a);
    tr[p << 1].tmp = max(tr[p << 1].tmp, a);
    tr[p << 1 | 1].tmp = max(tr[p << 1 | 1].tmp, a);
  }
}
void build(i64 p, i64 l, i64 r) {
  tr[p].l = l; tr[p].r = r; tr[p].tmp = tr[p].v = -inf;
  if (l == r) {
    return;
  }
  i64 mid = (l + r) >> 1;
  build(p << 1, l, mid);
  build(p << 1 | 1, mid + 1, r);
  pushup(p);
}
void modify(i64 p, i64 l, i64 r, i64 v) {
  if (tr[p].l >= l and tr[p].r <= r) {
    tr[p].tmp = max(tr[p].tmp, v);
    tr[p].v = max(tr[p].v, v);
    return;
  }
  pushdown(p);
  i64 mid = (tr[p].l + tr[p].r) >> 1;
  if (l <= mid)modify(p << 1, l, r, v);
  if (r > mid)modify(p << 1 | 1, l, r, v);
  pushup(p);
}
i64 query(i64 p, i64 l, i64 r) {
  if (tr[p].l >= l and tr[p].r <= r) {
    return tr[p].v;
  }
  pushdown(p); i64 mid = (tr[p].l + tr[p].r) >> 1;
  i64 ret = -inf;
  if (l <= mid)ret = max(ret, query(p << 1, l, r));
  if (r > mid)ret = max(ret, query(p << 1 | 1, l, r));
  return ret;
}
int main() {
  i64 n, l, r; std::cin >> n >> l >> r;
  vector<i64>a(n + 5, 0);
  for (i64 i = 1; i <= n + 1; i ++) {
    std::cin >> a[i];
  }
  vector<i64>dp(n + 5, -inf); dp[1] = 0;
  build(1, 1, n + 1); i64 ans = -inf;
  if (1 + r > n + 1)ans = max(ans, 0ll);
  modify(1, 1, 1, 0);
  for (i64 i = l + 1; i <= n + 1; i++) {
    i64 L = max(1ll, i - r);
    i64 R = (i - l);
    auto q = query(1, L, R);
    //std::cout  << "#" << q << "\n";
;
    dp[i] = max(dp[i], q + a[i]);
    if (i + r > n + 1)ans = max(ans, dp[i]);
    modify(1, i, i, dp[i]);
  }
  std::cout  << ans << "\n";;
}





/*单调队列*/
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

constexpr i64 mod = 1e9 + 7;
constexpr i64 maxn = 2e7 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


i64 q[maxn], hed = 1, tal = 0;

i64 dp[maxn], a[maxn];
int main() {
  i64 n, l, r; std::cin >> n >> l >> r;
  for (i64 i = 1; i <= n + 1; i++) {
    std::cin >> a[i];
  }
  i64 ans = -inf;
  for (i64 i = 1; i <= n + 1; i++) {
    dp[i] = i == 1 ? a[i] : -inf;
    if (i <= l)continue;
    while (hed <= tal and dp[q[tal]] <= dp[i - l])tal--;
    q[++tal] = i - l;
    while (hed <= tal and q[hed] < i - r)hed++;
    if (hed <= tal)dp[i] = dp[q[hed]] + a[i];
    if (i + r > n + 1)
      ans = std::max(ans, dp[i]);
  }
  std::cout  << ans << "\n";;
}