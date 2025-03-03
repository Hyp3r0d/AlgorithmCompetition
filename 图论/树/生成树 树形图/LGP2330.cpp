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
constexpr i64 maxn = 2e3 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

struct cmp {
	bool operator()(const pair<i64, i64>&x, const pair<i64, i64>&y)const {
		return x.second > y.second;
	}
};

/*Prim算法求MST, 适用于稠密图*/
int main() {
	i64 n, m; std::cin >> n >> m;
	std::vector<std::vector<pair<i64, i64>>>g(n + 1);
	for (i64 i = 1; i <= m; i++) {
		i64 u, v, c; std::cin >> u >> v >> c;
		g[u].push_back({v, c});
		g[v].push_back({u, c});
	}
	std::priority_queue<std::pair<i64, i64>, std::vector<std::pair<i64, i64>>, cmp>pq;
	std::vector<bool>vis(n + 1); std::vector<i64>dis(n + 1);
	auto check = [&](i64 x) {
		i64 cnt = 0;
		while (pq.size())pq.pop();
		std::fill(dis.begin() + 1, dis.begin() + 1 + n, inf);
		std::fill(vis.begin() + 1, vis.begin() + 1 + n, false);
		dis[1] = 0;
		pq.push({1, 0});
		while (pq.size()) {
			if (cnt >= n)break;
			auto [u, d] = pq.top(); pq.pop();
			if (vis[u])continue;
			if (d > x)continue;
			vis[u] = true;
			cnt++;
			for (auto [v, w] : g[u]) {
				if (w < dis[v]) {
					dis[v] = w;
					pq.push({v, w});
				}
			}
		}
		return cnt == n;
	};
	i64 l = 0, r = 1e10 + 5;
	i64 ans = -1;
	while (l <= r) {
		i64 mid = (l + r) >> 1;
		if (check(mid))r = mid - 1, ans = mid;
		else l = mid + 1;
	}
	std::cout << n - 1 << " " << ans << "\n";
	return 0;
}