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

constexpr i64 mod = 999911659;
constexpr i64 maxn = 2e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;



i64 fa[maxn][30];
i64 dep[maxn], dis[maxn][30];
int main() {

	i64 n, m; std::cin >> n >> m;
	std::string z; std::cin >> z;
	z = " " + z;
	std::vector<std::vector<std::pair<i64, i64>>>g(n + 1);
	std::vector<i64>w(n + 1);
	for (i64 i = 1; i <= n; i++) {
		w[i] = (z[i] == 'G' ? 1 : 0);
	}
	for (i64 i = 1; i <= n - 1; i++) {
		i64 u, v; std::cin >> u >> v;
		g[u].push_back({v, w[u]}); g[v].push_back({u, w[v]});
	}

	std::function<void(i64, i64)>dfs = [&](i64 u, i64 f) {
		fa[u][0] = f;
		dep[u] = dep[fa[u][0]] + 1;
		for (i64 i = 1; (1 << i) <= dep[u]; i++) {
			fa[u][i] = fa[fa[u][i - 1]][i - 1];
			dis[u][i] = dis[u][i - 1] + dis[fa[u][i - 1]][i - 1];
		}
		for (auto [v, w] : g[u]) {
			if (v == f)continue;
			dfs(v, u);
			dis[v][0] = w;
		}
	};
	dfs(1, 0);
	auto lca = [&](i64 u, i64 v)->pair<i64, i64> {
		i64 ret = 0;
		if (dep[u] < dep[v]) {
			swap(u, v);
		}
		if (dep[u] != dep[v]) {
			for ( i64 i = log2(dep[u] - dep[v]); i >= 0; i--) {
				if (dep[fa[u][i]] >= dep[v]) {
					ret += dis[u][i];
					u = fa[u][i];
				}
			}
		}
		if (u == v) {
			return {ret, u};
		}
		for ( i64 i = log2(dep[u]); i >= 0; i--) {
			if (fa[u][i] != fa[v][i]) {
				ret += dis[u][i]; ret += dis[v][i];
				u = fa[u][i];
				v = fa[v][i];
			}
		}
		if (u != v) {
			u = fa[u][0];
			v = fa[v][0];
			ret += dis[u][0];
			ret += dis[v][0];
		}
		return {ret, u};
	};


	while (m--) {
		i64 x, y; char c;
		std::cin >> x >> y >> c;
		i64 f = (c == 'G' ? 1 : 0);
		auto [s, t] = lca(x, y);
		s += w[t];
		i64 len = dep[t] - dep[x] + dep[t] - dep[y] + 1;
		if ((s and f) or (not f and not (s == len))) {
			std::cout << 1;
		} else std::cout << 0;
	}

}
