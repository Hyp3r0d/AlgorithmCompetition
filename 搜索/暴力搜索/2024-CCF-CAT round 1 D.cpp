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

constexpr i64 mod = 999911659;
constexpr i64 maxn = 2e7 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

std::vector<std::pair<i64, i64>>dir = {{1, 0}, { -1, 0}, {0, 1}, {0, -1}};


int main() {
	i64 n, m; std::cin >> n >> m;
	std::vector<string>g(n + 2, std::string(m + 2, '0'));
	for (i64 i = 1; i <= n; i++) {
		for (i64 j = 1; j <= m; j++) {
			i64 v; std::cin >> v;
			g[i][j] = v + '0';
		}
		//std::cout  << g[i] << "\n";;
	}
	std::vector<i64>cnt(5, 0);
	std::vector<std::vector<bool>>vis(n + 1, std::vector<bool>(m + 1, false));
	i64 ans = 0; i64 cur = 0;
	std::function<void(i64, i64)>dfs = [&](i64 x, i64 y) {
		vis[x][y] = true;
		cnt[g[x][y] - '0']++;
		for (auto [dx, dy] : dir) {
			i64 xx = x + dx, yy = y + dy;
			if (xx <= 0 or xx > n or yy <= 0 or yy > m)continue;
			if (vis[xx][yy])continue;
			if (g[xx][yy] != (char)(cur + '0'))continue;
			dfs(xx, yy);
		}
	};
	std::function<void(i64, i64)>dfs2 = [&](i64 x, i64 y) {
		vis[x][y] = false;
		for (auto [dx, dy] : dir) {
			i64 xx = x + dx, yy = y + dy;
			if (xx <= 0 or xx > n or yy <= 0 or yy > m)continue;
			if (not vis[xx][yy])continue;
			dfs2(xx, yy);
		}
	};

	std::map<vector<string>, i64>t;
	std::function<void(i64)>dfs3 = [&](i64 depth) {

		if (t.count(g))return; t[g]++;
		i64 c = 0;
		for (i64 i = 1; i <= n; i++) {
			for (i64 j = 1; j <= m; j++) {
				if (g[i][j] == 'x')c++;
			}
		}
		ans = std::max(ans, c);
		auto tmp = g;
		for (i64 i = 1; i <= n; i++) {
			for (i64 j = 1; j <= m; j++) {
				if (isdigit(g[i][j])) {
					cur = g[i][j] - '0';
					dfs(i, j);
					if (cnt[cur] < 3) {
						dfs2(i, j);
						cnt[cur] = 0;
						// 不满足消除的条件, 还原
					} else {
						// 满足消除的条件
						cnt[cur] = 0;
						for (i64 i = 1; i <= n; i++) {
							for (i64 j = 1; j <= m; j++) {
								if (vis[i][j]) {
									g[i][j] = 'x';
								}
							}
						}
						dfs2(i, j);
						// 还原vis的状态
						for (i64 i = 1; i <= m; i++) {
							i64 w = n;
							while (isdigit(g[w][i]) and w >= 1)w--;
							if (not w)continue; i64 p = w;
							for (i64 j = w; j >= 1; j--) {
								if (isdigit(g[j][i])) {
									swap(g[j][i], g[p][i]);
									p--;
								}
							}//将上块下移
						}
						dfs3(depth + 1);
						g = tmp;
						// 回溯后还原
					}

				}
			}
		}

	};
	dfs3(0);
	std::cout  << ans << "\n";
}
