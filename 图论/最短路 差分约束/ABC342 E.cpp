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

constexpr i64 mod = 999911659;
constexpr i64 maxn = 2e5 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;




std::vector<std::array<i64, 5>>g[maxn];

int main() {

	i64 n, m; std::cin >> n >> m;
	std::priority_queue<std::pair<i64, i64>>q;
	for (i64 i = 1; i <= m; i++) {
		i64 l, d, k, c, a, b;
		std::cin >> l >> d >> k >> c >> a >> b;
		g[b].push_back({a, c, l, d, k});
	}
	std::vector<i64>vis(2 * n + 5, false);
	std::vector<i64>dis(2 * n + 5, 0);
	dis[n] = inf;
	q.push({dis[n], n});
	while (q.size()) {
		i64 u = q.top().second;
		q.pop();
		vis[u] = true;
		for (auto [v, w, l, d, k] : g[u]) {
			if (dis[u] - w < l)continue;
			i64 x = std::min((dis[u] - w - l) / d, k - 1) * d + l;
			if (x > dis[v]) {
				dis[v] = x;
				if (not vis[v]) {
					q.push({dis[v], v});
				}
			}
		}
	}
	for (i64 i = 1; i < n; i++) {
		if (dis[i] == 0) {
			puts("Unreachable");
		} else {
			std::cout << dis[i] << "\n";
		}
	}
}
