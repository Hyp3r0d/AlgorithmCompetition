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

constexpr i64 mod = 998244353;
constexpr i64 maxn = 3e5 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


std::vector<pair<i64, i64>>dir = {{ -1, 2}, { -1, -2}, {1, 2}, {1, -2}, {2, 1}, { -2, 1}, { -2, -1}, {2, -1}};

void solve() {
	std::unordered_set<string>st;

	string cur = "";

	for (i64 i = 0; i < 5; i++) {
		string p; std::cin >> p; cur += p;
	}

	auto locate = [&](i64 x, i64 y) {
		return x * 5 + y;
	};
	auto dlocate = [&](i64 p)->pair<i64, i64> {
		return pair<i64, i64> {p / 5, p % 5};
	};

	i64 ans = inf;

	auto check = [&](i64 x, i64 y) {
		return x >= 0 and x < 5 and y >= 0 and y < 5 and cur[locate(x, y)] == '*';
	};


	string target = "";
	target += "11111"; target += "01111"; target += "00*11"; target += "00001";
	target += "00000";
	auto cal = [&](string x) {
		i64 cnt = 0;
		for (i64 i = 0; i < 25; i++)if (x[i] != target[i])cnt++;
		return cnt;
	};
	std::function<void(i64)>dfs = [&](i64 dep) {
		if (dep > 15)return;

		if (st.count(cur))return;

		if (dep + cal(cur) > ans)return;

		if (dep + cal(cur) > 15)return;
		if (cur == target) {
			ans = std::min(ans, dep);
			return;
		}

		st.insert(cur);

		for (i64 i = 0; i < 5; i++) {
			for (i64 j = 0; j < 5; j++) {
				if (cur[locate(i, j)] == '*')continue;
				for (auto [dx, dy] : dir) {
					i64 xx = i + dx, yy = j + dy;
					if (not check(xx, yy))continue;
					swap(cur[locate(i, j)], cur[locate(xx, yy)]);
					if (st.count(cur) or dep + 1 > 15 or dep + 1 + cal(cur) >= ans or dep + 1 + cal(cur) > 15) {
						swap(cur[locate(i, j)], cur[locate(xx, yy)]);
						continue;
					}
					dfs(dep + 1);
					swap(cur[locate(i, j)], cur[locate(xx, yy)]);
				}
			}
		}
		st.erase(cur);
	};

	dfs(0);
	if (ans == inf) {
		puts("-1"); return;
	}
	std::cout << ans << "\n";

}

int main() {
	i64 t; std::cin >> t;
	while (t--) {
		solve();
	}

	return 0;
}