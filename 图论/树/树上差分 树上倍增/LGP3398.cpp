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
constexpr i64 maxn = 2e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


std::vector<i64>g[maxn];
i64 fa[maxn][30], dis[maxn][30];
i64 dep[maxn];

void dfs(i64 u, i64 f) {
	fa[u][0] = f;
	dep[u] = dep[fa[u][0]] + 1;
	for (i64 i = 1; (1 << i) <= dep[u]; i++) {
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
		dis[u][i] = dis[u][i - 1] + dis[fa[u][i - 1]][i - 1];
	}
	for (auto v : g[u]) {
		if (v == f)continue;
		dis[v][0] = 1;
		dfs(v, u);
	}
}


std::pair<i64, i64> lca(i64 u, i64 v) {
	i64 ret = 0;
	if (dep[u] < dep[v]) {
		swap(u, v);
	}
	if (dep[u] != dep[v]) {
		for (i64 i = log2(dep[u] - dep[v]); i >= 0; i--) {
			if (dep[fa[u][i]] >= dep[v]) {
				ret += dis[u][i];
				u = fa[u][i];
			}
		}
	}
	if (u == v) {
		return {u, ret};
	}
	for (i64 i = log2(dep[u]); i >= 0; i--) {
		if (fa[u][i] != fa[v][i]) {
			ret += dis[u][i];
			ret += dis[v][i];
			u = fa[u][i];
			v = fa[v][i];
		}
	}
	if (u != v) {
		ret += dis[u][0];
		ret += dis[v][0];
		u = fa[u][0];
		v = fa[v][0];
	}
	return {u, ret};
}

int main() {
	i64 n, q; std::cin >> n >> q;
	for (i64 i = 1; i <= n - 1; i++) {
		i64 u, v; std::cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1, 0);
	//std::cout << lca(3, 5).second << "\n";
	auto check = [&](i64 x, i64 u, i64 v) {
		auto [f, d1] = lca(x, u);
		auto [g, d2] = lca(x, v);
		auto [h, d3] = lca(u, v);
		return (d1 + d2) == d3;
	};
	while (q--) {
		i64 a, b, c, d;
		std::cin >> a >> b >> c >> d;
		auto [u, d1] = lca(a, b);
		auto [v, d2] = lca(c, d);
		if (check(u, c, d) or check(v, a, b)) {
			puts("Y");
		} else puts("N");
	}
	return 0;
}