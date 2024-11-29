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
	bool isMatch(string s, string p) {
		i64 n = s.size(), m = p.size();
		s = " " + s; p = " " + p;
		std::vector dp(m + 1, std::vector<i64>(n + 1, 0));
		dp[0][0] = 1;
		for (i64 i = 1; i <= m; i++) {
			if (isalpha(p[i])) {
				for (i64 j = 1; j <= n; j++) {
					if (s[j] == p[i])
						dp[i][j] = (dp[i][j] | dp[i - 1][j - 1]);
				}
			} else if (p[i] == '?') {
				for (i64 j = 1; j <= n; j++)dp[i][j] = (dp[i][j] | dp[i - 1][j - 1]);
			} else {
				for (i64 j = 0; j <= n; j++) {
					for (i64 k = 0; k <= j; k++)dp[i][j] = (dp[i][j] | dp[i - 1][k]);
				}
			}
		}
		return dp[m][n];
	}
};