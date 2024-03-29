/*A Star搜索*/
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

constexpr i64 mod = 1e9 + 7;
constexpr i64 maxn = 2e7 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


/*启发式搜索使用期望函数剪枝 + 暴搜*/
/*Astar搜索是启发式搜索 + 优先队列*/
i64 nxt[20][20]; i64 g[maxn];
i64 fa[maxn], ans[maxn], opt[maxn];
struct Node {
	i64 state;
	f64 f;
	Node(i64 s): state(s) {
		f64 h = 0;
		f = 0;
		for (i64 i = 0; i <= 11; i++) {
			if ((s >> (i << 1)) & 3) {
				h += 4 - ((s >> (i << 1)) & 3);
			}
		}
		/*该状态最理想*/
		f = h * 0.6 + g[s];
	}
};
struct cmp {
	bool operator()(const Node&x, const Node&y)const {
		return x.f > y.f;
	}
};
std::priority_queue<Node, std::vector<Node>, cmp>q;
int main() {
	i64 start = 0;
	for (i64 i = 0; i <= 11; i++) {
		i64 v; std::cin >> v;
		start |= (v - 1) << (i << 1);
		for (i64 j = 0; j <= 3; j++) {
			std::cin >> nxt[i][j];
			nxt[i][j]--;
		}
	}
	q.push(Node(start));
	while (q.size()) {
		i64 state = q.top().state;
		q.pop();
		if (state == 0)break;
		for (i64 i = 0; i <= 11; i++) {
			i64 si = (state >> (i << 1)) & 3;
			i64 nx = nxt[i][si];
			i64 snext = (state >> (nx << 1)) & 3;
			i64 nextstate = state ^ (si << (i << 1)) ^ (((si + 1) & 3) << (i << 1));
			nextstate ^= ((snext << (nx << 1)));
			nextstate ^= ((((snext + 1) & 3) << (nx << 1)));
			if (not g[nextstate]) {
				g[nextstate] = g[state] + 1;
				fa[nextstate] = state;
				opt[nextstate] = i + 1;
				q.push(Node(nextstate));
			}
		}
	}
	i64 cnt = 0, state = 0;
	while (state != start) {
		ans[++cnt] = opt[state];
		state = fa[state];
	}
	std::cout  << cnt << "\n";;
	for (i64 i = cnt; i >= 1; i--) {
		std::cout  << ans[i] << " \n"[i == 1];
	}
	return 0;
}