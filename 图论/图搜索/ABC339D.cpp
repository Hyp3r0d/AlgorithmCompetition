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

int xchg[4] = {1, -1, 0, 0}, ychg[4] = {0, 0, 1, -1};
i64 dis[65][65][65][65];
bool vis[65][65][65][65];
vector<string > mp;

struct jgt {
	i64 dist;
	int x1, y1, x2, y2;
	bool operator < (const jgt &x) const {
		return dist > x.dist;
	}
};

priority_queue<jgt> q;

int n;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nui64ptr);
	cout.tie(nui64ptr);
	for (int i = 0; i <= 60; ++i)
		for (int j = 0; j <= 60; ++j)
			for (int ii = 0; ii <= 60; ++ii)
				for (int jj = 0; jj <= 60; ++jj)
					dis[i][j][ii][jj] = 1e18;
	memset(vis, 0, sizeof vis);
	cin >> n;
	mp = vector<string >(n);
	for (auto &i : mp) cin >> i;
	int p1x = -1, p1y = -1, p2x = -1, p2y = -1;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (mp[i][j] == 'P') {
				if (p1x == -1) {
					p1x = i;
					p1y = j;
				} else {
					p2x = i;
					p2y = j;
				}
			}
		}
	}
	dis[p1x][p1y][p2x][p2y] = 0;
	q.push((jgt) {0, p1x, p1y, p2x, p2y});
	while (!q.empty()) {
		auto frot = q.top();
		q.pop();
		int curx1 = frot.x1, cury1 = frot.y1, curx2 = frot.x2, cury2 = frot.y2;
		i64 curdis = frot.dist;
		if (vis[curx1][cury1][curx2][cury2]) continue;
		vis[curx1][cury1][curx2][cury2] = 1;
		for (int i = 0; i < 4; ++i) {
			int tarx1 = curx1 + xchg[i], tarx2 = curx2 + xchg[i], tary1 = cury1 + ychg[i], tary2 = cury2 + ychg[i];
			if (tarx1 < 0 || tarx1 >= n || tary1 < 0 || tary1 >= n || mp[tarx1][tary1] == '#') tarx1 = curx1, tary1 = cury1;
			if (tarx2 < 0 || tarx2 >= n || tary2 < 0 || tary2 >= n || mp[tarx2][tary2] == '#') tarx2 = curx2, tary2 = cury2;
			if (dis[tarx1][tary1][tarx2][tary2] > curdis + 1) {
				dis[tarx1][tary1][tarx2][tary2] = curdis + 1;
				if (!vis[tarx1][tary1][tarx2][tary2]) {
					q.push((jgt) {dis[tarx1][tary1][tarx2][tary2], tarx1, tary1, tarx2, tary2});
				}
			}
		}
	}
	i64 ans = 1e18;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			ans = min(ans, dis[i][j][i][j]);
		}
	}
	if (ans == 1e18) cout << -1 << "\n";
	else cout << ans;
	return 0;
}