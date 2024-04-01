/*A Star搜索*/
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

constexpr i64 mod = 1e9 + 7;
constexpr i64 maxn = 2e7 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

int main() {
	i64 n, m; std::cin >> n >> m;
	std::vector<i64>a(n + 1); i64 tot = 0;
	for (i64 i = 1; i <= n; i++) {
		std::cin >> a[i]; tot += a[i];
	}
	i64 ans = 0;
	std::vector<bool>vis(n + 1);
	auto dp = [&]() {
		i64 x = 0; i64 z = 0;
		std::vector dp(n - m + 1, std::vector<bool>(1 * tot + 5, false));
		dp[0][0] = true;
		for (i64 i = 1; i <= n; i++) {
			if (vis[i])continue;
			x++;
			for (i64 j = tot; j >= 0; j--) {
				dp[x][j] = dp[x][j] | (dp[x - 1][abs(j - a[i])]);
				if (j + a[i] <= tot) {
					dp[x][j] = (dp[x][j] | dp[x - 1][j + a[i]]);
				}
			}
		}
		for (i64 j = tot; j >= 1; j--) {
			if (dp[x][j])z++;
		}
		ans = std::max(ans, z);
	};
	std::function<void(i64, i64)>dfs = [&](i64 cur, i64 now) {
		if (cur > n or now > m) {
			return;
		}
		vis[cur] = true;
		if (now + 1 == m) {
			dp(); vis[cur] = false;
		} else {
			if (n - cur >= m - (now + 1)) {
				dfs(cur + 1, now + 1);
			}
			vis[cur] = false;
		}
		if (n - cur >= m - now) {
			dfs(cur + 1, now);
		}
	};
	dfs(1, 0);
	std::cout  << ans << "\n";;
	return 0;
}

