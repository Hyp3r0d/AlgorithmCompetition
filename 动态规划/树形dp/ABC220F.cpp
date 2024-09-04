


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

i64 dp[maxn], sz[maxn], ans[maxn];

i64 dp2[maxn];
int main() {

	i64 n; std::cin >> n;

	std::vector<vector<i64>>g(n + 1);
	for (i64 i = 1; i <= n - 1; i++) {
		i64 u, v; std::cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	std::function<void(i64, i64)>dfs = [&](i64 u, i64 f) {
		sz[u] = 1;
		for (auto v : g[u]) {
			if (v == f)continue;
			dfs(v, u);
			sz[u] += sz[v];
			dp[u] += (dp[v] + sz[v]);
		}
	};
	dfs(1, 0);


	dp2[1] = dp[1];

	std::function<void(i64, i64)>dfs2 = [&](i64 u, i64 f) {

		for (auto v : g[u]) {
			if (v == f)continue;

			dp2[v] = dp[v] + (dp2[u] - dp[v] - sz[v]) + (n - sz[v]);
			dfs2(v, u);
		}
	};

	dfs2(1, 0);
	for (i64 i = 1; i <= n; i++) {
		std::cout << dp2[i] << "\n";
	}

	return 0;
}