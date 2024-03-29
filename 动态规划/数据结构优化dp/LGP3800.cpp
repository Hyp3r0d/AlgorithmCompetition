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
constexpr i64 maxn = 4e3 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

i64 lg[5005]; i64 st[maxn][30];
i64 v[maxn][maxn];
int main() {
	i64 n, m, k, t; std::cin >> n >> m >> k >> t;
	for (i64 i = 2; i <= 5000; i++) {
		lg[i] = (lg[i >> 1] + 1);
	}
	std::vector<i64>dp(m + 1);
	auto init = [&]() {
		for (i64 i = 1; i <= m; i++)st[i][0] = dp[i];
		for (i64 len = 1; (1 << len) <= m; len++) {
			for (i64 i = 1; i + (1 << len) - 1 <= m; i++) {
				st[i][len] = std::max(st[i][len - 1], st[i + (1 << (len - 1))][len - 1]);
			}
		}
	};
	auto query = [&](i64 l, i64 r) {
		i64 x = lg[r - l + 1];
		return std::max(st[l][x], st[r - (1 << x) + 1][x]);
	};
	for (i64 i = 1; i <= k; i++) {
		i64 x, y, z; std::cin >> x >> y >> z;
		v[x][y] = z;
	}
	for (i64 i = 1; i <= m; i++) {
		dp[i] = v[1][i];
	}
	for (i64 i = 2; i <= n; i++) {
		init();
		std::vector<i64>ndp(m + 1, 0);
		for (i64 j = 1; j <= m; j++) {
			i64 l = std::max(1ll, j - t);
			i64 r = std::min(m, j + t);
			ndp[j] = std::max(ndp[j], query(l, r) + v[i][j]);
		}
		dp = ndp;
	}
	i64 x = 0;
	for (i64 i = 1; i <= m; i++) {
		x = std::max(x, dp[i]);
	}
	std::cout  << x << "\n";;
}