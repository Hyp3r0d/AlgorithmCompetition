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
const i64 maxn = 2e5 + 5;
const i64 inf = 0x3f3f3f3f3f3f3f3f;


i64 fa[maxn];

i64 find(i64 x) {
	if (x == fa[x])return x;
	i64 tmp = find(fa[x]);
	fa[x] = tmp;
	return tmp;

}

bool same(i64 x, i64 y) {
	return find(x) == find(y);
}

void merge(i64 x, i64 y) {
	x = find(x), y = find(y);
	fa[x] = y;
}
int main() {
	i64 n, m; std::cin >> n >> m;
	std::iota(fa + 1, fa + 1 + n, 1ll);
	std::vector<pair<i64, std::vector<i64>>>g(m + 1);
	for (i64 i = 1; i <= m; i++) {
		i64 k; std::cin >> k >> g[i].first;
		g[i].second = vector<i64>(k + 1);
		for (i64 j = 1; j <= k; j++)std::cin >> g[i].second[j];
	}
	std::sort(g.begin() + 1, g.begin() + 1 + m, [&](auto x, auto y)->bool{
		return x.first < y.first;
	});
	i64 cnt = 0;
	i64 res = 0;
	for (i64 i = 1; i <= m; i++) {
		i64 c = g[i].first;
		for (i64 j = 1; j < g[i].second.size(); j++) {
			g[i].second[j] = find(g[i].second[j]);
		}
		std::sort(g[i].second.begin() + 1, g[i].second.end());
		i64 len = unique(g[i].second.begin() + 1, g[i].second.end()) - g[i].second.begin() - 1;
		res += c * (len - 1);
		cnt += len - 1;
		for (i64 j = 1; j < len; j++) {
			merge(g[i].second[j], g[i].second[j + 1]);
		}
	}
	if (cnt < n - 1) {
		puts("-1"); return 0;
	}
	std::cout << res << "\n";

	return 0;
}