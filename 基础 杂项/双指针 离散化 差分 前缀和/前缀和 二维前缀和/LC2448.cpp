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
constexpr i64 maxn = 2e5 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:

	long long minCost(vector<int>& nums, vector<int>& cost) {
		i64 n = nums.size();
		std::vector<pair<i64, i64>>w(n + 1);
		for (i64 i = 1; i <= n; i++) {
			w[i] = {nums[i - 1], cost[i - 1]};
		}
		std::sort(w.begin() + 1, w.begin() + 1 + n, [&](auto x, auto y)->bool{
			return x.first < y.first;
		});
		std::vector<i64>pre1(n + 1), pre2(n + 1);
		for (i64 i = 1; i <= n; i++) {
			pre1[i] = pre1[i - 1] + w[i].first * w[i].second;
		}
		for (i64 i = 1; i <= n; i++) {
			pre2[i] = pre2[i - 1] + w[i].second;
		}
		i64 ans = inf;
		for (i64 i = 1; i <= n; i++) {
			i64 cur = (pre1[n] - pre1[i]) - (pre2[n] - pre2[i]) * w[i].first;
			cur += ((pre2[i - 1]) * w[i].first - pre1[i - 1]);
			ans = std::min(ans, cur);
		}
		return ans;
	}
};