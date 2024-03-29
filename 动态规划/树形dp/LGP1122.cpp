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

constexpr i64 mod = 45989;
constexpr i64 maxn = 5e4 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


i64 a[maxn], dp[maxn];
std::vector<i64>g[maxn];

void dfs(i64 u, i64 f) {
	dp[u] = a[u];
	for (auto v : g[u]) {
		if (v == f)continue;
		dfs(v, u);
		dp[u] = std::max(dp[u], dp[u] + dp[v]);
	}
}
int main() {
	i64 n; std::cin >> n;
	for (i64 i = 1; i <= n; i++) {
		std::cin >> a[i];
	}
	std::fill(dp + 1, dp + 1 + n, -inf);
	for (i64 i = 1; i <= n - 1; i++) {
		i64 u, v; std::cin >> u >> v;
		g[u].push_back(v); g[v].push_back(u);
	}
	i64 ans = 0;
	dfs(1, 0);
	std::cout << *max_element(dp + 1, dp + 1 + n) << "\n";
}