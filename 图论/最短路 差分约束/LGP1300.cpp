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
constexpr i64 maxn = 3e4 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


// 0 北 1 西 2 南 3 东

bool vis[45][45][45]; // 在那个坐标朝那
std::vector<pair<i64, i64>>rev = {{ -1, 0}, {0, -1}, {1, 0}, {0, 1}};
struct Node {
	i64 x, y, dir, d;
	bool operator<(const Node&b)const {
		return d > b.d;
	}
};

priority_queue<Node>que;
i64 dis[45][45][4];
int main() {
	i64 h, w; std::cin >> h >> w;
	std::vector<string>G(h + 1);
	for (i64 i = 1; i <= h; i++) {
		std::cin >> G[i]; G[i] = " " + G[i];
	}
	memset(dis, 0x3f, sizeof(dis));
	i64 sx, sy, tx, ty;
	for (i64 i = 1; i <= h; i++) {
		for (i64 j = 1; j <= w; j++) {
			if (isalpha(G[i][j])) {
				if (G[i][j] == 'F') {
					tx = i, ty = j;
				} else {
					sx = i, sy = j;
				}
			}
		}
	}
	if (G[sx][sy] == 'N') {
		que.push({sx, sy, 0, 0});
		dis[sx][sy][0] = 0;
	} else if (G[sx][sy] == 'W') {
		que.push({sx, sy, 1, 0});
		dis[sx][sy][1] = 0;
	} else if (G[sx][sy] == 'S') {
		que.push({sx, sy, 2, 0});
		dis[sx][sy][2] = 0;
	} else if (G[sx][sy] ==	 'E') {
		que.push({sx, sy, 3, 0});
		dis[sx][sy][3] = 0;
	}
	auto check = [&](i64 x, i64 y) {
		if (x >= 1 and x <= h and y >= 1 and y <= w and G[x][y] != '.')return true;
		return false;
	};
	while (que.size()) {
		auto cur = que.top(); que.pop();
		i64 x = cur.x, y = cur.y, dir = cur.dir, d = cur.d;
		if (vis[x][y][dir])continue;
		vis[x][y][dir] = true;
		bool f = false;
		// 试试直行
		auto tmp = dir;
		auto [dx, dy] = rev[tmp];
		if (check(x + dx, y + dy)) {
			f = true;
			if (dis[x + dx][y + dy][tmp] > dis[x][y][dir]) {
				dis[x + dx][y + dy][tmp] = dis[x][y][dir];
				if (not vis[x + dx][y + dy][tmp]) {
					que.push({x + dx, y + dy, tmp});

				}
			}
		}
		// 试试左转
		tmp = (dir + 1) % 4;
		dx = rev[tmp].first, dy = rev[tmp].second;
		if (check(x + dx, y + dy)) {
			f = true;
			if (dis[x + dx][y + dy][tmp] > dis[x][y][dir] + 1) {
				dis[x + dx][y + dy][tmp] = dis[x][y][dir] + 1;
				if (not vis[x + dx][y + dy][tmp]) {
					que.push({x + dx, y + dy, tmp});

				}
			}
		}
		// 试试右转
		tmp = (dir + 3) % 4;
		dx = rev[tmp].first, dy = rev[tmp].second;
		if (check(x + dx, y + dy)) {
			f = true;
			if (dis[x + dx][y + dy][tmp] > dis[x][y][dir] + 5) {
				dis[x + dx][y + dy][tmp] = dis[x][y][dir] + 5;
				if (not vis[x + dx][y + dy][tmp]) {
					que.push({x + dx, y + dy, tmp});

				}
			}
		}
		// 都不行
		if (not f) {
			tmp = (dir + 2) % 4;
			dx = rev[tmp].first, dy = rev[tmp].second;
			if (check(x + dx, y + dy)) {
				if (dis[x + dx][y + dy][tmp] > dis[x][y][dir] + 10) {
					dis[x + dx][y + dy][tmp] = dis[x][y][dir] + 10;
					if (not vis[x + dx][y + dy][tmp]) {
						que.push({x + dx, y + dy, tmp});

					}
				}
			}
		}
	}
	i64 ans = inf;
	for (i64 i = 0; i <= 3; i++) {
		ans = std::min(ans, dis[tx][ty][i]);
	}
	std::cout << ans << "\n";
	return 0;
}