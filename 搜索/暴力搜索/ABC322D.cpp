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

void rotate(vector<string>&str) {
  auto ret = str;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ret[i][j] = str[3 - j][i];
    }
  }
  str = ret;
}
bool in(int x, int y) {
  return x >= 0 and x<4 and y >= 0 and y < 4;
}
bool check(vector<vector<int>>&tmp, vector<string>&s, int dx, int dy) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (s[i][j] == '#') {
        int nx = i + dx, ny = j + dy;
        if (not in(nx, ny))return false;
        if (tmp[nx][ny])return false;
        tmp[nx][ny] = 1;
      }
    }
  }
  return true;
}

void solve() {
  vector p(3, vector<string>(4));
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++)std::cin >> p[i][j];
  }
  function<bool(int , vector<vector<int>>, vector<vector<string>>&)> dfs = [&](int i, vector<vector<int>>tmp, vector<vector<string>>&p) {
    if (i == 3) {
      for (int j = 0; j < 4; j++) {
        for (int k = 0; k < 4; k++) {
          if (tmp[j][k] == 0)return false;
        }
      }
      puts("Yes"); return true;
    } else {
      for (int dx = -3; dx <= 3; dx++) {
        for (int dy = -3; dy <= 3; dy++) {
          auto tmp2 = tmp;
          if (check(tmp2, p[i], dx, dy)) {
            bool f = dfs(i + 1, tmp2, p);
            if (f)return true;
          }
        }
      }
    }
    return false;
  };
  bool ans = false;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ans = dfs(0, vector(4, vector<int>(4, 0)), p);
      if (ans) {
        return;
      }
      rotate(p[2]);
    }
    rotate(p[1]);
  }
  puts("No");
}
int main() {
  solve();
}






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

constexpr i64 mod = 998244353;
constexpr i64 maxn = 5e4 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

int main() {
  std::vector G(4, std::vector<string>(5));
  for (i64 i = 1; i <= 3; i++) {
    for (i64 j = 1; j <= 4; j++) {
      std::cin >> G[i][j];
      G[i][j] = " " + G[i][j];
    }
  }
  auto check = [&](i64 x, i64 y) {
    return x >= 1 and x <= 4 and y >= 1 and y <= 4;
  };
  auto rotate = [&](vector<string>&g) {
    auto ret = g;
    for (i64 i = 1; i <= 4; i++) {
      for (i64 j = 1; j <= 4; j++) {
        ret[i][j] = g[5 - j][i];
      }
    }
    g = ret;
  };

  std::vector tmp(5 + 1, std::vector<i64>(5 + 1, 0));
  auto fill = [&](i64 cur, i64 dx, i64 dy) {
    for (i64 i = 1; i <= 4; i++) {
      for (i64 j = 1; j <= 4; j++) {
        if (G[cur][i][j] == '#') {
          i64 xx = i + dx, yy = j + dy;
          if (not check(xx, yy))return false;
          if (tmp[xx][yy])return false;
          tmp[xx][yy] = 1;
        }
      }
    }
    return true;
  };
  std::function<bool(i64)>dfs = [&](i64 cur)->bool {
    if (cur == 4) {
      for (i64 i = 1; i <= 4; i++) {
        for (i64 j = 1; j <= 4; j++) {
          if (not tmp[i][j]) {
            return false;
          }
        }
      }
      return true;
    }
    for (i64 dx = -3; dx <= 3; dx++) {
      for (i64 dy = -3; dy <= 3; dy++) {
        auto z = tmp;
        bool f = fill(cur, dx, dy);
        //试试能不能填
        if (not f) {
          // 回溯时恢复该状态
          tmp = z; continue;
        }
        f = dfs(cur + 1);
        if (f) {
          return true;
        }
        // 恢复该状态
        tmp = z;
      }
    }
    return false;
  };
  for (i64 i = 1; i <= 4; i++) {
    for (i64 j = 1; j <= 4; j++) {
      bool f = dfs(1);
      if (f) {
        puts("Yes"); return 0;
      }
      rotate(G[2]);
    }
    rotate(G[1]);
  }
  puts("No"); return 0;
}