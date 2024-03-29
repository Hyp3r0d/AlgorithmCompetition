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

constexpr i64 mod = 45989;
constexpr i64 maxn = 3e4 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;



i64 fa[maxn], sz[maxn], dis[maxn];

i64 find(i64 x) {
	if (x == fa[x])return x;
	i64 f = find(fa[x]);
	dis[x] += dis[fa[x]];
	return fa[x] = f;
}
int main() {
	i64 t; std::cin >> t;
	std::iota(fa + 1, fa + 1 + 30000, 1ll);
	std::fill(sz + 1, sz + 1 + 30000, 1ll);

	while (t--) {
		char opt; std::cin >> opt;
		if (opt == 'M') {
			i64 x, y; std::cin >> x >> y;
			i64 fx = find(x), fy = find(y);
			dis[fx] += sz[fy];
			fa[fx] = fy;
			sz[fy] += sz[fx];
			sz[fx] = 0;
		} else {
			i64 x, y; std::cin >> x >> y;
			i64 fx = find(x), fy = find(y);
			if (fx != fy) {
				puts("-1");
			} else {
				std::cout << abs(dis[x] - dis[y]) - 1 << "\n";
			}
		}
	}
}