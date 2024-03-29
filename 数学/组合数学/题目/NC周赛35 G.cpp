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

constexpr i64 mod = 1e9 + 7;
constexpr i64 maxn = 4e6 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;
i64 fac[maxn];


i64 qpow(i64 x, i64 y) {
	i64 ret = 1;
	while (y) {
		if (y & 1)ret = ret * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ret % mod;
}


i64 inv(i64 x) {
	return qpow(x, mod - 2) % mod;
}

i64 comb(i64 n, i64 m) {
	if (m > n)return 0ll;
	return fac[n] % mod * inv(fac[m] % mod * fac[n - m] % mod) % mod;
}


/*范德蒙卷积*/
int main() {
	fac[0] = 1;
	i64 n; std::cin >> n;
	for (i64 i = 1; i <= 2 * n; i++) {
		fac[i] = fac[i - 1] % mod * i % mod;
	}

	std::vector<i64>cnt(5);
	std::vector<i64>a(n + 1); i64 buf = 1;
	for (i64 i = 1; i <= n; i++) {
		std::cin >> a[i]; cnt[a[i]]++;
	}
	for (i64 i = 1; i <= cnt[1]; i++)buf = buf % mod * 2 % mod;
	i64 ans = buf;
	std::vector<i64>s(4);
	for (i64 i = 2; i <= 3; i++) {
		for (i64 j = 0; j <= cnt[i]; j++) {
			s[i] = (s[i] % mod + (j + 1) % mod * comb(cnt[i], j)) % mod;
		}
	}
	ans = (ans % mod * s[2] % mod * s[3] % mod) % mod;
	ans = ((ans - 1) % mod + mod) % mod;
	std::cout << ans << "\n";
	return 0;
}