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


/* dp i j 为 该轮操作状态下还剩i 仑， 有 j 个 2 , 当前操作者赢的概率*/

int main() {
	i64 n; std::cin >> n;
	std::vector<i64>a(n + 1);
	std::vector<i64>cnt(3);
	for (i64 i = 1; i <= n; i++) {
		std::cin >> a[i]; cnt[a[i]]++;
	}

	auto qpow = [&](i64 x, i64 y) {
		i64 ret = 1;
		while (y) {
			if (y & 1)ret = ret * x % mod;
			x = x * x % mod;
			y >>= 1;
		}
		return ret % mod;
	};
	auto inv = [&](i64 x) {
		return qpow(x, mod - 2) % mod;
	};

	std::vector dp(n + 1, std::vector<i64>(n + 1, -1));
	/*for (i64 i = 1; i <= n; i++) {
		dp[i][0] = 1;
	}





	for (i64 i = 1; i <= n; i++) {
		for (i64 j = 1; j <= i; j++) {
			dp[i][j] = (dp[i][j] % mod + (i - j) % mod * inv(i) % mod * (1 - dp[i - 1][j] + mod) % mod) % mod;
			dp[i][j] = (dp[i][j] % mod + j % mod * inv(i) % mod * (1 - dp[i][j - 1] + mod) % mod) % mod;
		}
	}*/

	std::function<i64(i64, i64)>dfs = [&](i64 x, i64 y) {
		if (x == 0) {
			return dp[x][y] = 0ll;
		} else if (y == 0) {
			return dp[x][y] = 1ll;
		}
		if (dp[x][y] != -1)return dp[x][y] % mod;
		i64 res = 0;
		res = (res % mod + (x - y) % mod * inv(x) % mod * (1 - dfs(x - 1, y) + mod) % mod) % mod;
		res = (res % mod + y % mod * inv(x) % mod * (1 - dfs(x, y - 1) + mod) % mod) % mod;
		return dp[x][y] = res % mod;
	};
	std::cout << dfs(n, cnt[2]) << "\n";

	return 0;

}