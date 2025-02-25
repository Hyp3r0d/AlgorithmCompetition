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
constexpr i64 maxn = 4e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


int main() {
	i64 n; std::cin >> n;
	std::vector<i64>a(n + 5);
	for (i64 i = 1; i <= n; i++)std::cin >> a[i];
	i64 mx = *max_element(a.begin() + 1, a.begin() + 1 + n);
	std::vector<i64>ans(mx + 5, 0);

	for (i64 i = 1; i <= n; i++) {
		for (i64 l = 1; l <= mx;) {
			i64 t = (a[i] + l - 1) / l;
			i64 r = std::min(mx, (a[i] - 1) / l ? (a[i] - 1) / ((a[i] - 1) / l) : (i64)1e9);
			if (a[i] > a[i - 1])ans[l] += t, ans[r + 1] -= t;
			if (a[i] < a[i + 1])ans[l] -= t, ans[r + 1] += t;
			l = r + 1;
		}
	}
	for (i64 i = 1; i <= mx; i++) {
		ans[i] += ans[i - 1];
		std::cout << ans[i] << " \n"[i == mx];
	}

}


