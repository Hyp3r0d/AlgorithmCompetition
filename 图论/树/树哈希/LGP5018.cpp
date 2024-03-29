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
constexpr i64 maxn = 5e2 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


int main() {
	srand(time(0));
	u64 mask = rand() % 1000005;
	auto shift = [&](u64 x) {
		x ^= mask;
		x ^= (x << 13);
		x ^= (x >> 7);
		x ^= (x << 17);
		x ^= mask;
		return x;
	};
	i64 n; std::cin >> n;
	std::vector<u64>hash(n + 5, 0ll), v(n + 5);
	for (i64 i = 1; i <= n; i++) {
		std::cin >> v[i];
	}
	std::vector<i64>sz(n + 1);
	std::vector<pair<i64, i64>>g(n + 1);
	for (i64 i = 1; i <= n; i++) {
		i64 l, r; std::cin >> l >> r;
		if (l < 0)l = 0; if (r < 0)r = 0;
		g[i] = {l, r};
	}
	i64 ans = 0;
	std::function<void(i64)>dfs = [&](i64 i) {
		hash[i] = v[i];
		sz[i] = 1;
		if (g[i].first)dfs(g[i].first), hash[i] += shift(hash[g[i].first]), sz[i] += sz[g[i].first];
		if (g[i].second)dfs(g[i].second), hash[i] += shift(hash[g[i].second]), sz[i] += sz[g[i].second];
		if (sz[g[i].first] == sz[g[i].second] and hash[g[i].first] == hash[g[i].second]) {
			ans = std::max(ans, sz[i]);
		}
	};
	dfs(1);
	std::cout << ans << "\n";
	return 0;
}