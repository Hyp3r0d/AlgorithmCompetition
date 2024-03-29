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

constexpr i64 mod = 999911659;
constexpr i64 maxn = 1e5 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


i64 P;

i64 sz[maxn], son[maxn], top[maxn], rk[maxn], w[maxn], dfn[maxn];
i64 cnt = 0, dep[maxn], fa[maxn];
std::vector<i64>g[maxn];


struct Node {
	i64 l, r, sum, add;
} tr[maxn * 4 + 5];

void dfs1(i64 u, i64 f) {
	dep[u] = dep[f] + 1;
	fa[u] = f;
	son[u] = -1, sz[u] = 1;
	for (auto v : g[u]) {
		if (v == f)continue;
		dfs1(v, u);
		sz[u] += sz[v];
		if (son[u] == -1 or sz[v] > sz[son[u]]) {
			son[u] = v;
		}
	}
}

void dfs2(i64 u, i64 t) {
	top[u] = t;
	cnt++; dfn[u] = cnt;
	rk[cnt] = u;
	if (son[u] == -1)return;
	dfs2(son[u], t);
	for (auto v : g[u]) {
		if (v == fa[u])continue;
		if (v == son[u])continue;
		dfs2(v, v);
	}
}

void pushUp(i64 p) {
	tr[p].sum = (tr[p << 1].sum % P + tr[p << 1 | 1].sum % P) % P;
}

void build(i64 p, i64 l, i64 r) {
	tr[p].l = l; tr[p].r = r;
	if (l == r) {
		tr[p].sum = w[rk[l]];
		return;
	}
	i64 mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	pushUp(p);
}


void pushDown(i64 p) {
	i64 ad = tr[p].add;
	tr[p].add = 0;
	tr[p << 1].add = (tr[p << 1].add % P + ad) % P;
	tr[p << 1 | 1].add = (tr[p << 1 | 1].add % P + ad) % P;
	i64 len1 = (tr[p << 1].r - tr[p << 1].l + 1);
	i64 len2 = (tr[p << 1 | 1].r - tr[p << 1 | 1].l + 1);
	tr[p << 1].sum = (tr[p << 1].sum % P + len1 % P * ad % P) % P;
	tr[p << 1 | 1].sum = (tr[p << 1 | 1].sum % P + len2 % P * ad % P) % P;
}

void add(i64 p, i64 l, i64 r, i64 v) {
	if (tr[p].l >= l and tr[p].r <= r) {
		tr[p].add = (tr[p].add % P + v) % P;
		tr[p].sum = (tr[p].sum % P + (tr[p].r - tr[p].l + 1) % P * v % P) % P;
		return;
	}
	pushDown(p);
	i64 mid = (tr[p].l + tr[p].r) >> 1;
	if (l <= mid) {
		add(p << 1, l, r, v);
	}
	if (r > mid) {
		add(p << 1 | 1, l, r, v);
	}
	pushUp(p);
}


i64 query(i64 p, i64 l, i64 r) {
	if (tr[p].l >= l and tr[p].r <= r) {
		return tr[p].sum;
	}
	i64 ret = 0;
	pushDown(p);
	i64 mid = (tr[p].l + tr[p].r) >> 1;;
	if (r > mid) {
		ret = (ret % P + query(p << 1 | 1, l, r)) % P;
	}
	if (l <= mid) {
		ret = (ret % P + query(p << 1, l, r)) % P;
	}
	return ret % P;
}



i64 querySum(i64 x, i64 y) {
	i64 ret = 0, fx = top[x], fy = top[y];
	while (fx != fy) {
		if (dep[fx] >= dep[fy]) {
			ret = (ret % P + query(1, dfn[fx], dfn[x])) % P;
			x = fa[fx];
		} else {
			ret = (ret % P + query(1, dfn[fy], dfn[y])) % P;
			y = fa[fy];
		}
		fx = top[x], fy = top[y];
	}
	if (dfn[x] < dfn[y]) {
		ret = (ret % P + query(1, dfn[x], dfn[y])) % P;
	} else {
		ret = (ret % P + query(1, dfn[y], dfn[x])) % P;
	}
	return ret % P;
}


void Change(i64 x, i64 y, i64 v) {
	i64 fx = top[x], fy = top[y];
	while (fx != fy) {
		if (dep[fx] >= dep[fy]) {
			add(1, dfn[fx], dfn[x], v);
			x = fa[fx];
		} else {
			add(1, dfn[fy], dfn[y], v);
			y = fa[fy];
		}
		fx = top[x], fy = top[y];
	}
	if (dfn[x] < dfn[y]) {
		add(1, dfn[x], dfn[y], v);
	} else {
		add(1, dfn[y], dfn[x], v);
	}
}

int main() {
	i64 n, m, r; std::cin >> n >> m >> r >> P;
	for (i64 i = 1; i <= n; i++) {
		std::cin >> w[i];
	}
	for (i64 i = 1; i <= n - 1; i++) {
		i64 x, y; std::cin >> x >> y;
		g[x].push_back(y); g[y].push_back(x);
	}
	dfs1(r, r); dfs2(r, r);
	build(1, 1, n);
	while (m--) {
		i64 opt; std::cin >> opt;
		if (opt == 1) {
			i64 x, y, z; std::cin >> x >> y >> z;
			Change(x, y, z);
		} else if (opt == 2) {
			i64 x, y; std::cin >> x >> y;
			std::cout  << querySum(x, y) % P << "\n";;
		} else if (opt == 3) {
			i64 x, z; std::cin >> x >> z;
			add(1, dfn[x], dfn[x] + sz[x] - 1, z);
		} else {
			i64 x; std::cin >> x;
			std::cout  << query(1, dfn[x], dfn[x] + sz[x] - 1) % P << "\n";;
		}
	}
}
