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

constexpr i64 mod = 45989;
constexpr i64 maxn = 3e4 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

i64 dis[maxn]; bool vis[maxn];
std::vector<pair<i64, i64>>g[maxn];
i64 n, m;
int main() {
	i64 n, m; std::cin >> n >> m;
	for (i64 i = 1; i <= m; i++) {
		i64 u, v, w; std::cin >> u >> v >> w;
		g[u].push_back({v, w});
	}
	queue<i64>q;
	std::fill(dis + 1, dis + 1 + n, -inf);
	q.push(1); vis[1] = true; dis[1] = 0;
	while (q.size()) {
		auto u = q.front(); q.pop(); vis[u] = false;
		for (auto [v, w] : g[u]) {
			if (dis[v] < dis[u] + w) {
				dis[v] = dis[u] + w;
				if (not vis[v]) {
					q.push(v);
					vis[v] = true;
				}
			}
		}
	}
	std::cout << ((dis[n] == -inf) ? -1 : dis[n]);
	return 0;
}
