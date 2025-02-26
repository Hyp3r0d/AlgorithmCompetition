/* tarjan求无向图割边*/


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
constexpr i64 maxn = 1e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;



i64 n, m, a, b; i64 tot = 0;
i64 dfn[maxn], cnt1[maxn], cnt2[maxn], l[maxn];
i64 head[maxn]; i64 cnt = 0;
struct edge {
	i64 u, v, nxt;
} e[maxn];


bool vis[maxn];
void addedge(i64 u, i64 v) {
	e[cnt].u = u; e[cnt].v = v;
	e[cnt].nxt = head[u]; head[u] = cnt++;
}
int main() {
	memset(head, -1, sizeof(head));
	std::cin >> n >> m >> a >> b;
	for (i64 i = 1; i <= a; i++) {
		i64 v; std::cin >> v;
		cnt1[v] = 1;
	}
	for (i64 i = 1; i <= b; i++) {
		i64 v; std::cin >> v;
		cnt2[v]++;
	}
	//std::vector<std::vector<i64>>g(n + 1);
	for (i64 i = 1; i <= m; i++) {
		i64 x, y; std::cin >> x >> y;
		addedge(x, y); addedge(y, x);
	}
	std::vector<std::pair<i64, i64>>ans;
	std::function<void(i64)>tarjan = [&](i64 u) {
		dfn[u] = l[u] = ++tot;
		for (i64 i = head[u]; i != -1; i = e[i].nxt) {
			if (not vis[i]) {
				vis[i] = vis[i ^ 1] = 1;
				i64 v = e[i].v;
				if (not dfn[v]) {
					tarjan(v), cnt1[u] += cnt1[v], cnt2[u] += cnt2[v];
					l[u] = std::min(l[u], l[v]);
					if (l[v] > dfn[u] and (cnt1[v] == 0 or cnt2[v] == 0 or cnt1[v] == a or cnt2[v] == b)) {
						ans.push_back({u, v});
					}
				} else {
					l[u] = std::min(l[u], dfn[v]);
				}
			}
		}
	};
	tarjan(1);
	std::cout << ans.size() << "\n";
	for (auto [u, v] : ans) {
		std::cout << u << " " << v << "\n";
	}
	return 0;
}