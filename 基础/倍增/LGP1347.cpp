
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
	i64 n, ans;
	std::cin >> n; std::vector<i64>x(n + 1);
	std::vector dp(60, std::vector<i64>(n + 5, 0));
	for (i64 i = 1; i <= n; i++) {
		i64 v; std::cin >> v;
		dp[v][i] = i + 1;
	}
	for (i64 i = 2; i <= 58; i++) {
		for (i64 j = 1; j <= n; j++) {
			if (not dp[i][j])dp[i][j] = dp[i - 1][dp[i - 1][j]];
			if (dp[i][j])ans = i;
		}
	}
	std::cout  << ans << "\n";;
}

