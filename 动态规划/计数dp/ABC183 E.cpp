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
constexpr i64 maxn = 4e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


i64 cnt[2005][2005][3];
int main() {
	i64 h, w; std::cin >> h >> w;
	std::vector<string>g(h + 1);
	for (i64 i = 1; i <= h; i++) {
		std::cin >> g[i]; g[i] = (" " + g[i]);
	}
	std::vector dp(h + 1, std::vector<i64>(w + 1, 0));
	dp[1][1] = 1;
	for (i64 i = 1; i <= h; i++) {
		for (i64 j = 1; j <= w; j++) {
			if (g[i][j] == '#') {
				for (i64 k = 0; k <= 2; k++)cnt[i][j][k] = 0;
				continue;
			}
			dp[i][j] = (cnt[i - 1][j][0] % mod + cnt[i][j - 1][1] % mod + cnt[i - 1][j - 1][2]) % mod;
			cnt[i][j][0] = (cnt[i - 1][j][0] + dp[i][j]) % mod;
			cnt[i][j][1] = (cnt[i][j - 1][1] + dp[i][j]) % mod;
			cnt[i][j][2] = (cnt[i - 1][j - 1][2] + dp[i][j]) % mod;
		}
	}
	std::cout << dp[h][w] << "\n";
	return 0;
}