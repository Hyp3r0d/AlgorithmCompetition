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
const i64 mod = 998244353;
const i64 maxn = 2e5 + 5;
const i64 inf = 0x3f3f3f3f3f3f3f3f;


int main() {
	i64 n, x, y; std::cin >> n >> x >> y;
	std::vector<pair<i64, i64>>g(n + 1);
	for (i64 i = 1; i <= n; i++) {
		std::cin >> g[i].first >> g[i].second;
	}
	std::vector dp(n + 1, std::vector (n + 1, std::vector<i64>(x + 1, inf)));
	dp[0][0][0] = 0;
	for (i64 i = 0; i <= n; i++) {
		for (i64 j = 0; j <= i; j++) {
			for (i64 k = x; k >= 0; k--) {
				if (i >= 1)
					dp[i][j][k] = std::min(dp[i][j][k], dp[i - 1][j][k]);
				if (j >= 1 and k >= g[i].first)dp[i][j][k] = std::min(dp[i][j][k], dp[i - 1][j - 1][k - g[i].first] + g[i].second);
			}
		}
	}
	for (i64 i = n; i >= 0; i--) {
		for (i64 j = i; j >= 0; j--) {
			for (i64 k = x; k >= 0; k--) {
				if (dp[i][j][k] <= y) {
					std::cout << std::min(j + 1, n) << "\n"; return 0;
				}
			}
		}
	}
}