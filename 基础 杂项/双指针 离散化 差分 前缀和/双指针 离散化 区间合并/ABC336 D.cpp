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


i64 q[maxn], p[maxn];
int main() {
	i64 n; std::cin >> n;
	std::vector<i64>a(n + 1);

	for (i64 i = 1; i <= n; i++) {
		std::cin >> a[i];
	}
	for (i64 i = 1; i <= n; i++) {
		q[i] = std::min(q[i - 1] + 1, a[i]);
	}
	for (i64 i = n; i >= 1; i--) {
		p[i] = std::min(p[i + 1] + 1, a[i]);
	}
	i64 ans = 0;
	for (i64 i = 1; i <= n; i++) {
		ans = std::max(std::min(p[i], q[i]), ans);
	}
	std::cout << ans << "\n";
}