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
constexpr i64 maxn = 2e3 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


struct z {
	i64 w, v; f64 p;
} g[maxn];
int main() {
	i64 n, W; std::cin >> n >> W;
	for (i64 i = 1; i <= n; i++) {
		std::cin >> g[i].w >> g[i].v;
		g[i].p = ((f64)g[i].v) / (g[i].w + 0.0);
	}
	sort(g + 1, g + 1 + n, [&](auto x, auto y)->bool{
		return x.p > y.p;
	});
	auto f = [&](i64 t, i64 v)->i64 {
		i64 tot = 0;
		for (i64 i = 1; t + i <= n; i++) {
			if (v >= g[t + i].w) {
				v -= g[t + i].w;
				tot += g[t + i].v;
			} else {
				return tot + v * g[t + i].p;
			}
		}
		return tot;
	};
	i64 ans = 0;
	std::function<void(i64, i64, i64)>dfs = [&](i64 t, i64 p, i64 v) {
		ans = std::max(ans, v);
		if (t > n)return;
		if (f(t, p) + v > ans) {
			dfs(t + 1, p, v);// 不选
		}
		if (g[t].w <= p) {
			dfs(t + 1, p - g[t].w, v + g[t].v);
			// 选了
		}
	};
	dfs(1, W, 0);
	std::cout << ans << "\n";
	return 0;
}