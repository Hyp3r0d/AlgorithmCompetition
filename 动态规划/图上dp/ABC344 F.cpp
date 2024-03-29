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
constexpr i64 maxn = 6405;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


i64 n, m;
i64 w[maxn], dp[2][maxn]; bool vis[maxn];
i64 dis[maxn][maxn];
// 用 两个值表示一个状态，从起点到 i 的最小操作数
// 从起点到 i 操作数最小情况下的最大剩余能量
std::vector<pair<i64, i64>>g[maxn];

struct edge {
	i64 x; i64 id;
} a[maxn];


struct cmp {
	bool operator()(const pair<i64, i64>&x, const pair<i64, i64>&y)const {
		return x.first > y.first;
	}
};

void dijkstra(i64 s) {
	priority_queue<pair<i64, i64>, std::vector<pair<i64, i64>>, cmp>q;
	memset(vis, 0, sizeof(vis));
	dis[s][s] = 0; q.push({0, s});
	while (q.size()) {
		auto [d, u] = q.top();
		q.pop();
		if (vis[u])continue;
		vis[u] = true;
		for (auto [v, d] : g[u]) {
			if (dis[s][v] > dis[s][u] + d) {
				dis[s][v] = dis[s][u] + d;
				if (not vis[v]) {
					q.push({dis[s][v], v});
				}
			}
		}
	}
}

void change(i64 x, i64 v1, i64 v2) {
	if (v1 < dp[0][x]) {
		dp[0][x] = v1; dp[1][x] = v2;
	} else if (v1 == dp[0][x] and v2 > dp[1][x]) {
		dp[0][x] = v1, dp[1][x] = v2;
	}
}

i64 get(i64 x, i64 y) {
	return (x - 1) * n + y;
}

int main() {
	std::cin >> n;
	memset(dis, 0, sizeof(dis));
	for (i64 i = 1; i <= n * n; i++) {
		for (i64 j = 1; j <= n * n; j++) {
			if (i == j)dis[i][j] = 0;
			else dis[i][j] = inf;
		}
	}
	for (i64 i = 1; i <= n * n; i++) {
		std::cin >> w[i];
		a[i].x = w[i]; a[i].id = i;
	}
	sort(a + 1, a + 1 + n * n, [&](const edge & b, const edge & s)->bool const {
		return b.x < s.x;
	});
	a[n * n + 1].x = 0, a[n * n + 1].id = n * n;
	for (i64 i = 1; i <= n; i++) {
		for (i64 j = 1; j <= n - 1; j++) {
			i64 x; std::cin >> x;
			g[get(i, j)].push_back({get(i, j + 1), x});
		}
	}
	for (i64 i = 1; i <= n - 1; i++) {
		for (i64 j = 1; j <= n; j++) {
			i64 x; std::cin >> x;
			g[get(i, j)].push_back({get(i + 1, j), x});
		}
	}
	for (i64 i = 1; i <= n * n; i++) {
		dijkstra(i);
	}
	for (i64 i = 1; i <= n * n; i++) {
		dp[0][i] = inf, dp[1][i] = 0;
	}
	dp[0][1] = dp[1][1] = 0;
	for (i64 i = 1; i <= n * n; i++) {
		for (i64 j = i + 1; j <= n * n + 1; j++) { // 直接转移到 id = n*n的点
			i64 x = a[i].id, y = a[j].id;
			if (dis[x][y] == inf)continue;
			if (dp[1][x] >= dis[x][y]) {
				change(y, dp[0][x], dp[1][x] - dis[x][y]);
			} else {
				i64 t = dis[x][y] - dp[1][x];
				i64 k = (t + w[x] - 1) / w[x];
				change(y, dp[0][x] + k, dp[1][x] + k * w[x] - dis[x][y]);
			}
		}
	}
	if (dp[0][n * n] != inf) {
		std::cout << dp[0][n * n] + 2 * n - 2 << "\n";
	} else {
		std::cout << "-1";
	}

	return 0;
}