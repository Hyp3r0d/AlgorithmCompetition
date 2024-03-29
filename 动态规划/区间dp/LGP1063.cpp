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

constexpr i64 mod = 998244353;
constexpr i64 maxn = 5e4 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


struct P {
	i64 x; i64 y;
} z[maxn]; i64 dp[405][405];
int main() {
	i64 n; std::cin >> n;
	for (i64 i = 1; i <= n; i++) {
		std::cin >> z[i].x;
	}
	for (i64 i = 1; i <= n; i++) {
		z[i].y = (z[((i % n) + 1)].x);
	}
	for (i64 i = n + 1; i <= 2 * n; i++) {
		z[i] = z[i - n];
	}
	i64 ans = 0;
	for (i64 len = 1; len <= 2 * n; len++) {
		for (i64 i = 1; i + (len) - 1 <= 2 * n; i++) {
			i64 l = i, r = i + len - 1;
			for (i64 k = l; k <= r - 1; k++) {
				dp[l][r] = std::max(dp[l][r], dp[l][k] + dp[k + 1][r] + z[l].x * z[k + 1].x * z[r].y);
			}
			if (len == n) {
				ans = std::max(ans, dp[l][r]);
			}
		}

	}
	std::cout << ans << "\n";
	return 0;
}