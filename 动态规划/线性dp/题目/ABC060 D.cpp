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

constexpr i64 mod = 1e9 + 7;
constexpr i64 maxn = 4e3 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


i64 dp[105][305][105];
int main() {
	i64 n, m; std::cin >> n >> m;

	std::vector<i64>w(n + 1), v(n + 1);
	for (i64 i = 1; i <= n; i++) {
		std::cin >> w[i] >> v[i];
	}
	i64 h = w[1];
	for (i64 i = 1; i <= n; i++)w[i] -= h;
	for (i64 i = 1; i <= n; i++) {
		for (i64 j = 0; j <= 3 * i; j++) {
			for (i64 k = 0; k <= i; k++) {
				dp[i][j][k] = std::max(dp[i][j][k], dp[i - 1][j][k]);
				if (j >= w[i] and k) {
					dp[i][j][k] = std::max(dp[i][j][k], dp[i - 1][j - w[i]][k - 1] + v[i]);
				}
			}
		}
	}

	i64 ans = 0;
	for (i64 i = 0; i <= 3 * n; i++) {
		for (i64 j = 0; j <= n; j++) {
			if (i + j * h <= m) {
				ans = std::max(ans, dp[n][i][j]);
			}
		}
	}

	std::cout << ans;
}
