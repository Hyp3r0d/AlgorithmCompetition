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

/*数论分块结论*/

void solve() {
	i64 ans = 0;
	i64 n; std::cin >> n;
	for (i64 l = 1; l <= n;) {
		i64 r = n / (n / l);
		ans += (r - l + 1) * (n / l);
		l = r + 1;
	}
	std::cout << ans << "\n";
}

int main() {
	i64 t; std::cin >> t;
	while (t--) {
		solve();
	}
}
