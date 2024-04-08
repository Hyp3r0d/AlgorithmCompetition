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


std::vector<pair<i64, i64>>dir = {{1, 0}, { -1, 0}, {0, 1}, {0, -1}};
i64 n, k;
std::map<vector<string>, int>p;
int main() {
	std::cin >> n >> k;
	std::vector<string>g(n + 1);
	i64 tot = 0;
	for (int i = 1; i <= n; i++) {
		std::cin >> g[i];
		g[i] = " " + g[i];
	}
	i64 ans = 0;
	std::function<void(i64)>dfs = [&](i64 cur) {
		if (p[g])return; // 可以考虑哈希技术为暴搜加上记忆化
		p[g]++;
		if (cur == 0) {
			ans++; return;
		}
		for (i64 i = 1; i <= n; i++) {
			for (i64 j = 1; j <= n; j++) {
				if (g[i][j] == '.') {
					for (auto [dx, dy] : dir) {
						dx += i, dy += j;
						if (dx >= 1 and dy <= n and dx <= n and dy >= 1 and g[dx][dy] == 'r') {
							g[i][j] = 'r';
							dfs(cur - 1);
							g[i][j] = '.';
						}
					}
				}
			}
		}
	};
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (g[i][j] == '.') {
				g[i][j] = 'r';
				dfs(k - 1);
				g[i][j] = '.';
			}
		}
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

int main() {
	std::cin >> n >> k;
	std::vector<string>g(n + 1);
	i64 tot = 0;
	for (int i = 0; i < n; i++) {
		std::cin >> g[i];
	}
	i64 ans = 0;
	auto check = [&](i64 x, i64 y) {
		for (auto [dx, dy] : dir) {
			int nx = x + dx, ny = y + dy;
			if (nx >= 0 and nx < n and ny >= 0 and ny < n and g[nx][ny] == '@') {
				return true;
			}
		}
		return false;
	};
	std::function<void(i64)>dfs = [&](i64 cur) {
		if (cur == k) {
			++ans; return;
		}
		std::vector<pair<i64, i64>>p;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (g[i][j] == '.' and (cnt == 0 or check(i, j))) {
					g[i][j] = '@';
					p.push_back({i, j});
					dfs(cnt + 1);
					g[i][j] = '#';
				}
			}
		}
		for (auto [x, y] : p) {
			g[x][y] = '.';
		}
	};
	dfs(0);
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


pair<i64, i64>stk[maxn];
i64 ban[8][8]; i64 sn = 0;

int main() {
	int n, k; std::cin >> n >> k;
	std::vector<string>s(n);
	for (int i = 0; i < n; i++) {
		std::cin >> s[i];
	}
	i64 ans = 0;
	std::function<void(i64, i64)>dfs = [&](i64 it, i64 cur) {
		if (cur == k) {
			ans++; return;
		}
		if (it == sn) {return;}
		dfs(it + 1, cur);
		i64 nxt = sn;
		for (auto [dx, dy] : dir) {
			i64 nx = stk[it].first + dx;
			i64 ny = stk[it].second + dy;
			if (not check(nx, ny) or ban[nx][ny] or s[nx][ny] == '#')continue;
			ban[nx][ny] = 1;
			stk[++sn] = {nx, ny};
			dfs(it + 1, cur + 1);
			while (sn > nxt) {
				ban[stk[sn].first][stk[sn].second] = 0;
				sn--;
			}
			sn = nxt;
		}
	};
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (s[i][j] == '#')continue;
			ban[i][j] = 1; sn = 0;
			for (auto [dx, dy] : dir) {
				i64 nx = i + dx, ny = j + dy;
				if (not check(nx, ny) or ban[nx][ny] or s[nx][ny] == '#' ) {
					continue;
				}
				ban[nx][ny] = 1;
				stk[++sn] = {nx, ny};
			}
			dfs(0, 1);
			while (sn > 0) {
				ban[stk[sn].first][stk[sn].second] = 0;
				sn--;
			}
		}
	}
}