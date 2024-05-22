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

constexpr i64 mod = 999911659;
constexpr i64 maxn = 2e5 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;



int main() {
	i64 n, m; std::cin >> n >> m;
	std::vector<i64>w(n), a(n);
	std::vector<std::vector<i64>>g(n);
	for (i64 i = 0; i < m; i++) {
		i64 u, v; std::cin >> u >> v;
		u--; v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (i64 i = 0; i < n; i++) {
		std::cin >> w[i];
	}
	for (i64 i = 0; i < n; i++)std::cin >> a[i];
	vector<i64>idx(n);
	std::iota(idx.begin(), idx.end(), 0);
	std::sort(idx.begin(), idx.end(), [&](i64 i, i64 j)->bool{
		return w[i] < w[j];
	});
	i64 ans = 0;
	std::vector<i64>s(n);
	for (auto u : idx) {
		std::vector<i64>dp(w[u]);
		for (auto v : g[u]) {
			if (w[v] > w[u])continue;
			for (i64 j = w[u] - 1; j >= w[v]; j--) {
				dp[j] = std::max(dp[j], dp[j - w[v]] + s[v]);
			}
		}
		s[u] = dp.back() + 1;
		ans += s[u] * a[u];
	}
	std::cout << ans << "\n";
}




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


i64 ans[maxn], w[maxn]; vector<i64>g[maxn];

i64 a[maxn];

// 记忆化搜索

void dfs(i64 u) {
	if (ans[u] != -1)return;
	std::vector<i64>dp(w[u] + 1);
	vector<i64>p;
	for (auto v : g[u]) {
		if (w[v] >= w[u])continue;
		dfs(v);
		p.push_back(v);
	}

	for (auto v : p) {
		for (i64 j = w[u] - 1; j >= 0; j--) {
			if (j >= w[v])
				dp[j] = std::max(dp[j], dp[j - w[v]] + ans[v]);
		}
	}

	ans[u] = dp[w[u] - 1] + 1;
}


int main() {
	i64 n, m; std::cin >> n >> m;
	std::fill(ans + 1, ans + 1 + n, -1);
	for (i64 i = 1; i <= m; i++) {
		i64 u, v; std::cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	for (i64 i = 1; i <= n; i++)std::cin >> w[i];
	for (i64 i = 1; i <= n; i++)std::cin >> a[i];
	i64 q = 0;
	for (i64 i = 1; i <= n; i++) {
		if (ans[i] == -1)dfs(i);
	}
	i64 res = 0;
	for (i64 i = 1; i <= n; i++) {
		res += ans[i] * a[i];
	}
	std::cout << res;
}