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

constexpr i64 mod = 45989;
constexpr i64 maxn = 4e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


int main() {
	i64 n; std::cin >> n; i64 sum = 0;
	std::vector<i64>a(n + 1);
	std::vector<i64>dp1(n + 5, 0), dp2(n + 5, 0);
	for (i64 i = 1; i <= n; i++) {
		std::cin >> a[i]; sum += a[i];
	}
	for (i64 i = 1; i <= n; i++) {
		dp1[i] = std::max(dp1[i - 1], 0ll) + a[i];
	}
	for (i64 i = n; i >= 1; i--) {
		dp2[i] = std::max(dp2[i + 1], 0ll) + a[i];
	}
	for (i64 i = 2; i <= n; i++) {
		dp1[i] = std::max(dp1[i], dp1[i - 1]);
	}
	for (i64 i = n - 1; i >= 1; i--) {
		dp2[i] = std::max(dp2[i], dp2[i + 1]);
	}
	i64 ans = -inf;
	for (i64 i = 1; i <= n - 1; i++) {
		ans = std::max(ans, dp1[i] + dp2[i + 1]);
	}

	for (i64 i = 1; i <= n; i++) {
		dp1[i] = std::min(dp1[i - 1], 0ll) + a[i];
	}
	for (i64 i = 2; i <= n; i++)dp1[i] = min(dp1[i], dp1[i - 1]);
	for (i64 i = n; i >= 1; i--) {
		dp2[i] = std::min(dp2[i + 1], 0ll) + a[i];
	}
	for (i64 i = n - 1; i >= 1; i--)dp2[i] = min(dp2[i], dp2[i + 1]);
	i64 z = inf;
	for (i64 i = 1; i <= n - 1; i++) {
		z = min(z, dp1[i] + dp2[i + 1]);
	}
	ans = std::max(ans, sum - z);
	std::cout << ans << "\n";
}