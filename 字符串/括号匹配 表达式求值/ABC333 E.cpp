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
constexpr i64 maxn = 2e5 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

int main() {
	i64 n; std::cin >> n;
	i64 ans = 0;
	std::vector<i64>t(n + 1), x(n + 1);
	for (i64 i = 1; i <= n; i++) {
		std::cin >> t[i] >> x[i];
	}

	std::vector<i64>res(n + 1);

	std::vector<std::vector<i64>>p(n + 1);
	std::vector<bool>vis(n + 1);
	for (i64 i = 1; i <= n; i++) {
		if (t[i] == 1) {
			p[x[i]].push_back(i);
		} else {
			if (p[x[i]].size() == 0) {
				puts("-1"); return 0;
			} else {
				vis[p[x[i]].back()] = true;
				p[x[i]].pop_back();
			}
		}
	}
	i64 cnt = 0;
	for (i64 i = 1; i <= n; i++) {
		if (vis[i]) {
			cnt++;
		} else if (t[i] == 2) {
			cnt--;
		}
		ans = std::max(ans, cnt);
	}
	std::cout << ans << "\n";
	for (i64 i = 1; i <= n; i++) {
		std::cout << vis[i] << " \n"[i == n];
	}
}