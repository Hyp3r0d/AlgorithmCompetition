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
	i64 l = 0, r = 1e18;
	i64 n, m, k; std::cin >> n >> m >> k;
	auto check = [&](i64 x) {
		return x / m + x / n - x / ((n * m) / gcd(n, m)) * 2;
	};
	i64 ans = -1;
	while (l <= r) {
		i64 mid = (l + r) >> 1;
		if (check(mid) >= k) {
			ans = mid; r = mid - 1;
		} else l = mid + 1;
	}
	std::cout << ans << "\n";
}