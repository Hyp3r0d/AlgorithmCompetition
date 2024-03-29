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

constexpr i64 mod = 45989;
constexpr i64 maxn = 4e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


int main() {
	i64 n, m; std::cin >> n >> m;
	std::vector z(n + 1, vector<i64>(m, 0));
	for (i64 i = 1; i <= n; i++) {
		for (i64 j = 0; j < m; j++) {
			std::cin >> z[i][j];
		}
	}

	std::vector dp(n + 1, std::vector<i64>((1 << m) + 1, 0));
	dp[0][0] = 0;
	for (i64 i = 1; i <= n; i++) {
		for (i64 k = 0; k < (1 << m); k++) {
			i64 sum = 0;
			for (i64 f = 0; f < m; f++) {
				if ((k >> f) & 1)sum += z[i][f];
			}
			for (i64 j = 0; j < (1 << m); j++) {
				if (j == 0 or k == 0 or !((((j ^ k) >> 1)) | (((j ^ k) << 1)))) {
					dp[i][k] = std::max(dp[i][k], dp[i - 1][j] + sum);
				}
			}
		}
	}
	i64 ans = -inf;
	for (i64 i = 0; i < (1 << m); i++)ans = std::max(ans, dp[n][i]);
	std::cout << ans << "\n";
	return 0;
}