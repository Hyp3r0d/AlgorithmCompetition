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
constexpr i64 maxn = 4e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

i64 dp[205][205][2];

int main() {
	i64 n, c; std::cin >> n >> c;
	std::vector<i64>d(n + 1), p(n + 1);
	for (i64 i = 1; i <= n; i++) {
		std::cin >> d[i] >> p[i];
		p[i] = p[i - 1] + p[i];
	}

	// 关了哪几部分的路灯, 走到了左/右, 耗电量最小的办法
	memset(dp, 0x3f, sizeof(dp));
	dp[c][c][0] = dp[c][c][1] = 0;
	// 1 左 0 右
	for (i64 len = 2; len <= n; len++) {
		for (i64 i = 1; i + len - 1 <= n; i++) {
			i64 j = i + len - 1;
			dp[i][j][1] = std::min(dp[i][j][1], dp[i + 1][j][1] + (d[i + 1] - d[i]) * (p[n] - (p[j] - p[i])));
			dp[i][j][1] = std::min(dp[i][j][1], dp[i + 1][j][0] + (d[j] - d[i]) * (p[n] - (p[j] - p[i])));
			dp[i][j][1] = std::min(dp[i][j][1], dp[i][j - 1][1] + (d[j] - d[i]) * (p[n] - (p[j - 1] - p[i - 1])) + (d[j] - d[i]) * (p[n] - (p[j] - p[i - 1])));
			dp[i][j][1] = std::min(dp[i][j][1], dp[i][j - 1][0] + (d[j] - d[j - 1]) * (p[n] - (p[j - 1] - p[i - 1])) + (d[j] - d[i]) * (p[n] - (p[j] - p[i - 1])));


			dp[i][j][0] = std::min(dp[i][j][0], dp[i][j - 1][0] + (d[j] - d[j - 1]) * (p[n] - (p[j - 1] - p[i - 1])));
			dp[i][j][0] = std::min(dp[i][j][0], dp[i][j - 1][1] + (d[j] - d[i]) * (p[n] - (p[j - 1] - p[i - 1])));
			dp[i][j][0] = std::min(dp[i][j][0], dp[i + 1][j][0] + (d[j] - d[i]) * (p[n] - (p[j] - p[i])) + (d[j] - d[i]) * (p[n] - (p[j] - p[i - 1])));
			dp[i][j][0] = std::min(dp[i][j][0], dp[i + 1][j][1] + (d[i + 1] - d[i]) * (p[n] - (p[j] - p[i])) + (d[j] - d[i]) * (p[n] - (p[j] - p[i - 1])));
		}
	}

	std::cout << std::min(dp[1][n][0], dp[1][n][1]) << "\n";
	return 0;
}