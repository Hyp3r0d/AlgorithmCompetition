/*dp求概率*/
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
	i64 n, a, q; std::cin >> n >> a >> q;
	std::string s; std::cin >> s;
	s = " " + s;
	f64 p = (f64)a / 100.0;
	std::vector dp(n + 1, std::vector<f64>(n + 1, 0.0));
	dp[0][0] = 1.0;
	for (i64 i = 1; i <= n; i++) {
		for (i64 j = 0; j <= i; j++) {
			if (s[i] == '0') {
				dp[i][j] = dp[i - 1][j] * p;
				if (j >= 1)
					dp[i][j] += dp[i - 1][j - 1] * (1 - p);
			} else {
				dp[i][j] = (dp[i - 1][j] * (1 - p));
				if (j >= 1)
					dp[i][j] += dp[i - 1][j - 1] * p;
			}
		}
	}
	f64 ans = 0.0;
	for (i64 i = q; i <= n; i++) {
		ans += dp[n][i];
	}
	printf("%.3lf\n", ans);
}