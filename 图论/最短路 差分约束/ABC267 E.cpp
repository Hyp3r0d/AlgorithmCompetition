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
	std::vector<i64>a(n + 1);
	for (i64 i = 1; i <= n; i++) {
		std::cin >> a[i];
	}

	std::vector<std::vector<i64>>g(n + 1);
	std::vector<i64>t(n + 1);
	for (i64 i = 1; i <= m; i++) {
		i64 u, v; std::cin >> u >> v;
		g[u].push_back(v);
		t[u] += a[v];
		t[v] += a[u];
		g[v].push_back(u);
	}

	std::priority_queue<pair<i64, i64>>pq;
	for (i64 i = 1; i <= n; i++) {
		pq.push({t[i], i});
	}
	i64 ans = 0;
	std::vector<bool>vis(n + 1);
	while (pq.size()) {
		auto [d, u] = pq.top(); pq.pop();
		if (vis[u])continue;
		ans = std::max(ans, d);
		vis[u] = true;
		for (auto v : g[u]) {
			if (vis[v])continue;
			t[v] -= a[u];
			pq.push({t[v], v});
		}
	}
	std::cout << ans << "\n";
}