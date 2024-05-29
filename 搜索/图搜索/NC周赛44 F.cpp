/*概率dp模型*/
/*不外乎两种,概率dp与期望dp,注意概率与期望的递推是不同的*/
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
constexpr i64 maxn = 1e5 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;



struct Node {
	i64 u; i64 d;
	bool operator<(const Node&b)const {
		return d > b.d;
	}
};

vector<pair<i64, i64>>g[maxn];
int main() {

	i64 n; std::cin >> n;

	for (i64 i = 1; i <= n; i++) {
		i64 u, v; std::cin >> u >> v;
		g[u].push_back({v, i});
		g[v].push_back({u, i});
	}

	std::vector<bool>ban(n + 1);


	std::vector<i64>d(n + 1, inf);
	std::function<void(i64, i64)>dfs = [&](i64 u, i64 dep) {
		if (u == n) {
			for (i64 i = 1; i <= n; i++) {
				if (not ban[i])
					d[i] = std::min(d[i], dep);
			}
			return;
		}

		for (auto [v, idx] : g[u]) {
			if (not ban[idx]) {
				ban[idx] = true;
				dfs(v, dep + 1);
				ban[idx] = false;
			}
		}
	};

	dfs(1, 0);
	for (i64 i = 1; i <= n; i++) {
		std::cout << (d[i] == inf ? -1 : d[i]) << "\n";
	}

	return 0;
}
