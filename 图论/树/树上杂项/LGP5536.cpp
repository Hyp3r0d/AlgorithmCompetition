/*两次dfs找一条树的直径*/
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
constexpr i64 maxn = 1e5 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

/* 找树上直径的中心, 贪心地选择以他为根前 k 高的*/
i64 dep[maxn]; i64 fa[maxn];

i64 rt = 1; i64 bs = 0;
vector<i64>g[maxn];
void dfs(i64 u, i64 f) {
	dep[u] = dep[f] + 1;
	fa[u] = f;
	if (dep[u] > dep[bs]) {
		bs = u;
	}
	for (auto v : g[u]) {
		if (v == f)continue;
		dfs(v, u);
	}
}

i64 maxdep[maxn];
void dfs2(i64 u, i64 f) {
	dep[u] = dep[f] + 1;
	maxdep[u] = dep[u];
	for (auto v : g[u]) {
		if (v == f)continue;
		dfs2(v, u);
		maxdep[u] = std::max(maxdep[u], maxdep[v]);
	}
}
int main() {
	i64 n, k; std::cin >> n >> k;
	for (i64 i = 1; i <= n - 1; i++) {
		i64 u, v; std::cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	dfs(rt, 0);
	rt = bs; bs = 0;
	memset(dep, 0, sizeof(dep));
	dfs(rt, 0);
	i64 d = dep[bs] / 2;
	i64 cur = bs;
	while (d--) {
		cur = fa[cur];
	}
	memset(dep, 0, sizeof(dep));
	dfs2(cur, 0);
	vector<i64>ans(n + 1);
	for (i64 i = 1; i <= n; i++)ans[i] = maxdep[i] - dep[i];
	sort(ans.begin() + 1, ans.begin() + 1 + n, [&](i64 x, i64 y)->bool{
		return x > y;
	});
	i64 z = 0;
	for (i64 i = k + 1; i <= n; i++) {
		z = std::max(z, ans[i] + 1);
	}
	std::cout << z << "\n";
}