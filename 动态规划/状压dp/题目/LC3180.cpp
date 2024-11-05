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
	int maxTotalReward(vector<int>& rewardValues) {
		std::sort(rewardValues.begin(), rewardValues.end());
        int mx = *max_element(rewardValues.begin(), rewardValues.end());
		std::bitset<10000>dp; dp[0] = 1;
		for (auto x : rewardValues) {
			std::bitset<10000>ndp = dp;
			for (i64 j = 0; j < x; j++) {
				ndp[j + x] = ndp[j + x] | dp[j];
			}
			dp = ndp;
		}
		for (i64 j = 2 * mx; j >= 0; j--) {
			if (dp[j])return j;
		}
		return 0;
	}
};