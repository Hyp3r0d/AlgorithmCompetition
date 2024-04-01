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
	i64 n, k; std::cin >> n >> k;
	string s; std::cin >> s; s = " " + s;
	std::vector dp(n + 1, std::vector<i64>(k + 2, 0));
	auto get = [&](i64 a, i64 b) {
		i64 ret = 0;
		for (i64 i = a; i <= b; i++) {
			ret = (ret * 10) + s[i] - '0';
		}
		return ret;
	};
	dp[0][0] = 1;
	for (i64 i = 1; i <= n; i++) {
		for (i64 j = 1; j <= k + 1; j++) {
			for (i64 x = 0; x < i; x++)
				dp[i][j] = std::max(dp[i][j], dp[x][j - 1] * get(x + 1, i));
		}
	}
	std::cout << dp[n][k + 1] << "\n";
}