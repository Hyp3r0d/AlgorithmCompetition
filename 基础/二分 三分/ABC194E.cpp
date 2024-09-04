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
const i64 maxn = 2e6 + 5;
const i64 inf = 0x3f3f3f3f3f3f3f3f;



i64 tr[maxn], n, m;

i64 cnt[maxn];

void add(i64 idx, i64 v) {
  for (; idx <= n; idx += idx & -idx)tr[idx] += v;
}

i64 query(i64 idx) {
  i64 ret = 0;
  for (; idx >= 1; idx -= idx & -idx)ret += tr[idx];
  return ret;
}



void insert(i64 x) {
  if (x == 0) {
    cnt[x]++;
  } else {
    cnt[x]++;
    if (cnt[x] == 1)add(x, 1);
  }
}

void rem(i64 x) {
  if (x == 0) {
    cnt[x]--;
  } else {
    cnt[x]--;
    if (cnt[x] == 0)add(x, -1);
  }
}

i64 query2(i64 x) {
  if (x == -1)return 0ll;
  return query(x) + (cnt[0] ? 1 : 0);
}

int main() {
  std::cin >> n >> m;
  std::vector<i64>a(n + 1);
  for (i64 i = 1; i <= n; i++) {
    std::cin >> a[i];
  }
  auto check = [&](i64 mid) {
    std::fill(tr, tr + 1 + n, 0ll);
    std::fill(cnt, cnt + 1 + n, 0ll);

    i64 r = 1, l = 1;
    for (; r <= m; r++) {
      insert(a[r]);

    }
    if (query2(mid - 1) < mid)return false;
    for (r = m + 1, l = 1; r <= n; r++) {
      insert(a[r]);
      while (r - l + 1 > m) {
        rem(a[l]); l++;
      }
      if (query2(mid - 1) < mid)return false;
    }
    return true;
  };
  i64 l = 0, r = n; i64 ans = -1;
  while (l <= r) {
    i64 mid = (l + r) >> 1;
    if (check(mid))l = mid + 1, ans = mid;
    else r = mid - 1;
  }
  std::cout << ans << "\n";
}



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
    i64 n, m; std::cin >> n >> m;
    vector<i64>A(n + 5, 0); vector<i64>cnt(n + 5, 0);
    for (i64 i = 1; i <= n; i++)std::cin >> A[i];
    for (i64 i = 1; i <= m; i++)cnt[A[i]]++;
    i64 cur = 0;
    while (cnt[cur])cur++;
    if (not cur) {
        std::cout  << 0 << "\n";
        return;
    }
    for (i64 r = m + 1, l = m + 1; r <= n; r++, l++) {
        cnt[A[r]]++;
        cnt[A[l]]--;
        if (A[l] < cur and cnt[A[l]] == 0)cur = A[l];
        if (cur == 0) {
            std::cout  << 0 << "\n";
            return;
        }
    }
    std::cout  << cur << "\n";
; return;
}
int main() {
    solve();
}


