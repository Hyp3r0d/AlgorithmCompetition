/*与概率递推不同,本题应当先算出各种情况的种数量,结合古典概型进行运算*/
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

int main() {
	i64 n; std::cin >> n;
	std::vector<i64>a(n + 1);
	i64 tot = 0;
	for (i64 i = 1; i <= n; i++) {
		std::cin >> a[i]; tot += abs(a[i]);
	}
	if (tot & 1) {
		puts("-1"); return 0;
	}
	std::vector dp(n + 1, std::vector<i64>(2 * tot + 1, inf));
	dp[0][tot] = 0;
	for (i64 i = 1; i <= n; i++) {
		for (i64 j = 0; j <= 2 * tot; j++) {
			if (a[i] >= 0) {
				if (j + a[i] <= 2 * tot)
					dp[i][j + a[i]] = std::min(dp[i][j + a[i]], dp[i - 1][j]);
				if (j + (-a[i]) >= 0) {
					dp[i][j - a[i]] = std::min(dp[i][j - a[i]], dp[i - 1][j] + 1);
				}
			} else {
				if (j + (a[i]) >= 0) {
					dp[i][j + a[i]] = std::min(dp[i][j + a[i]], dp[i - 1][j]);
				}
				if (j - a[i] <= 2 * tot) {
					dp[i][j - a[i]] = std::min(dp[i][j - a[i]], dp[i - 1][j] + 1);
				}
			}
		}
	}
	i64 ans = dp[n][tot];
	if (ans == inf) {
		std::cout << -1 << "\n";
	} else std::cout << dp[n][tot] << "\n";
	return 0;
}