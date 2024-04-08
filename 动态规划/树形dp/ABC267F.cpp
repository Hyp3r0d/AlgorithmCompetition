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
	int n; std::cin >> n;
	std::vector<vector<int>>g(n + 1); auto query = g;
	for (int i = 1; i <= n - 1; i++) {
		int u, v; std::cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	i64 q; std::cin >> q;
	std::vector<int>dis(q + 1);
	for (int i = 1; i <= q; i++) {
		int u; std::cin >> u >> dis[i];
		query[u].push_back(i);
	}
	int len = 0;
	std::vector<int>z(n + 1);
	std::vector<int>ans(q + 1);
	std::function<void(int, int, int)>dfs = [&](int u, int f, int dep) {
		z[dep] = u;
		for (auto q : query[u]) {
			if (dep >= dis[q]) {
				ans[q] = z[dep - dis[q]];
			}
		}
		len = std::max(len, dep);
		for (auto v : g[u]) {
			if (v != f)dfs(v, u, dep + 1);
		}
	};
	for (int turn : {0, 1, 2}) {
		int pos = z[len]; len = 0;
		if (!turn)pos = 1;
		dfs(pos, 0, 0);
	}
	for (int i = 1; i <= q; i++) {
		std::cout << (ans[i] ? ans[i] : -1) << "\n";
	}
	return 0;
}