#include<bits/stdc++.h>
#include<sys/stat.h>
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
const i64 mod = 1e9 + 7;
const i64 maxn = 1e6 + 5;
const i64 inf = 0x3f3f3f3f3f3f3f3f;


i64 tr[10000020];
void add(i64 idx, i64 v) {
	for (; idx <= 10000010; idx += (idx & -idx))tr[idx] += v;
}

i64 query(i64 idx) {
	i64 ret = 0;
	for (; idx >= 1; idx -= (idx & -idx))ret += tr[idx];
	return ret;
}

i64 n, sum, rt, sz[maxn], mx[maxn], dis[maxn], k;

bool vis[maxn];

queue<i64>tag;

i64 ans = 0;

vector<pair<i64, i64>>g[maxn];

i64 d[maxn];
i64 cnt = 0;
int main() {
	std::cin >> n;
	for (i64 i = 1; i <= n - 1; i++) {
		i64 u, v, w; std::cin >> u >> v >> w;
		g[u].push_back({v, w});
		g[v].push_back({u, w});
	}
	std::cin >> k;
	mx[rt] = inf; sum = n;
	std::function<void(i64, i64)>dfs = [&](i64 u, i64 fa) {
		sz[u] = 1; mx[u] = 0;
		for (auto [v, w] : g[u]) {
			if (v == fa or vis[v])continue;
			dfs(v, u);
			mx[u] = std::max(mx[u], sz[v]);
			sz[u] += sz[v];
		}
		mx[u] = std::max(mx[u], sum - mx[u]);
		if (mx[u] < mx[rt])rt = u;
	};
	std::function<void(i64, i64)>cal = [&](i64 u, i64 fa) {
		d[++cnt] = dis[u];
		for (auto [v, w] : g[u]) {
			if (v != fa and not vis[v]) {
				dis[v] = dis[u] + w; cal(v, u);
			}
		}
	};
	std::function<void(i64, i64)>dfs2 = [&](i64 u, i64 fa) {
		tag.push(0); vis[u] = true;
		add(0 + 1, 1);
		for (auto [v, w] : g[u]) {
			if (v != fa and not vis[v]) {
				dis[v] = w;
				cal(v, u);
				for (i64 s = 1; s <= cnt; s++) {

					if (k >= d[s]) {

						ans += query(k - d[s] + 1);

					}
				}

				for (i64 s = 1; s <= cnt; s++) {
					if (d[s] <= 10000010) {
						tag.push(d[s]); add(d[s] + 1, 1);
					}
				}
				cnt = 0;
			}
		}
		while (tag.size())add(tag.front() + 1, -1), tag.pop();
		for (auto [v, w] : g[u]) {
			if (v != fa and not vis[v]) {
				sum = sz[v];
				rt = 0;
				mx[rt] = inf;
				dfs(v, u);
				dfs(rt, -1);
				dfs2(rt, u);
			}
		}
	};
	dfs(1, -1); dfs(rt, -1);
	dfs2(rt, -1);
	std::cout << ans << "\n";
	return 0;
}



