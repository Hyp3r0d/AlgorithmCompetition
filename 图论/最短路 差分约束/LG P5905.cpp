/* Johnson 全源最短路算法*/
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
constexpr i64 maxn = 6e3 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


i64 head[5005]; i64 cnt = 0;
i64 d[5005], dis[5005], dep[5005];

bool vis[5005];
struct edge {
	i64 u, v, w, nxt;
} g[10005];

struct cmp {
	bool operator()(const pair<i64, i64>& x, const pair<i64, i64>&y)const {
		return x.first > y.first;
	}
};

void addedge(i64 u, i64 v, i64 w) {
	g[cnt].u = u; g[cnt].v = v; g[cnt].w = w;
	g[cnt].nxt = head[u];
	head[u] = cnt++	;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nui64ptr);
	cout.tie(nui64ptr);
	i64 n, m; std::cin >> n >> m;
	memset(head, 0xff, sizeof(head));
	for (i64 i = 1; i <= m; i++) {
		i64 u, v, w; std::cin >> u >> v >> w;
		addedge(u, v, w);
	}
	for (i64 i = 1; i <= n; i++) {
		addedge(0, i, 0);
	}

	auto spfa = [&](i64 s) {
		std::queue<i64>q; q.push(s);
		for (i64 i = 0; i <= n; i++) {
			d[i] = inf;
		}
		d[s] = 0, vis[s] = 1;
		while (q.size()) {
			auto u = q.front(); q.pop();
			vis[u] = false;
			for (auto cur = head[u]; cur != -1; cur = g[cur].nxt) {
				i64 v = g[cur].v;
				i64 w = g[cur].w;
				if (d[v] > d[u] + w) {
					d[v] = d[u] + w;
					if (not vis[v]) {
						vis[v] = true; q.push(v);
						dep[v]++;
						if (dep[v] == n + 1)return false;
					}
				}
			}
		}
		return true;
	};
	auto dijkstra = [&](i64 s) {
		std::priority_queue<pair<i64, i64>, vector<pair<i64, i64>>, cmp>q;
		for (i64 i = 0; i <= n; i++) {
			dis[i] = inf, vis[i] = false;
		}

		dis[s] = 0;
		q.push({0, s});
		while (q.size()) {
			auto [_, u] = q.top(); q.pop();
			if (vis[u])continue;
			vis[u] = true;
			for (i64 cur = head[u]; cur != -1; cur = g[cur].nxt) {
				i64 v = g[cur].v;
				i64 w = g[cur].w;
				if (dis[v] > dis[u] + w) {
					dis[v] = dis[u] + w;
					if (not vis[v]) {
						q.push({dis[v], v});
					}
				}
			}
		}
	};
	if (not spfa(0)) {
		puts("-1"); return 0;
	}
	for (i64 u = 1; u <= n; u++) {
		for (i64 cur = head[u]; cur != -1; cur = g[cur].nxt) {
			i64 v = g[cur].v;
			g[cur].w += d[u] - d[v];
		}
	}
	i64 tmp = 1e9;
	for (i64 i = 1; i <= n; i++) {
		dijkstra(i); i64 ans = 0;
		for (i64 j = 1; j <= n; j++) {
			if (dis[j] == inf) {
				ans += j * tmp;
			} else {
				ans += j * (dis[j] + d[j] - d[i]); // 后者是i - j 的最短路
			}
		}
		std::cout << ans << "\n";
	}
	return 0;
}