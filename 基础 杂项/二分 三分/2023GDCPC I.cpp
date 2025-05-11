/* 
https://www.luogu.com.cn/contest/135929#problems
*/
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


void solve() {
	i64 n, m; std::cin >> n >> m;
	vector<pair<i64, i64>>p(n * m + 5);
	for (i64 i = 0; i < n; i++) {
		for (i64 j = 0; j < m; j++) {
			i64 v; std::cin >> v;
			p[v] = {i, j};
		}
	}
	auto check = [&](i64 mid)->bool{
		vector<pair<i64, i64>>tmp;
		for (i64 i = 0; i < mid; i++) {
			tmp.push_back(p[i]);
		}
		std::sort(tmp.begin(), tmp.end(), [&](pair<i64, i64>x, pair<i64, i64>y)->bool{
			if (x.first != y.first)return x.first < y.first;
			if (x.second != y.second)return x.second < y.second;
		});
		for (i64 i = 1; i < tmp.size(); i++) {
			if (tmp[i].second < tmp[i - 1].second)return false;
		}
		return true;
	};
	i64 l = 0, r = n * m;
	while (l < r) {
		i64 mid = (l + r + 1) >> 1;
		if (check(mid))l = mid;
		else r = mid - 1;
	}
	std::cout  << l << "\n";
;
}
int main() {
	i64 T; std::cin >> T;
	while (T--) {
		solve();
	}
}
