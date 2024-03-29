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
constexpr i64 maxn = 2e5 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

i64 c[maxn]; i64 r[maxn], l[maxn];
std::unordered_map<i64, i64>cnt;
i64 z[maxn]; i64 dfn = 0;
i64 big[maxn], sz[maxn];
std::vector<i64>g[maxn];


i64 tot = 0; i64 ans[maxn];
void add(i64 u) {
	cnt[c[u]]++;
	if (cnt[c[u]] == 1)tot++;
}


void del(i64 u) {
	cnt[c[u]]--;
	if (cnt[c[u]] == 0)tot--;
}


void dfs1(i64 u, i64 f) {
	z[++dfn] = u;
	l[u] = dfn;
	sz[u] = 1;
	for (auto v : g[u]) {
		if (v == f)continue;
		dfs1(v, u);
		sz[u] += sz[v];
		if (big[u] == 0 or sz[v] > sz[big[u]]) {
			big[u] = v;
		}
	}
	r[u] = dfn;
}


void dfs2(i64 u, i64 f, bool k) {
	for (auto v : g[u]) {
		if (v != f and v != big[u]) {
			dfs2(v, u, false);
		}
	}
	if (big[u] != 0) {
		dfs2(big[u], u, true);
	}
	for (auto v : g[u]) {
		if (v == f or v == big[u])continue;
		for (i64 i = l[v]; i <= r[v]; i++) {
			add(z[i]);
		}

	}
	add(u);
	ans[u] = tot;
	if (not k) {
		for (i64 i = l[u]; i <= r[u]; i++) {
			del(z[i]);
		}
	}
}

void solve() {
	i64 n; std::cin >> n;

	for (i64 i = 1; i <= n - 1; i++) {
		i64 u, v; std::cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	for (i64 i = 1; i <= n; i++) {
		std::cin >> c[i];
	}

	dfs1(1, 0);

	dfs2(1, 0, false);

	i64 m; std::cin >> m;

	for (i64 i = 1; i <= m; i++) {
		i64 q; std::cin >> q;
		std::cout << ans[q] << "\n";
	}
}
int main() {
	solve();
	return 0;
}


