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
const i64 mod = 998244353;
const i64 maxn = 2e5 + 5;
const i64 inf = 0x3f3f3f3f3f3f3f3f;


int main() {
	i64 n, k; std::cin >> n >> k;
	std::vector<i64>d(n + 1);
	std::vector<vector<i64>>g(n + 1);
	for (i64 i = 1; i <= n - 1; i++) {
		i64 u, v; std::cin >> u >> v; d[u]++; d[v]++;
		g[u].push_back(v); g[v].push_back(u);
	}
	std::vector<bool>p(n + 1), vis(n + 1);
	while (k--) {
		i64 u; std::cin >> u; p[u] = true;
	}
	queue<i64>q;
	for (i64 i = 1; i <= n; i++)if (d[i] == 1 and not p[i])q.push(i);
	while (q.size()) {
		auto u = q.front(); q.pop(); vis[u] = true;
		for (auto v : g[u]) {
			d[v]--;
			if (d[v] == 1 and not p[v])q.push(v);
		}
	}
	i64 ans = 0;
	for (i64 i = 1; i <= n; i++)if (not vis[i])ans++;
	std::cout << ans << "\n";
	return 0;
}