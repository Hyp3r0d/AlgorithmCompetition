/*树上重心 : 其余点到该点的距离和最小, 且一棵树最多有两个*/
/* 无论带权树还是无权树, 采用换根 dp的方法求重心*/

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
constexpr i64 maxn = 1e5 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;



i64 w[maxn], dp[maxn]; i64 n;

i64 sz[maxn];
vector<i64>g[maxn];


void dfs(i64 u, i64 f) {
	sz[u] = w[u];
	for (auto v : g[u]) {
		if (v == f)continue;
		dfs(v, u);
		dp[u] += sz[v] + dp[v];
		sz[u] += sz[v];
	}
}

i64 ans[maxn]; i64 tot = 0;
void dfs2(i64 u, i64 f) {
	ans[u] = dp[u];
	for (auto v : g[u]) {
		if (v == f)continue;
		dp[v] += (dp[u] - dp[v] - sz[v]) + (tot - sz[v]);
		sz[v] = tot;
		dfs2(v, u);
	}
}
int main() {
	std::cin >> n;
	for (i64 i = 1; i <= n; i++) {
		i64 u, v;
		std::cin >> w[i] >> u >> v;
		if (u)
			g[i].push_back(u), g[u].push_back(i);
		if (v)
			g[i].push_back(v), g[v].push_back(i);
	}
	tot = accumulate(w + 1, w + 1 + n, 0ll);
	dfs(1, 0);
	dfs2(1, 0);
	i64 rt = 1;
	std::cout << *min_element(ans + 1, ans + 1 + n);
	return 0;
}