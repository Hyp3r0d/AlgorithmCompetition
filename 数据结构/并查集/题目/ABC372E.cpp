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
const i64 mod = 1e9 + 7;
const i64 maxn = 2e5 + 5;
const i64 inf = 0x3f3f3f3f3f3f3f3f;

i64 fa[maxn];
std::set<i64>st[maxn];

i64 find(i64 x) {
	if (x == fa[x])return x;
	i64 tmp = find(fa[x]);
	fa[x] = tmp;
	return fa[x];
}

void merge(i64 x, i64 y) {
	x = find(x), y = find(y);
	if (x == y)return;
	fa[x] = y; 
	for (auto c : st[x]) {
		if (st[y].size() < 10)st[y].insert(c);
		else {
			if ((*st[y].begin()) < c) {
				st[y].erase(st[y].begin());
				st[y].insert(c);
			}
		}
	}
}

int main() {
	i64 n, q; std::cin >> n >> q;
	std::iota(fa + 1, fa + 1 + n, 1ll);
	for (i64 i = 1; i <= n; i++)st[i].insert(i);
	while (q--) {
		i64 opt, u, v; std::cin >> opt >> u >> v;
		if (opt == 1) {
			merge(u, v);
		} else if (opt == 2) {
			i64 z = find(u);
			if (st[z].size() < v) {
				puts("-1");
			} else {
				auto it = st[z].end(); it--;
				i64 cnt = 0;
				for (;; it--) {
					cnt++; if (cnt == v)break;
				}
				std::cout << (*it) << "\n";
			}
		}
	}
	//merge(1, 2); merge(2, 3); merge(3, 4);
	return 0;
}