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

constexpr i64 mod = 1e9 + 7;
constexpr i64 maxn = 5e2 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

int main() {
	i64 n, k; std::cin >> n >> k;
	std::vector<std::vector<i64>>g(n + 1);
	for (i64 i = 1; i <= n - 1; i++) {
		i64 v; std::cin >> v;
		g[i + 1].push_back(v);
		g[v].push_back(i + 1);
	}
	std::vector<f64>dp(n + 1, 0.0);
	vector<i64>sz(n + 1);
	f64 ans = 0.0;
	std::function<void(i64, i64)>dfs = [&](i64 u, i64 f) {
		sz[u] = 1;
		for (auto v : g[u]) {
			if (v == f)continue;
			dfs(v, u);
			sz[u] += sz[v];
		}
		if (sz[u] == 1) {
			dp[u] = 1; return;
		}
		for (auto v : g[u]) {
			if (v == f)continue;
			dp[u] = max(dp[u], min(dp[v], (sz[v] + 0.0) / (sz[u] - 1)));
		}
		if (sz[u] > k)ans = std::max(ans, dp[u]);
	};
	dfs(1, 0);
	printf("%.8lf", ans);
	return 0;
}