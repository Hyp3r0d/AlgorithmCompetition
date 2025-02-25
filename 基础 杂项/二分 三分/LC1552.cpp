class Solution {
public:
    int maxDistance(vector<int>& position, int m) {
        int n = position.size();
        std::sort(position.begin(), position.end());
        auto check = [&](int mid) {
            int cnt = 1;
            int pre = position[0];
            for (int i = 1; i < n; i++) {
                if (position[i] - pre >= mid) {
                    pre = position[i];
                    cnt++;
                }
            }
            return cnt >= m;
        };
        int l = 1, ans = 0, r = position.back() - position.front();
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid)) {
                l = mid + 1;
                ans = mid;
            } else {
                r = mid - 1;
            }
        }
        return ans;
    }
};





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


class Solution {
public:
  int maxDistance(vector<int>& position, int m) {
    std::sort(position.begin(), position.end());
    i64 n = position.size();
    auto check = [&](i64 mid) {
      i64 pre = 0, cnt = 1;
      for (i64 i = 0; i < n; i++) {
        if (position[i] - position[pre] >= mid) {
          pre = i; cnt++;
        }
      }
      return cnt >= m;
    };
    i64 l = 1, r = 1e10;
    while (l < r) {
      i64 mid = (l + r + 1) >> 1;
      if (check(mid))l = mid;
      else r = mid - 1;
    }
    return l;
  }
};