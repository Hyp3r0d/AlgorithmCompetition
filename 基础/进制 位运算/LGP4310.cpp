/*A Star搜索*/
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

int main() {
	i64 n; std::cin >> n;
	std::vector<i64>a(n + 1);
	i64 ans = 0;
	std::vector<i64>dp(33, 0);
	for (i64 i = 1; i <= n; i++) {
		i64 v; std::cin >> v;
		i64 k = 1;
		for (i64 j = 0; j <= 30; j++) {
			if ((v >> j) & 1) {
				k = std::max(k, dp[j] + 1);
			}
		}
		for (i64 j = 0; j <= 30; j++) {
			if ((v >> j) & 1)dp[j] = std::max(dp[j], k);
		}
		ans = std::max(ans, k);
	}
	std::cout  << ans << "\n";;
}

