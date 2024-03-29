
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
constexpr i64 maxn = 5e4 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


std::vector<i64>g[maxn]; i64 dep[maxn];
i64 fa[maxn][20], d[maxn];
int main() {
	i64 n, k; std::cin >> n >> k;
	for (i64 i = 1; i <= n - 1; i++) {
		i64 u, v; std::cin >> u >> v;
		g[u].push_back(v); g[v].push_back(u);
	}
	std::function<void(i64, i64)>dfs1 = [&](i64 u, i64 f) {
		fa[u][0] = f;
		dep[u] = dep[fa[u][0]] + 1;
		for (i64 i = 1; (1 << i) <= dep[u]; i++) {
			fa[u][i] = fa[fa[u][i - 1]][i - 1];
		}
		for (auto v : g[u]) {
			if (v == f)continue;
			dfs1(v, u);
		}
	};
	dfs1(1, 0);
	auto lca = [&](i64 u, i64 v) {
		if (dep[u] < dep[v])std::swap(u, v);
		if (dep[u] != dep[v]) {
			for (i64 i = log2(dep[u] - dep[v]); i >= 0; i--) {
				if (dep[fa[u][i]] >= dep[v]) {
					u = fa[u][i];
				}
			}
		}
		if (u == v)return u;
		for (i64 i = log2(dep[u]); i >= 0; i--) {
			if (fa[u][i] != fa[v][i]) {
				u = fa[u][i]; v = fa[v][i];
			}
		}
		if (u != v) {
			u = fa[u][0];
			v = fa[v][0];
		}
		return u;
	};
	while (k--) {
		i64 u, v; std::cin >> u >> v;
		d[u]++; d[v]++;
		i64 z = lca(u, v);
		d[z]--; d[fa[z][0]]--;
	}
	std::function<void(i64 , i64 )>dfs = [&](i64 u, i64 f) {
		for (auto v : g[u]) {
			if (v == f)continue;
			dfs(v, u);
			d[u] += d[v];
		}
	};
	dfs(1, 0);
	std::cout  << *std::max_element(d + 1, d + 1 + n) << "\n";;
}