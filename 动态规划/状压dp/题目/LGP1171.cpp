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

constexpr i64 mod = 45989;
constexpr i64 maxn = 3e4 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;



i64 dp[1000005][25];
i64 z[21][21];
int main() {
	i64 n; std::cin >> n;
	memset(dp, 0x3f, sizeof(dp));
	for (i64 i = 0; i < n; i++) {
		for (i64 j = 0; j < n; j++) {
			std::cin >> z[i][j];
		}
	}
	dp[1][0] = 0;
	for (i64 i = 1; i < (1 << n); i++) {
		if (not ((i) & 1))continue;
		for (i64 j = 0; j < n; j++) {
			if ((i >> j) & 1) {
				for (i64 k = 0; k < n; k++) {
					if (not ((i >> k) & 1)) {
						dp[i | (1 << k)][k] = std::min(dp[i | (1 << k)][k], dp[i][j] + z[j][k]);
					}
				}
			}
		}
	}
	i64 ans = inf;
	for (i64 i = 0; i < n; i++) {
		ans = std::min(ans, dp[(1 << n) - 1][i] + z[i][0]);
	}
	std::cout << ans << "\n";
	return 0;
}