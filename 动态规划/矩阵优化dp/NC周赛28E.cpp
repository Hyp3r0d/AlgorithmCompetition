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

constexpr i64 mod = 1e9 + 7;
constexpr i64 maxn = 2e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;




int main() {
	i64 n, k; std::cin >> n >> k;
	// k / 2 even, k - k / 2 odd
	std::vector dp(n + 1, std::vector<i64>(10, 0));
	auto check = [&](i64 x) {
		i64 cnt = 0;
		for (i64 i = 0; i <= 2; i++) {
			auto cur = ((x >> i) & 1);
			if (cur)cnt++; // 1为odd
		}
		return (cnt % 2) == 0;
	};
	auto qpow = [&](i64 x, i64 y) {
		i64 ret = 1;
		while (y) {
			if (y & 1)ret = ret * x % mod;
			x = x * x % mod;
			y >>= 1;
		}
		return ret % mod;
	};
	for (i64 i = 0; i < (1 << 3); i++) {
		if (check(i)) {
			i64 q = 1;
			i64 cnt = 0;
			for (i64 j = 0; j <= 2; j++) {
				if ((i >> j) & 1)cnt++;
			}
			q = (q % mod * qpow(k - k / 2, cnt) % mod) % mod;
			q = (q % mod * qpow(k / 2, 3 - cnt) % mod) % mod;
			dp[3][i] = q;
		}
	}
	auto ver = [&](i64 x, i64 y) {
		return (x % 4) == (y >> 1);
	};
	for (i64 i = 4; i <= n; i++) {
		for (i64 j = 0; j < (1 << 3); j++) {
			if (check(j)) {
				for (i64 k = 0; k < (1 << 3); k++) {
					if (ver(k, j)) {
						dp[i][j] = (dp[i][j] % mod + dp[i - 1][k]) % mod;
					}
				}
				i64 z = (j & 1) ? k - k / 2 : k / 2;
				dp[i][j] = (dp[i][j] % mod * z) % mod;
			}
		}
	}
	i64 ans = 0;
	for (i64 i = 0; i < (1 << 3); i++) {
		ans = (ans % mod + dp[n][i]) % mod;
	}
	std::cout << ans << "\n";
	return 0;
}