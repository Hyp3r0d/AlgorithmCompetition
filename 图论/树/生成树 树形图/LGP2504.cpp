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

i64 dis[maxn];
std::pair<i64, i64>cord[maxn];
i64 fa[maxn];

i64 find(i64 x) {
	if (x == fa[x])return x;
	i64 f = find(fa[x]);
	fa[x] = f;
	return fa[x];
}

bool same(i64 x, i64 y) {
	return find(x) == find(y);
}

void merge(i64 x, i64 y) {
	if (same(x, y))return;
	x = find(x), y = find(y);
	fa[x] = y;
	return;
}


int main() {
	i64 m, n; std::cin >> m;
	for (i64 i = 1; i <= m; i++)std::cin >> dis[i];
	std::vector<tuple<i64, i64, f64>>edges;
	std::cin >> n;
	for (i64 i = 1; i <= n; i++) {
		std::cin >> cord[i].first >> cord[i].second;
	}
	for (i64 i = 1; i <= n; i++) {
		for (i64 j = i + 1; j <= n; j++) {
			auto [x1, y1] = cord[i];
			auto [x2, y2] = cord[j];
			f64 d = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
			edges.push_back({i, j, d});
		}
	}
	std::iota(fa + 1, fa + 1 + n, 1ll);
	std::sort(edges.begin(), edges.end(), [&](auto a, auto b)->bool{
		return get<2>(a) < get<2>(b);
	});
	i64 cnt = 0; f64 ans = 0;
	for (auto [u, v, w] : edges) {
		if (same(u, v))continue;
		merge(u, v);
		ans = std::max(ans, w);
		cnt++; if (cnt == n - 1)break;
	}
	i64 z = 0;
	for (i64 i = 1; i <= m; i++) {
		if (dis[i] >= ans)z++;
	}
	std::cout << z << "\n";
	return 0;
}