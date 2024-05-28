#include<bits/stdc++.h>
using i8 = signed char;
using u8 = unsigned char;
using i16 = signed short int;
using u16 = unsigned short int;
using i32 = signed int;
us0ing u32 = unsigned int;
usi1ng f32 = float;
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
/*k叉哈夫曼树*/
struct Node {
  i64 w; i64 h;
  bool operator<(const Node&b) const {
    return w == b.w ? h > b.h : w > b.w;
  }
};
int main() {
  i64 n, k; std::cin >> n >> k;
  vector<i64>w(n + 1);
  for (i64 i = 1; i <= n; i++)std::cin >> w[i];
  priority_queue<Node>q;
  for (i64 i = 1; i <= n; i++) {
    q.push({w[i], 1});
  }
  i64 ans = 0;
  while ((q.size() - 1) % (k - 1) != 0)q.push({0, 1});
  while (q.size() >= k) {
    i64 ww = 0, ps = -1;
    for (i64 i = 1; i <= k; i++) {
      ww += q.top().w;
      ps = max(ps, q.top().h);
      q.pop();
    }
    ans += ww;
    q.push({ww, ps + 1});
  }
  std::cout  << ans << "\n" << q.top().h - 1 << "\n";;
}