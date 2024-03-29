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

constexpr i64 mod = 45989;
constexpr i64 maxn = 3e4 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


int main() {
	i64 n, h, delta; std::cin >> n >> h >> delta;
	std::vector d(n + 1, std::vector<i64>(h + 1, 0));
	for (i64 i = 1; i <= n; i++) {
		i64 z; std::cin >> z;
		for (i64 j = 1; j <= z; j++) {
			i64 v; std::cin >> v; d[i][v]++;
		}
	}
	std::vector dp(h + 1, std::vector<i64>(n + 1, 0));
	std::vector<i64>mx(h + 5);
	for (i64 i = 1; i <= n; i++)dp[h][i] = d[i][h], mx[h] = std::max(mx[h], dp[h][i]);

	for (i64 i = h - 1; i >= 0; i--) {
		for (i64 j = 1; j <= n; j++) {
			if (i + delta <= h) {
				dp[i][j] = std::max(dp[i][j], mx[i + delta] + d[j][i]);
			}
			dp[i][j] = std::max(dp[i][j], dp[i + 1][j] + d[j][i]);
			mx[i] = std::max(mx[i], dp[i][j]);
		}
	}
	std::cout << mx[0] << "\n";
}