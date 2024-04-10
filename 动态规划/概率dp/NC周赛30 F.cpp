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
constexpr i64 maxn = 4e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;



i64 dp[55][55][55][55];

i64 qpow(i64 x, i64 y) {
	i64 ret = 1;
	while (y) {
		if (y & 1)ret = ret * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ret % mod;
}

i64 inv(i64 x) {
	return qpow(x, mod - 2) % mod;
}
int main() {
	i64 n, m; std::cin >> n >> m;
	std::vector<i64>c1(3), c2(3);
	for (i64 i = 1; i <= n; i++) {
		i64 v; std::cin >> v; c1[v]++;
	}
	for (i64 i = 1; i <= m; i++) {
		i64 v; std::cin >> v; c2[v]++;
	}
	memset(dp, -1, sizeof(dp));
	// u 总数 u1 2的数量
	std::function<i64(i64, i64, i64, i64)>dfs = [&](i64 u, i64 u1, i64 v, i64 v1) {
		if (u == u1 and v == v1) {
			return dp[u][u1][v][v1] = 0ll;
		}
		if (not u1 and not v1) {
			return dp[u][u1][v][v1] = 0ll;

		}
		if (not u or not v) {
			return dp[u][u1][v][v1] = 0ll;
		}
		if (dp[u][u1][v][v1] != -1)return dp[u][u1][v][v1] % mod;

		i64 res = 1;

		if (u1 and v > v1) {
			res = (res % mod + u1 % mod * inv(u) % mod * (v - v1) % mod * inv(v) % mod * dfs(u, u1, v - 1, v1) % mod) % mod;
		}

		if (u > u1 and v1) {
			res = (res % mod + (u - u1) % mod * inv(u) % mod * v1 % mod * inv(v) % mod * dfs(u - 1, u1, v, v1) % mod) % mod;
		}
		i64 x = 0, y = 0;

		if (u1 and v1) {
			x = u1 % mod * inv(u) % mod * v1 % mod * inv(v) % mod;
		}

		if (u > u1 and v > v1) {
			y = (u - u1) % mod * inv(u) % mod * (v - v1) % mod * inv(v) % mod;
		}
		i64 t = inv(((1 - x - y + mod) % mod + mod) % mod) % mod;
		return dp[u][u1][v][v1] = (res) % mod * t % mod;
	};
	std::cout << dfs(n, c1[2], m, c2[2]) % mod  << "\n";
	return 0;
}