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

int main() {
	i64 n, m; std::cin >> n >> m;
	std::vector dis(n + 1, std::vector<i64>(n + 1, inf));
	for (i64 i = 1; i <= n; i++) {
		dis[i][i] = 0;
	}
	std::vector<array<i64, 3>>e(m + 1);
	for (i64 i = 1; i <= m; i++) {
		std::cin >> e[i][0] >> e[i][1] >> e[i][2];
		dis[e[i][0]][e[i][1]] = dis[e[i][1]][e[i][0]] = e[i][2];
	}
	for (i64 k = 1; k <= n; k++) {
		for (i64 i = 1; i <= n; i++) {
			for (i64 j = 1; j <= n; j++) {
				dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
			}
		}
	}
	i64 ans = 0;
	for (i64 i = 1; i <= m; i++) {
		auto [u, v, w] = e[i];
		for (i64 k = 1; k <= n; k++) {
			if (w >= dis[u][k] + dis[k][v]) {
				ans += 1; break;
			}
		}
	}
	std::cout << ans << "\n";
}