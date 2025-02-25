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
const i64 mod = 998244353;
const i64 maxn = 2e5 + 5;
const i64 inf = 0x3f3f3f3f3f3f3f3f;


int main() {
	i64 n, q; std::cin >> n >> q;
	std::vector<i64>a(n + 1);
	for (i64 i = 1; i <= n; i++)std::cin >> a[i];
	std::sort(a.begin() + 1, a.begin() + 1 + n);
	while (q--) {
		i64 b, k; std::cin >> b >> k;
		i64 l = 0, r = 1e9;
		auto check = [&](i64 x) {
			i64 l = lower_bound(a.begin() + 1, a.begin() + 1 + n, b - x) - a.begin();
			i64 r = upper_bound(a.begin() + 1, a.begin() + 1 + n, b + x) - a.begin() - 1;
			return r - l + 1 >= k;
		};
		i64 ans = -1;
		while (l <= r) {
			i64 mid = (l + r) >> 1;
			if (check(mid))r = mid - 1, ans = mid;
			else l = mid + 1;
		}
		std::cout << ans << "\n";
	}
	return 0;
}