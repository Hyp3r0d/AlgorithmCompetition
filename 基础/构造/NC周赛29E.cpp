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

constexpr i64 mod = 1e9 + 7;
constexpr i64 maxn = 2e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


/* dp i j 为 该轮操作状态下还剩i 仑， 有 j 个 2 , 当前操作者赢的概率*/

int main() {
	i64 x; std::cin >> x; i64 z = 0;
	std::unordered_map<i64, i64>w;
	i64 mx = 0, sum = 0;
	std::priority_queue<std::pair<i64, i64>>pq;
	for (i64 i = 2; i <= sqrt(x); i++) {
		if (x % i == 0) {
			i64 cnt = 0;
			while (x % i == 0) {
				x /= i, cnt++;
			}
			sum += cnt;
			w[i] = cnt; mx = std::max(mx, cnt);
			pq.push({cnt, i});
		}
	}

	if (x > 1) {
		w[x] = 1; sum += 1; mx = std::max(mx, 1ll);
		pq.push({1ll, x});
	}

	if (mx - 1 > sum - mx) {
		puts("-1"); return 0;
	}
	std::vector<i64>ans;
	while (pq.size() > 1) {
		auto [x1, y1] = pq.top();
		pq.pop();
		auto [x2, y2] = pq.top();
		pq.pop();
		ans.push_back(y1); ans.push_back(y2);
		if (x1 - 1)pq.push({x1 - 1, y1});
		if (x2 - 1)pq.push({x2 - 1, y2});
	}
	if (pq.size())ans.push_back(pq.top().second);
	pq.pop();
	std::cout << ans.size() << "\n";
	for (i64 i = 0; i < ans.size(); i++) {
		std::cout << ans[i] << " \n"[i == ans.size() - 1];
	}
	return 0;
}