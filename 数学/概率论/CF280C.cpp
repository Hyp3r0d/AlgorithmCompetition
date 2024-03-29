
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
	i64 n; std::cin >> n;
	std::vector<std::vector<i64>>g(n + 1);
	for (i64 i = 1; i <= n - 1; i++) {
		i64 u, v; std::cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	std::vector<i64>dep(n + 1);
	f64 ans = 0.0;
	std::function<void(i64, i64)>dfs = [&](i64 u, i64 f) {
		dep[u] = dep[f] + 1;
		ans += 1.00 / (dep[u]);
		for (auto v : g[u]) {
			if (v == f)continue;
			dfs(v, u);
		}
	};
	dfs(1, 0);
	printf("%.6lf\n", ans);
	return 0;
}

