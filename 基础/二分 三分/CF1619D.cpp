#include<bits/extc++.h>


using i64 = signed long long;


constexpr i64 mod = 1e9 + 7;
constexpr i64 maxn = 2e3 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

void solve() {
	i64 m, n; std::cin >> m >> n;
	std::vector z(m + 1, std::vector<i64>(n + 1, 0));
	for (i64 i = 1; i <= m; i++) {
		for (i64 j = 1; j <= n; j++) {
			std::cin >> z[i][j];
		}
	}
	i64 l = 0, r = 1e9;
	auto check = [&](i64 x)->bool{
		for (i64 i = 1; i <= n; i++) {
			bool f = true;
			for (i64 j = 1; j <= m; j++) {
				if (z[j][i] >= x)f = false;
			}
			if (f)return false;
		}
		for (i64 i = 1; i <= m; i++) {
			i64 cnt = 0;
			for (i64 j = 1; j <= n; j++) {
				if (z[i][j] >= x)cnt++;
			}
			if (cnt >= 2)return true;
		}
		return false;
	};
	i64 ans = -1;
	while (l < r) {
		i64 mid = (l + r + 1) >> 1;
		if (check(mid)) {
			l = mid; ans = mid;
		} else {
			r = mid - 1;
		}
	}
	std::cout << l << "\n";
}


int main() {
	i64 T; std::cin >> T;
	while (T--)solve();
	return 0;
}