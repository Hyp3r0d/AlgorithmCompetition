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
const i64 mod = 998244353;
const i64 maxn = 2e5 + 5;
const i64 inf = 0x3f3f3f3f3f3f3f3f;


int main() {
	i64 n, m; std::cin >> n >> m;
	std::vector<array<i64, 3>>e(m + 1);
	std::vector f(n + 1, std::vector<i64>(n + 1, inf));
	for (i64 i = 1; i <= n; i++)for (i64 j = 1; j <= n; j++)if (i == j)f[i][j] = 0;
	for (i64 i = 1; i <= m; i++) {
		i64 u, v, t; std::cin >> u >> v >> t;
		f[u][v] = std::min(f[u][v], t);
		f[v][u] = std::min(f[v][u], t);
		e[i] = {u, v, t};
	}

	for (i64 i = 1; i <= n; i++) {
		for (i64 j = 1; j <= n; j++) {
			for (i64 k = 1; k <= n; k++) {
				f[j][k] = std::min(f[j][k], f[j][i] + f[i][k]);
			}
		}
	}

	i64 q; std::cin >> q;
	while (q--) {
		i64 k; std::cin >> k;
		std::vector<i64>z(k + 1);
		for (i64 i = 1; i <= k; i++)std::cin >> z[i];
		i64 res = inf;

		do {
			for (i64 i = 0; i < (1 << k); i++) {
				i64 cur = 1; i64 c = 0;
				for (i64 j = 1; j <= k; j++) {
					auto [u, v, t] = e[z[j]];
					if ((i >> (j - 1)) & 1)std::swap(u, v);
					c += f[cur][u]; c += t;
					cur = v;
				}
				if (cur != n)c += f[cur][n];
				res = std::min(res, c);
			}

		} while (next_permutation(z.begin() + 1, z.begin() + 1 + k));
		std::cout << res << "\n";
	}
}