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
constexpr f64 eps = 1e-7;


int main() {
	i64 n, m; std::cin >> n >> m;
	std::vector<i64>deg(n + 1);
	std::vector<std::vector<i64>>g(n + 1);
	for (i64 i = 1; i <= m; i++) {
		string s; std::cin >> s;
		std::vector<i64>dep(n + 1);
		auto u = s[0] - 'A' + 1, v = s[2] - 'A' + 1;
		g[u].push_back(v);
		deg[v] += 1; auto d = deg; std::queue<i64>q;
		for (i64 i = 1; i <= n; i++) {
			if (not d[i]) {
				q.push(i); dep[i] = 1;
			}
		}
		i64 cnt = 0; string h = "";
		while (q.size()) {
			auto u = q.front(); q.pop();
			cnt++;
			h += char(u - 1 + 'A');
			for (auto v : g[u]) {
				d[v]--; dep[v] = std::max(dep[v], dep[u] + 1);
				if (not d[v]) {
					q.push(v);
				}
			}
		}
		if (cnt != n) {
			printf("Inconsistency found after %d relations.\n", i);
			return 0;
		}
		i64 depmax = *std::max_element(dep.begin() + 1, dep.begin() + 1 + n);
		if (depmax == n) {
			printf("Sorted sequence determined after %d relations: ", i);
			std::cout << h << ".\n";
			return 0;
		}
	}
	puts("Sorted sequence cannot be determined.");
}