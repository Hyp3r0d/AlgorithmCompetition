
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

constexpr i64 mod = 1e9 + 7;
constexpr i64 maxn = 2e7 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
	int minCut(string s) {
		i64 n = s.size(); s = " " + s;
		std::vector<i64>dp(n + 1, inf);
		dp[0] = 0;
		std::vector a(n + 1, std::vector<bool>(n + 1, false));
		for (i64 i = 1; i <= n; i++) {
			a[i][i - 1] = a[i][i] = true;
		}
		for (i64 len = 2; len <= n; len++) {
			for (i64 i = 1; i + len - 1 <= n; i++) {
				i64 j = i + len - 1;
				if (s[i] == s[j]) {
					a[i][j] = a[i][j] | a[i + 1][j - 1];
				}
			}
		}
		for (i64 i = 1; i <= n; i++) {
			for (i64 j = 0; j < i; j++) {
				if (a[j + 1][i]) {
					dp[i] = std::min(dp[i], dp[j] + 1);
				}
			}
		}
		return dp[n] - 1;
	}
};