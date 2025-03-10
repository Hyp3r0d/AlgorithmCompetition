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
	ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout .tie(0);
	i64 n, m; std::cin >> n >> m;
	auto inv = [&](i64 x) {
		i64 b = mod - 2;
		i64 ret = 1;
		while (b) {
			if (b & 1) {
				ret = ret % mod * x % mod;
			}
			x = x % mod * x % mod;
			b >>= 1;
		}
		return ret % mod;
	};
	i64 p = inv(2) % mod;
	auto qpow = [&](i64 a, i64 b) {
		i64 ret = 1;
		while (b) {
			if (b & 1)ret = ret % mod * a % mod;
			a = a % mod * a % mod;
			b >>= 1;
		}
		return ret % mod;
	};
	i64 ans = 1; i64 pre = 0;
	for (i64 l = n, r; l <= n + m - 1; l = r + 1) {
		i64 cur = 0;
		while ((1ll << cur) <= l + 1)cur++;
		cur--;
		r = min((1ll << (cur + 1)) - 2ll, n + m - 1);
		i64 s = ((1ll - qpow(p, cur)) % mod + mod) % mod;
		ans = ans % mod * qpow(s, max(0ll, r - l + 1)) % mod;
	}
	std::cout  << ans % mod << "\n";;
	return 0;
}