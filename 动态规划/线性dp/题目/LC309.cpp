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
	int maxProfit(vector<int>& prices) {
		i64 n = prices.size();
		std::vector dp(n + 1, std::vector<i64>(3, -inf));
		// 0 不持仓且不处于冷冻期 1 不持仓处于冷冻期 2 持仓
		dp[0][0] = 0;
		for (i64 i = 1; i <= n; i++) {
			dp[i][0] = std::max(dp[i][0], dp[i - 1][0]);
			dp[i][0] = std::max(dp[i][0], dp[i - 1][1]);
			dp[i][1] = std::max(dp[i][1], dp[i - 1][2] + prices[i - 1]);
			dp[i][2] = std::max(dp[i][2], dp[i - 1][2]);
			dp[i][2] = std::max(dp[i][2], dp[i - 1][0] - prices[i - 1]);
		}
		return std::max({dp[n][0], dp[n][1], dp[n][2]});
	}
};