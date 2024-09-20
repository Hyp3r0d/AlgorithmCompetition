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
constexpr i64 maxn = 2e3 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
  int numRescueBoats(vector<int> &people, int limit) {
    int ans = 0;
    std::sort(people.begin(), people.end());
    i64 n = people.size(); i64 l = 0, r = n - 1;
    while (l <= r) {
      if (people[r] + people[l] > limit)r--;
      else l++, r--;
      ans++;
    }
    return ans;
  }
};

