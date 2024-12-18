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
		std::vector dp(n + 1, std::vector<i64>(3, -1));
		function<i64(i64, i64)>dfs = [&](i64 u, i64 v) {
			if (dp[u][v] != -1)return dp[u][v];
			if (u == 0) {
				if (v == 0)return dp[u][v] = 0;
				else return dp[u][v] = -inf;
			}
			i64 res = -inf;
			if (v == 0) {
				res = std::max(res, dfs(u - 1, 0));
				res = std::max(res, dfs(u - 1, 1));
			} else if (v == 1) {
				res = std::max(res, dfs(u - 1, 2) + prices[u - 1]);
			} else {
				res = std::max(res, dfs(u - 1, 2));
				res = std::max(res, dfs(u - 1, 0) - prices[u - 1]);
			}
			return dp[u][v] = res;
		};
		return std::max({dfs(n, 0), dfs(n, 1), dfs(n, 2)});
	}
};