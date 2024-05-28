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
const i64 maxn = 1e6 + 5;
const i64 inf = 0x3f3f3f3f3f3f3f3f;

std::vector<pair<i64, i64>>g[maxn]; i64 deg[maxn], U[maxn], c[maxn], deg2[maxn];
int main() {

	i64 n, p; std::cin >> n >> p;
	for (i64 i = 1; i <= n; i++) {
		std::cin >> c[i] >> U[i];

	}
	for (i64 i = 1; i <= p; i++) {
		i64 u, v, w; std::cin >> u >> v >> w;
		g[u].push_back({v, w});
		deg2[u]++;
		deg[v]++;
	}


	queue<i64>q; for (i64 i = 1; i <= n; i++) {
		if (not deg[i])q.push(i);
	}

	while (q.size()) {
		auto u = q.front(); q.pop();
		for (auto [v, w] : g[u]) {
			deg[v]--;
			c[v] += w * c[u];
			if (deg[v] == 0) {
				c[v] -= U[v];
				q.push(v);
			}
		}
	}
	std::vector<pair<i64, i64>>s;
	for (i64 i = 1; i <= n; i++) {
		if (c[i] > 0 and deg2[i] == 0) {
			s.push_back({i, c[i]});
		}
	}
	std::sort(s.begin(), s.end(), [&](auto x, auto y)->bool{
		return x.first < y.first;
	});
	for (auto [x, y] : s) {
		std::cout << x << " " << y << "\n";
	}

	return 0;
}