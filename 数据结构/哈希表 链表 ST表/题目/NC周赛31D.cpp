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

constexpr i64 mod = 1e9 + 7;
constexpr i64 maxn = 4e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

struct Node {
	i64 l, r, v;
} g[maxn];


std::unordered_map<i64, i64>pos;
i64 tot = 1;

void add(i64 x, i64 y) {
	if (y)y = pos[y];
	tot++; g[tot].v = x; pos[x] = tot;
	g[tot].r = g[y].r; g[g[y].r].l = tot;
	g[tot].l = y; g[y].r = tot;
}

void remove(i64 x) {
	x = pos[x];
	g[g[x].l].r = g[x].r;
	g[g[x].r].l = g[x].l;
}

int main() {
	g[0].r = 1; g[1].l = 0;
	i64 n; std::cin >> n;
	while (n--) {
		i64 op; std::cin >> op;
		if (op == 1) {
			i64 x, y; std::cin >> x >> y;
			add(x, y);
		} else {
			i64 x; std::cin >> x;
			remove(x);
		}
	}
	std::vector<i64>ans;
	for (i64 i = g[0].r; i != 1; i = g[i].r) {
		ans.push_back(g[i].v);
	}
	std::cout << ans.size() << "\n";
	for (i64 i = 0; i < ans.size(); i++) {
		std::cout << ans[i] << " \n"[i == ans.size() - 1];
	}
	return 0;
}