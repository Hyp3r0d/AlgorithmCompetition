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
constexpr i64 maxn = 4e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


int main() {
	i64 n, m; std::cin >> n >> m;
	vector<i64>a(n + 1);
	for (i64 i = 1; i <= n; i++) {
		std::cin >> a[i];
	}
	i64 tot = accumulate(a.begin() + 1, a.begin() + 1 + n, 0ll);
	vector<bool>ban(n + 5);
	i64 ans = 0;
	auto dp = [&]() {
		i64 ret = 0;
		i64 x = 0;
		vector dp(n + 5, std::vector<bool>(tot + 5, 0));
		dp[0][0] = true;
		for (i64 i = 1; i <= n; i++) {
			if (ban[i])continue;
			x++;
			for (i64 j = tot; j >= 0; j--) {
				dp[x][j] = dp[x][j] | dp[x - 1][j];
				if (j >= a[i])
					dp[x][j] = dp[x][j] | (dp[x - 1][j - a[i]]);
			}
		}
		for (i64 i = tot; i >= 1; i--) {
			if (dp[x][i])ret++;
		}
		ans = std::max(ans, ret);
	};
	std::function<void(i64, i64)>dfs = [&](i64 x, i64 y) {
		if (x > n) {
			if (y == m) {
				dp();
			}
			return;
		}
		if (n - x + 1 >= m - y) {
			ban[x] = true;
			dfs(x + 1, y + 1);
			ban[x] = false;
		}
		if (n - x >= m - y) {
			dfs(x + 1, y);
		}
	};
	dfs(1, 0);
	std::cout << ans << "\n";
}