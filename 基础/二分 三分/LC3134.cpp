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

class Solution {
public:
  std::unordered_map<i64, i64>cnt;
  void add(i64 v) {
    cnt[v]++;
  }
  void del(i64 v) {
    cnt[v]--; if (cnt[v] == 0)cnt.erase(v);
  }
  int medianOfUniquenessArray(vector<int>& nums) {
    i64 n = nums.size();
    nums.insert(nums.begin(), 0);
    i64 l = 0, r = n;
    i64 p = (n * (n + 1) / 2 + 1) / 2;
    auto check = [&](i64 mid) {
      cnt.clear(); i64 ans = 0;
      for (i64 r = 1, l = 1; r <= n; r++) {
        add(nums[r]);
        while (cnt.size() > mid) {
          del(nums[l]); l++;
        }
        ans += r - l + 1;
      }
      return ans >= p;
    };

    /*i64 ret = -1;
    while (l <= r) {
      i64 mid = (l + r) >> 1;
      if (check(mid))r = mid - 1, ret = mid;
      else l = mid + 1;
      return ret;
    }*/
    while (l < r) {
      i64 mid = (l + r) >> 1;
      if (check(mid))r = mid;
      else l = mid + 1;
    }
    return r;
  }
};