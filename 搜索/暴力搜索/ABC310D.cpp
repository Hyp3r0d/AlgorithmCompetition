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

constexpr i64 mod = 998244353;
constexpr i64 maxn = 4e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


std::vector<i64>g[15]; std::set<i64>st[15];
int main() {
	i64 n, t, m; std::cin >> n >> t >> m;

	for (i64 i = 1; i <= m; i++) {
		i64 u, v; std::cin >> u >> v;
		g[u].push_back(v); g[v].push_back(u);
	}
	i64 cur = 0, ans = 0;
	std::function<void(i64)>dfs = [&](i64 idx)  {
		if (n - idx + 1 < t - cur) {
			return;
		}
		if (idx == n + 1) {
			if (cur == t) {
				ans++;
			}
			return;
		}
		for (i64 i = 1; i <= cur; i++) {
			bool f = true;
			for (auto v : g[idx]) {
				if (st[i].count(v)) {
					f = false; break;
				}
			}
			if (f) {
				st[i].insert(idx); dfs(idx + 1);
				st[i].erase(idx);
			}
		}
		if (cur < t) {
			cur++; st[cur].insert(idx); dfs(idx + 1);
			st[cur].clear();
			cur--;
		}
	};
	dfs(1); std::cout << ans << "\n";

	return 0;
}