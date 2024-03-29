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

	i64 f, v; std::cin >> f >> v;

	std::vector a(f + 1, std::vector<i64>(v + 1, 0));

	for (i64 i = 1; i <= f; i++) {
		for (i64 j = 1; j <= v; j++) {
			std::cin >> a[i][j];
		}
	}

	std::vector dp(v + 1, std::vector<i64>(f + 1, -inf));

	dp[0][0] = 0;

	for (i64 i = 1; i <= v; i++) {
		for (i64 j = 0; j <= f; j++) {
			dp[i][j] = std::max(dp[i][j], dp[i - 1][j]);
			if (j >= 1) {
				dp[i][j] = std::max(dp[i][j], dp[i - 1][j - 1] + a[j][i]);
			}
		}
	}

	std::cout  << dp[v][f] << "\n";;
	std::vector<i64>ans(f + 1);
	for (i64 x = v, y = f; x >= 1; x--) {
		if (dp[x - 1][y] == dp[x][y]) {
			continue;
		} else if (dp[x - 1][y - 1] + a[y][x] == dp[x][y]) {
			ans[y] = x; y--;
			if (y == 0)break;
		}
	}
	for (i64 i = 1; i <= f; i++) {
		std::cout  << ans[i] << " \n"[i == f];
	}
	return 0;
}
