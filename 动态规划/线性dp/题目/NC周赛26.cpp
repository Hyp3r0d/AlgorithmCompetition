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
constexpr i64 maxn = 2e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

int main() {
	i64 n; std::cin >> n;
	std::vector<i64>dp(10);
	dp[0] = 25; dp[1] = 1;
	// 0 无意义结尾
	// 1 r 结尾
	// 2 re 结尾
	// 3一个 red
	// 4 一个 r结尾
	// 5 一个 re结尾
	// 6 两个 red
	for (i64 i = 2; i <= n; i++) {
		std::vector<i64>ndp(10, 0);
		ndp[0] = (ndp[0] % mod + dp[0] % mod * 25 % mod + dp[1] % mod * 24 % mod + dp[2] % mod * 24) % mod;
		ndp[1] = (ndp[1] % mod + dp[0] % mod + dp[1] % mod + dp[2] % mod) % mod;
		ndp[2] = (ndp[2] % mod + dp[1] % mod) % mod;
		ndp[3] = (dp[4] % mod * 24 % mod + ndp[3] % mod * 25 % mod + dp[3] % mod * 25 % mod + dp[2] % mod + dp[5] * 24) % mod;
		ndp[4] = (ndp[4] % mod + dp[3] % mod + dp[4] % mod + dp[5] % mod) % mod;
		ndp[5] = (ndp[5] % mod + dp[4] % mod) % mod;
		ndp[6] = (ndp[6] % mod + dp[6] % mod * 26 % mod + dp[5]) % mod;
		dp = ndp;
	}
	std::cout << dp[6] % mod << "\n";
	return 0;
}
