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
constexpr i64 maxn = 4e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


int main() {
	i64 n, m; std::cin >> n >> m;
	std::vector<i64>t(n + 1);
	for (i64 i = 1; i <= n; i++) {
		std::cin >> t[i];

	}
	vector f(n + 1, std::vector<i64>(n + 1, inf));

	for (i64 i = 1; i <= n; i++) {
		for (i64 j = 1; j <= n; j++) {
			if (i == j) {
				f[i][j] = 0;
			} else {
				f[i][j] = inf;
			}
		}
	}

	i64 now = 1;
	for (i64 i = 1; i <= m; i++) {
		i64 u, v, w; std::cin >> u >> v >> w;
		u++; v++;
		f[u][v] = f[v][u] = w;
	}
	i64 q; std::cin >> q;
	auto update = [&](i64 x) {
		for (i64 i = 1; i <= n; i++) {
			for (i64 j = 1; j <= n; j++) {
				f[i][j] = std::min(f[i][j], f[i][x] + f[x][j]);
			}
		}
	};
	while (q--) {
		i64 x, y, z; std::cin >> x >> y >> z; x++; y++;
		while (t[now] <= z and now <= n) {
			update(now); now++;
		}
		if (t[x] > z or t[y] > z) {
			puts("-1");
		} else {
			if (f[x][y] == inf and f[y][x] == inf) {
				puts("-1");
			} else {
				std::cout << std::min(f[x][y], f[y][x]) << "\n";
			}
		}
	}
}