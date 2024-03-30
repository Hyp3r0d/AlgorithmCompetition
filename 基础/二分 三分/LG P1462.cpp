/*多组Test下使用封装数据结构, 在函数中开对象,避免暴力清空数组造成时间浪费*/

/*STL: 数据结构 std::cin std::cout  function类 lowerbound builtin max min accumulate iota stoi atoi等函数需要加上std,避免命名空间污染*/

/*数学先打表, 后对拍, 图论只会暴力就bitset搞*/

/*300兆字节 1- 2 秒*/

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
constexpr i64 maxn = 5e4 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


struct cmp {
  bool operator()(const std::pair<i64, i64>&x, const std::pair<i64, i64>&y)const {
    return x.second > y.second;
  }
};
int main() {

  i64 n, m, b; std::cin >> n >> m >> b;
  vector<i64>f(n + 1), dis(n + 1);
  std::vector<bool>vis(n + 1, false);
  std::vector<vector<pair<i64, i64>>>g(n + 1);
  i64 l = 0, r = 0;
  for (i64 i = 1; i <= n; i++) {
    std::cin >> f[i]; r = max(r, f[i]);
  }
  l = max(f[1], f[n]);
  // l = 0 ,r = 1e10也可
  for (i64 i = 1; i <= m; i++) {
    i64 x, y, z; std::cin >> x >> y >> z;
    g[x].push_back({y, z});
    g[y].push_back({x, z});
  }
  auto check = [&](i64 x) {
    queue<i64>q;
    std::fill(dis.begin() + 1, dis.begin() + 1 + n, inf);
    std::fill(vis.begin() + 1, vis.begin() + 1 + n, false);
    dis[1] = 0; vis[1] = true; q.push(1);
    if (f[1] > x)return false;

    while (q.size()) {
      auto u = q.front(); q.pop(); vis[u] = false;
      for (auto [v, w] : g[u]) {
        if (f[v] > x)continue; //  ban掉这个点
        if (dis[v] > dis[u] + w) {
          dis[v] = dis[u] + w;
          if (not vis[v]) {
            q.push(v); vis[v] = true;
          }
        }
      }
    }
    return dis[n] <= b;
  };
  if (not check(r)) {
    puts("AFK"); return 0;
  }
  i64 ans = -1;
  while (l <= r) {
    i64 mid = (l + r) >> 1;
    if (check(mid))r = mid - 1, ans = mid;
    else l = mid + 1;
  }
  if (ans == -1) {
    puts("AFK"); return 0;
  }
  std::cout  << ans << "\n";;
}