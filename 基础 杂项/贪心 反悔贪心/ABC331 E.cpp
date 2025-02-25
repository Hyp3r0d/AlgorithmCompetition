/*tarjan 缩点模板*/

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
	i64 n, m, l; std::cin >> n >> m >> l;
	std::vector<i64>a(n + 1), b(m + 1);
	std::set<pair<i64, i64>>st;
	for (i64 i = 1; i <= n; i++) {
		std::cin >> a[i];
	}
	for (i64 i = 1; i <= m; i++) {
		std::cin >> b[i];
	}
	std::vector<i64>idx(m + 1);
	for (i64 i = 1; i <= l; i++) {
		i64 u, v; std::cin >> u >> v;
		st.insert({u, v});
	}
	std::iota(idx.begin() + 1, idx.begin() + 1 + m, 1);

	std::sort(idx.begin() + 1, idx.begin() + 1 + m, [&](i64 x, i64 y)->bool{
		return b[x] > b[y];
	});

	std::vector<i64>z(n + 1, 1);

	std::priority_queue<std::pair<i64, i64>, vector<pair<i64, i64>>, less<>>pq;
	for (i64 i = 1; i <= n; i++) {
		pq.push({a[i] + b[idx[z[i]]], i});
	}
	while (1) {
		auto u = pq.top(); pq.pop();
		if (not st.count({u.second, idx[z[u.second]]})) {
			std::cout << u.first << "\n";
			return 0;
		}
		z[u.second]++;
		if (z[u.second] <= m) {
			pq.push({a[u.second] + b[idx[z[u.second]]], u.second});
		}
	}
	return 0;
}