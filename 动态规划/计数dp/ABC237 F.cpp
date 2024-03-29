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


i64 dp[1005][20][20][20];

int main() {
	i64 n, m; std::cin >> n >> m;
	dp[0][m + 1][m + 1][m + 1] = 1;
	for (i64 i = 1; i <= n; i++) {
		for (i64 j = 1; j <= m + 1; j++) {
			for (i64 k = 1; k <= m + 1; k++) {
				for (i64 r = 1; r <= m + 1; r++) {
					for (i64 x = 1; x <= m; x++) {
						if (x <= j) {
							dp[i][x][k][r] += dp[i - 1][j][k][r];
							dp[i][x][k][r] %= mod;
						} else if (x <= k) {
							dp[i][j][x][r] += dp[i - 1][j][k][r];
							dp[i][j][x][r] %= mod;
						} else if (x <= r) {
							dp[i][j][k][x] += dp[i - 1][j][k][r];
							dp[i][j][k][x] %= mod;
						}
					}
				}
			}
		}
	}
	i64 ans = 0;
	for (i64 i = 1; i <= m; i++) {
		for (i64 j = 1; j <= m; j++) {
			for (i64 k = 1; k <= m; k++) {
				ans = (ans % mod + dp[n][i][j][k]) % mod;
			}
		}
	}
	std::cout << ans << "\n";
}