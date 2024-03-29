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
constexpr i64 maxn = 5e4 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

struct edge {
	i64 u; i64 v; i64 w; i64 nxt;
} g[maxn];

i64 head[maxn]; i64 cnt = 0;
void addedge(i64 u, i64 v, i64 w) {
	g[cnt].u = u; g[cnt].v = v; g[cnt].w = w;
	g[cnt].nxt = head[u]; head[u] = cnt++;

}
i64 tot[maxn];
std::queue<i64>q; i64 dis[maxn]; bool vis[maxn];
int main() {
	i64 n, m; std::cin >> n >> m;
	memset(dis, -0x3f, sizeof(dis));
	memset(head, -1, sizeof(head));
	for (i64 i = 1; i <= m; i++) {
		i64 u, v, w; std::cin >> u >> v >> w;
		addedge(u, v, -w);
	}
	for (i64 i = 1; i <= n; i++) {
		addedge(0, i, 0);
	}
	q.push(0); vis[0] = true; dis[0] = 0;
	while (q.size()) {
		auto u = q.front(); q.pop(); vis[u] = false;
		for (i64 cur = head[u]; cur != -1; cur = g[cur].nxt) {
			i64 v = g[cur].v, w = g[cur].w;
			if (dis[u] + w > dis[v]) {
				dis[v] = dis[u] + w;
				tot[v] = tot[u] + 1;
				if (tot[v] >= n) {
					puts("NO SOLUTION"); return 0;
				}
				if (not vis[v]) {
					q.push(v); vis[v] = true;

				}
			}

		}
	}
	i64 cur = *min_element(dis + 1, dis + 1 + n);
	for (i64 i = 1; i <= n; i++) {
		dis[i] = dis[i] - cur;
		std::cout << dis[i] << "\n";
	}
	return 0;
}