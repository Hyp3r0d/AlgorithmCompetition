// 单组测试数据开vector 多组测试数据开全局数组
#include<bits/extc++.h>

using i8 = signed char;
using u8 = unsigned char;
using i16 = signed short int;
using u16 = unsigned short int;
using i32 = signed int;
using u32 = unsigned int;
using f32 = float;
using i64 = signed  long long;
using u64 = unsigned  long long;
using f64 = double;
using i128 = __int128_t;
using u128 = __uint128_t;
using f128 = long double;
using namespace std;

constexpr i64 mod = 998244353;
constexpr i64 maxn = 4e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

char s[maxn]; int tot = 0;
i64 numss[maxn];
int opt[maxn];
i64 ksm( i64 x,  i64 y,  i64 z) {
  i64 ret = 1; x %= z;
  while (y) {
    if (y & 1)ret = ret % z * x % z;
    x = x  % z * x % z;
    y >>= 1;
  }
  return ret % z;
}
bool f = false;
void dfs(int now) {
  if (f)return; // 这一步和 exit(0)可以二选一
  // 搜索到边界, 判断
  if (now > tot - 2) {
    i64 cur = numss[1];
    for (int i = 1; i <= tot - 2; i++) {
      if (opt[i] == 1) {
        cur += numss[i + 1];
      } else if (opt[i] == 2) {
        cur -= numss[i + 1];
      } else {
        if (numss[i + 1] <= 0 or cur <= 0)return;
        cur = ksm(cur, cur, numss[i + 1]);
      }
    }
    if (cur == numss[tot]) {
      f = true;
      for (int i = 1; i < tot; i++) {
        std::cout  << numss[i];
        if (opt[i] == 1)putchar('+');
        else if (opt[i] == 2)putchar('-');
        else if (opt[i] == 3)putchar('#');
        else putchar('=');
      }
      std::cout  << numss[tot] << "\n";;
      exit(0);
    }
    return;
  }
  if (opt[now] == -1) {
    for (int i = 1; i <= 3; i++)opt[now] = i, dfs(now + 1);
  } else {
    dfs(now + 1);
  }
}
void solve() {
  scanf("%s", s + 1);
  int len = strlen(s + 1);
  for (int i = 1; i <= len; i++) {
    int cur = 0;
    while (i <= len and isdigit(s[i])) {
      cur = (cur * 10 + s[i] - '0'); i++;
    }
    numss[++tot] = cur;
    if (i > len)break;
    if (s[i] == '+') {
      opt[tot] = 1;
    } else if (s[i] == '-') {
      opt[tot] = 2;
    } else if (s[i] == '#') {
      opt[tot] = 3;
    } else if (s[i] == '?')opt[tot] = -1;
  }
  dfs(1);
  if (not f) {
    puts("-1");
  }
}

int main() {
  solve();
  return 0;
}


/*
  *
  * 第二种写法
  *
*/
bool dfs(int now) {
  if (now > tot - 2) {
    long long sum = nums[1];
    for (int i = 1; i <= tot - 2; i++) {
      if (opt[i] == 1) {
        sum = sum + nums[i + 1];
      }
      else if (opt[i] == 2) {
        sum = sum - nums[i + 1];
      }
      else if (opt[i] == 3) {
        if (sum > 0 && nums[i + 1] > 0)sum = qpow(sum, sum, nums[i + 1]);
        else return false;
      }
    }
    if (sum == nums[tot]) {
      for (int i = 1; i < tot; i++) {
        cout << nums[i];
        if (opt[i] == 1)cout << "+";
        else if (opt[i] == 2)cout << "-";
        else if (opt[i] == 3)cout << "#";
        else cout << "=";
      }
      cout << nums[tot] << "\n"; return true;
    }
    return false;
  }
  if (vis[now] == 0) {
    return dfs(now + 1);
  }
  for (int i = 1; i <= 3; i++) {
    opt[now] = i;
    bool f = dfs(now + 1);
    if (f) return true;
  }
  return false;
}




void dfs(int now) {
    if (now > tot - 2) {
        long long sum = nums[1];
        for (int i = 1; i <= tot - 2; i++) {
            if (opt[i] == 1) {
                sum = sum + nums[i + 1];
            }
            else if (opt[i] == 2) {
                sum = sum - nums[i + 1];
            }
            else if (opt[i] == 3) {
                if (sum > 0 && nums[i + 1] > 0)sum = qpow(sum,sum,nums[i + 1]);
                else return ;
            }
        }
        if (sum == nums[tot]) {
            flag = 1;
            for (int i = 1; i < tot; i++) {
                cout << nums[i];
                if (opt[i] == 1)cout << "+";
                else if(opt[i] == 2)cout << "-";
                else if(opt[i] == 3)cout << "#";
                else cout << "=";
            }
            cout << nums[tot] << "\n"; 
        }
        return;
    }
    if (vis[now] == 0){
        dfs(now + 1);
        return ;
    }
    for (int i = 1; i <= 3; i++) {
        opt[now] = i;
        dfs(now + 1);
        if(flag) return;
    }
}