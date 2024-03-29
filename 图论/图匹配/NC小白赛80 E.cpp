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

void solve() {
	i64 n; std::cin >> n;
	std::vector<i64>a(n + 1), b(n + 1);
	std::vector<std::vector<i64>>g(n + 1);
	for (i64 i = 1; i <= n; i++) {
		std::cin >> a[i];
	}
	for (i64 i = 1; i <= n; i++) {
		std::cin >> b[i];
	}
	for (i64 i = 1; i <= n; i++) {
		for (i64 j = 1; j <= n; j++) {
			if (__gcd(a[i], b[j]) == 1) {
				g[i].push_back(j + n);
			}
		}
	}
	i64 dfn = 0;
	std::vector<i64>vis(n + 1);
	std::vector<i64>pa(n + 1), pb(2 * n + 1);
	function<bool(i64)>dfs = [&](i64 u) {
		vis[u] = dfn;

		for (auto v : g[u]) {
			if (not pb[v]) {
				pb[v] = u;
				pa[u] = v;
				return true;
			}
		}

		for (auto v : g[u]) {
			if (vis[pb[v]] != dfn and dfs(pb[v])) {
				pa[u] = v;
				pb[v] = u;
				return true;
			}
		}

		return false;
	};
	i64 res = 0;
	while (1) {
		dfn++; i64 cnt = 0;
		for (i64 i = 1; i <= n; i++) {
			if (not pa[i] and dfs(i))cnt++;
		}
		if (not cnt)break;
		res += cnt;
	}
	puts(res < n ? "Alice" : "Bob");
}
int main() {
	solve();
}