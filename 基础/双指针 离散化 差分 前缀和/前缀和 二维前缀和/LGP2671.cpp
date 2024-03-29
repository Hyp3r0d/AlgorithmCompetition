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

constexpr i64 mod = 1e4 + 7;
constexpr i64 maxn = 2e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;

int main() {
	i64 n, m; std::cin >> n >> m;
	std::vector<i64>w(n + 1), c(n + 1);
	for (i64 i = 1; i <= n; i++) {
		std::cin >> w[i];
	}
	i64 ans = 0;
	for (i64 i = 1; i <= n; i++)std::cin >> c[i];
	std::vector p1(m + 1, std::array<i64, 2> {0, 0});
	// x * w[x]
	std::vector p2(m + 1, std::array<i64, 2> {0, 0});
	// x
	std::vector p3(m + 1, std::array<i64, 2> {0, 0});
	std::vector p4(m + 1, std::array<i64, 2> {0, 0});
	// w[x]
	for (i64 i = 1; i <= n; i++) {
		ans = (ans % mod + p1[c[i]][i & 1]) % mod;
		ans = (ans % mod + w[i] % mod * p2[c[i]][i & 1] % mod) % mod;
		ans = (ans % mod + p3[c[i]][i & 1] % mod * i) % mod;
		ans = (ans % mod + i % mod * w[i] * p4[c[i]][i & 1] % mod) % mod;
		p1[c[i]][i & 1] = (p1[c[i]][i & 1] % mod + i % mod * w[i] % mod) % mod;
		p2[c[i]][i & 1] = (p2[c[i]][i & 1] % mod + i) % mod;
		p3[c[i]][i & 1] = (p3[c[i]][i & 1] % mod + w[i]) % mod;
		p4[c[i]][i & 1]++;
	}
	std::cout << ans << "\n";

	return 0;
}
