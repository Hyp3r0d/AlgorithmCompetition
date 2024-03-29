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
constexpr i64 maxn = 3e4 + 5;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;


i64 exgcd(i64 a, i64 b, i64 & x, i64 & y) {
	if (b == 0) {
		x = 1; y = 0;
		return a;
	}
	i64 d = exgcd(b, a % b, x, y);
	i64 temp = x; x = y;
	y = temp - a / b * y;
	return d;
}


int main() {
	i64 n, p, k; std::cin >> n >> p >> k;
	std::vector<i64>a(n + 1);
	for (i64 i = 1; i <= n; i++)std::cin >> a[i];
	i64 cur = k;
	i64 ans = 0;
	for (i64 i = 1; i <= n; i++) {
		i64 x, y; exgcd(a[i], p, x, y);
		x = ((x % p) + p) % p;
		ans = (ans % p + x % p * cur % p) % p;
		cur = (cur % p * k) % p;
	}
	std::cout << ans % p << "\n";
}