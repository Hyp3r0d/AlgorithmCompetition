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

i64 dp[55][55][55][55];
i64 a[55][55];
int main() {
	i64 n, m; std::cin >> n >> m;
	for (i64 i = 1; i <= n; i++) {
		for (i64 j = 1; j <= m; j++) {
			std::cin >> a[i][j];
		}
	}
	for (i64 i = 1; i <= n; i++) {
		for (i64 j = 1; j <= m; j++) {
			for (i64 k = 1; k <= n; k++) {
				for (i64 l = j + 1; l <= m; l++) {
					dp[i][j][k][l] = std::max({dp[i - 1][j][k - 1][l], dp[i - 1][j][k][l - 1], dp[i][j - 1][k - 1][l], dp[i][j - 1][k][l - 1]}) + a[i][j]+a[k][l];
				}
			}
		}
	}
	std::cout << dp[n][m - 1][n - 1][m] << "\n";
}