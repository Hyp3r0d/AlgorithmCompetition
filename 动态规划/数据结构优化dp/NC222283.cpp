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
	i64 n, m;
	std::cin >> n >> m;
	std::vector<i64>a(n + 1);
	for (i64 i = 1; i <= n; i++) {
		std::cin >> a[i];
	}
	std::vector<i64>r(n + 1, n + 1);
	std::vector<i64>stk;
	for (i64 i = n; i >= 1; i--) {
		while (stk.size() and a[i] >= a[stk.back()]) {
			stk.pop_back();
		}
		if (stk.size()) {
			r[i] = stk.back();
		}
		stk.push_back(i);
	}

	std::vector f(n + 1, std::vector<i64>(25, 0));
	for (i64 i = 1; i <= n; i++) {
		f[i][0] = r[i];
	}
	for (i64 j = 1; j <= 17; j++) {
		for (i64 i = 1; i <= n; i++) {
			if (f[i][j - 1] > n)f[i][j] = n + 1;
			else f[i][j] = f[f[i][j - 1]][j - 1];
		}
	}/*倍增*/
	while (m--) {
		i64 l, r; std::cin >> l >> r;
		i64 res = 0;
		for (i64 i = 17; i >= 0; i--) {
			if (f[l][i] <= r)l = f[l][i], res |= (1 << i);
		}
		std::cout << res + 1 << "\n";
	}
	


}