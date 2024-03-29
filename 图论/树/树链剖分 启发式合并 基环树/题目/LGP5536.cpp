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

constexpr i64 mod = 1e9 + 7;
constexpr i64 maxn = 2e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


std::vector<i64>g[maxn];
i64 dep[maxn];
i64 fa[maxn];
i64 mdep[maxn];
i64 dcur = 0, cur = 0;
void dfs1(i64 u, i64 f) {
	if (dep[u] > dcur) {
		dcur = dep[u];
		cur = u;
	}
	for (auto v : g[u]) {
		if (v == f)continue;
		dep[v] = dep[u] + 1;
		dfs1(v, u);
	}
}


void dfs2(i64 u, i64 f) {
	if (dep[u] > dcur) {
		dcur = dep[u];
		cur = u;
	}
	for (auto v : g[u]) {
		if (v == f)continue;
		dep[v] = dep[u] + 1;
		fa[v] = u;
		dfs2(v, u);
	}
}

void dfs3(i64 u, i64 f) {
	mdep[u] = dep[u];
	for (auto v : g[u]) {
		if (v == f)continue;
		dep[v] = dep[u] + 1;
		dfs3(v, u);
		mdep[u] = std::max(mdep[u], mdep[v]);
	}
}
int main() {
	i64 n, k; std::cin >> n >> k;
	dfs1(1, 0);
	memset(dep, 0, sizeof(dep));
	dcur = 0;
	dfs2(dcur, 0);
	i64 z = dcur;
	for (i64 i = 1; i <= (dep[dcur] + 1) / 2; i++)dcur = fa[dcur];
	memset(dep, 0, sizeof(dep));
	dfs3(dcur, 0);
	std::vector<i64>ans(n + 1);
	for (i64 i = 1; i <= n; i++)ans[i] = mdep[i] - dep[i];
	std::sort(ans.begin() + 1, ans.begin() + 1 + n, [&](i64 x, i64 y)->bool{
		return x > y;
	});
	i64 res = 0;
	for (i64 i = k + 1; i <= n; i++) {
		res = std::max(res, ans[i] + 1);
	}
	std::cout << res << "\n";
}