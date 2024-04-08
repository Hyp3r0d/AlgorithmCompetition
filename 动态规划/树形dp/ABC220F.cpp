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

constexpr i64 mod = 998244353;
constexpr i64 maxn = 2e5 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


i64 n; std::vector<i64>g[maxn];

i64 dp[maxn], sz[maxn];

void dfs(i64 u, i64 f) {
	sz[u] = 1;
	for (auto v : g[u]) {
		if (v == f)continue;
		dfs(v, u);
		dp[u] += dp[v] + sz[v];
		sz[u] += sz[v];
	}
}

i64 ans[maxn];
void dfs2(i64 u, i64 f) {
	ans[u] = dp[u];
	for (auto v : g[u]) {
		if (v == f)continue;
		i64 tmp = sz[v];
		sz[v] += sz[u] - sz[v];
		dp[v] += (dp[u] - dp[v] - tmp) + (sz[u] - tmp);
		dfs2(v, u);
	}
}
int main() {
	std::cin >> n;
	for (i64 i = 1; i <= n - 1; i++) {
		i64 u, v; std::cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1, 0); dfs2(1, 0);
	for (i64 i = 1; i <= n; i++) {
		std::cout << ans[i] << "\n";
	}
	return 0;
}