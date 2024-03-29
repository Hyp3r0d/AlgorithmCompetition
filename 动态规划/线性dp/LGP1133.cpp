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


i64 dp[3][100005][3][3];

int main() {
	i64 n; std::cin >> n;
	std::vector<array<i64, 3>>z(n + 1);
	for (i64 i = 1; i <= n; i++) {
		std::cin >> z[i][0] >> z[i][1] >> z[i][2];
	}
	for (i64 i = 0; i <= 2; i++) {
		for (i64 j = 0; j <= 2; j++) {
			dp[i][2][i][j] = z[1][i] + z[2][j];
		}
	}
	auto check = [&](i64 i, i64 j, i64 k) {
		return (j < i and j < k) or (j > i and j > k);
	};

	for (i64 j = 3; j <= n; j++) {
		if (j == n) {
			for (i64 i = 0; i <= 2; i++)
				// 考虑 j - 1 j  - 2位 和 1 位
				for (i64 k = 0; k <= 2; k++) {
					for (i64 l = 0; k <= 2; k++) {
						for (i64 s = 0; s <= 2; s++) {
							if (check(k, l, s) and check(l, s, i)) {
								dp[i][j][l][s] = std::max(dp[i][j][l][s], dp[i][j - 1][k][l] + z[j][s]);
							}
						}
					}
				}
		}
		else if (j == 3) {
			// 考虑 1 2位
			for (i64 i = 0; i <= 2; i++)
				for (i64 k = 0; k <= 2; k++) {
					for (i64 l = 0; l <= 2; l++)
						dp[i][j][k][l] = std::max(dp[i][j][k][l], dp[i][j - 1][i][k] + z[j][l]);
				}
		} else {
			for (i64 i = 0; i <= 2; i++)
				for (i64 k = 0; k <= 2; k++) {
					for (i64 l = 0; l <= 2; l++) {
						for (i64 s = 0; s <= 2; s++) {
							if (check(k, l, s)) {
								dp[i][j][l][s] = std::max(dp[i][j][l][s], dp[i][j - 1][k][l] + z[j][s]);
							}
						}
					}
				}
		}
	}

	i64 ans = 0;
	for (i64 i = 0; i <= 2; i++) {
		for (i64 j = 0; j <= 2; j++) {
			for (i64 k = 0; k <= 2; k++) {
				ans = std::max(ans, dp[i][n][j][k]);
			}
		}
	}
	std::cout << ans << "\n";
}