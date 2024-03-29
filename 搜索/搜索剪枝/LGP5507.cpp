/*双向bfs*/
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

const i64 mod = 1e9 + 7;
const i64 maxn = 2e7 + 5;
const i64 inf = 0x3f3f3f3f3f3f3f3f;

bool vis[maxn]; i64 v[maxn]; std::queue<i64>q;
i64 fa[maxn]; i64 opt[maxn];
/*是否访问过*/
/*方向*/
void solve() {
	i64 start = 0;
	std::vector nxt(14, std::vector<i64>(6, 0));
	for (i64 i = 0; i <= 11; i++) {
		i64 v; std::cin >> v;
		start |= ((v - 1) << (i << 1));
		for (i64 j = 0; j <= 3; j++) {
			std::cin >> nxt[i][j];
			nxt[i][j]--;
		}
	}

	vis[start] = vis[0] = 1;
	v[start] = 1;
	v[0] = 2;
	q.push(start);
	q.push(0);
	i64 s = 0, t = 0, mid = 0;
	bool flag = false;
	while (q.size() and not flag) {
		i64 state = q.front(); q.pop();
		i64 nextstate = 0;
		i64 direction = v[state];
		for (i64 i = 0; i <= 11; i++) {
			if (direction == 1) {
				i64 si = (state >> (i << 1)) & 3;// 第i位的状态
				i64 nx = nxt[i][si]; // 影响到的位
				i64 snext = (state >> (nx << 1)) & 3; // 影响到的位的状态
				nextstate = state; // 下一个状态
				nextstate ^= (si << (i << 1));
				nextstate ^= (((si + 1) & 3) << (i << 1));
				nextstate ^= (snext << (nx << 1));
				nextstate ^= (((snext + 1) & 3) << (nx << 1));
			} else { // 该状态为反向搜索
				i64 si = (state >> (i << 1)) & 3;
				i64 nx = nxt[i][(si + 3) & 3];
				i64 snext = (state >> (nx << 1)) & 3;
				nextstate = state ^ (si << (i << 1)) ^ (((si + 3) & 3) << (i << 1));
				nextstate = (snext << (nx << 1)) ^ (((snext + 3) & 3) << (nx << 1));
			}
			if (vis[nextstate]) {
				if (v[nextstate] == direction)continue;
				s = direction == 1 ? state : nextstate;
				mid = i + 1;
				t = direction == 1 ? nextstate : state;
				flag = true; break;
			}
			vis[nextstate] = 1;
			v[nextstate] = direction;
			fa[nextstate] = state;
			opt[nextstate] = i + 1;
			q.push(nextstate);
		}
	}
	i64 state = s;
	std::vector<i64>ans1, ans2;
	while (state != start) {
		ans1.push_back(opt[state]);
		state = fa[state];
	}
	state = t;
	while (state != 0) {
		ans2.push_back(opt[state]);
		state = fa[state];
	}
	std::cout  << ans1.size() + ans2.size() + 1 << "\n";;
	for (i64 i = ans1.size() - 1; i >= 0; i--) {
		std::cout  << ans1[i] << " ";
	}
	std::cout  << mid << " ";
	for (i64 i = 0; i < ans2.size(); i++) {
		std::cout  << ans2[i] << " ";
	}
}

int main() {
	solve();
	return 0;
}